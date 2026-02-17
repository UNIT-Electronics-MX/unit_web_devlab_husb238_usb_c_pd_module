/*
 * HUSB238 USB-C PD Controller with BLE Support
 * 
 * Control del módulo HUSB238 USB-C Power Delivery via Bluetooth Low Energy
 * Compatible con ESP32 (probado con ESP32-C3, ESP32-S3)
 * 
 * Características:
 * - Control de voltajes USB-C PD (5V, 9V, 12V, 15V, 18V, 20V)
 * - Lectura de corriente disponible
 * - Detección de conexión USB-C
 * - Sweep automático de voltajes
 * - Control via BLE y Serial (SCPI commands)
 * 
 * Comandos SCPI soportados:
 * - *IDN?              : Identificación del dispositivo
 * - STAT?              : Estado de conexión USB-C (ATTACHED/UNATTACHED)
 * - PD:LIST?           : Lista de voltajes disponibles
 * - PD:GET?            : Voltaje actual seleccionado
 * - PD:SET<voltage>    : Establecer voltaje (5, 9, 12, 15, 18, 20)
 * - PD:SWEEP           : Sweep todos los voltajes disponibles
 * - CURR:GET?          : Corriente actual
 * - CURR:MAX?<voltage> : Corriente máxima para un voltaje específico
 */

#include <Wire.h>
#include "Adafruit_HUSB238.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// Configuración de pines I2C
#define I2C_SDA 12
#define I2C_SCL 22

// UUIDs para el servicio BLE
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define COMMAND_CHAR_UUID   "6d68efe5-04b6-4a85-abc4-c2670b7bf7fd"  // Write - Recibir comandos
#define RESPONSE_CHAR_UUID  "f27b53ad-c63d-49a0-8c0f-9f297e6cc520"  // Read/Notify - Enviar respuestas

// Variables globales
Adafruit_HUSB238 husb238;
BLEServer* pServer = NULL;
BLECharacteristic* pCommandCharacteristic = NULL;
BLECharacteristic* pResponseCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
String cmd = "";
String bleCommandBuffer = "";

// Forward declaration
void handleSCPI(String c, bool viaBLE);

// ========================================
// CALLBACKS BLE
// ========================================
class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
    Serial.println("BLE: Cliente conectado");
  };

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
    Serial.println("BLE: Cliente desconectado");
  }
};

class CommandCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    uint8_t* data = pCharacteristic->getData();
    size_t len = pCharacteristic->getLength();
    
    for (size_t i = 0; i < len; i++) {
      char ch = (char)data[i];
      if (ch == '\n') {
        handleSCPI(bleCommandBuffer, true); // true = respuesta via BLE
        bleCommandBuffer = "";
      } else {
        bleCommandBuffer += ch;
      }
    }
  }
};

// ========================================
// FUNCIONES DE COMUNICACIÓN
// ========================================
void sendBLEResponse(String response) {
  if (deviceConnected && pResponseCharacteristic != NULL) {
    response += "\n";
    pResponseCharacteristic->setValue(response.c_str());
    pResponseCharacteristic->notify();
    delay(10); // Pequeño delay para asegurar la transmisión
  }
}

void sendResponse(String response, bool viaBLE = false) {
  if (viaBLE) {
    sendBLEResponse(response);
  } else {
    Serial.println(response);
  }
}

// ========================================
// SETUP
// ========================================
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("========================================");
  Serial.println("HUSB238 USB-C PD Controller with BLE");
  Serial.println("UNIT Electronics - DevLab");
  Serial.println("========================================");

  // Inicializar I2C
  Wire.begin(I2C_SDA, I2C_SCL);
  
  // Inicializar HUSB238
  Serial.print("Inicializando HUSB238... ");
  if (husb238.begin(HUSB238_I2CADDR_DEFAULT, &Wire)) {
    Serial.println("OK");
  } else {
    Serial.println("ERROR");
    Serial.println("No se pudo encontrar el HUSB238, verifica el cableado");
    while (1) delay(100);
  }

  // Inicializar BLE
  Serial.print("Inicializando BLE... ");
  
  // Crear dispositivo BLE
  BLEDevice::init("HUSB238");
  
  // Crear servidor BLE
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Crear servicio BLE con BLEUUID explícito
  BLEService *pService = pServer->createService(BLEUUID(SERVICE_UUID));

  // Crear característica de comandos (Write)
  pCommandCharacteristic = pService->createCharacteristic(
                           BLEUUID(COMMAND_CHAR_UUID),
                           BLECharacteristic::PROPERTY_WRITE
                         );
  pCommandCharacteristic->setCallbacks(new CommandCallbacks());

  // Crear característica de respuestas (Read/Notify)
  pResponseCharacteristic = pService->createCharacteristic(
                         BLEUUID(RESPONSE_CHAR_UUID),
                         BLECharacteristic::PROPERTY_READ |
                         BLECharacteristic::PROPERTY_NOTIFY
                       );

  // Agregar descriptor BLE2902 para notificaciones
  pResponseCharacteristic->addDescriptor(new BLE2902());

  // Establecer valores iniciales
  pCommandCharacteristic->setValue("");
  pResponseCharacteristic->setValue("HUSB238_READY");

  // Iniciar servicio
  pService->start();

  // Configurar y iniciar advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(BLEUUID(SERVICE_UUID));
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);
  BLEDevice::startAdvertising();
  
  Serial.println("OK");
  Serial.println("========================================");
  Serial.println("Sistema listo!");
  Serial.println("BLE: Esperando conexiones...");
  Serial.println("Serial: Listo para recibir comandos SCPI");
  Serial.println("========================================");
}

// ========================================
// LOOP
// ========================================
void loop() {
  // Manejar comandos desde Serial
  while (Serial.available()) {
    char ch = Serial.read();
    if (ch == '\n') {
      handleSCPI(cmd, false); // false = respuesta via Serial
      cmd = "";
    } else {
      cmd += ch;
    }
  }

  // Manejar reconexión BLE
  if (!deviceConnected && oldDeviceConnected) {
    delay(500);
    pServer->startAdvertising();
    Serial.println("BLE: Reiniciando advertising");
    oldDeviceConnected = deviceConnected;
  }
  
  if (deviceConnected && !oldDeviceConnected) {
    oldDeviceConnected = deviceConnected;
  }
}

// ========================================
// MANEJADOR DE COMANDOS SCPI
// ========================================
void handleSCPI(String c, bool viaBLE) {
  c.trim();
  c.toUpperCase();

  // *IDN? - Identificación
  if (c == "*IDN?") {
    sendResponse("UNIT-DEVLAB,HUSB238,USBPD,1.0", viaBLE);
  }

  // STAT? - Estado de conexión
  else if (c == "STAT?") {
    sendResponse(husb238.isAttached() ? "ATTACHED" : "UNATTACHED", viaBLE);
  }

  // PD:LIST? - Lista de voltajes disponibles
  else if (c == "PD:LIST?") {
    HUSB238_PDSelection voltages[] = {PD_SRC_5V, PD_SRC_9V, PD_SRC_12V, PD_SRC_15V, PD_SRC_18V, PD_SRC_20V};
    int voltageValues[] = {5, 9, 12, 15, 18, 20};
    String response = "";
    
    for (int i = 0; i < 6; i++) {
      if (husb238.isVoltageDetected(voltages[i])) {
        response += String(voltageValues[i]) + "V ";
      }
    }
    sendResponse(response, viaBLE);
  }

  // PD:GET? - Voltaje actual
  else if (c == "PD:GET?") {
    String response = "PD=" + String(husb238.getPDSrcVoltage());
    sendResponse(response, viaBLE);
  }

  // PD:SET<voltage> - Establecer voltaje
  else if (c.startsWith("PD:SET")) {
    int v = c.substring(6).toInt();
    HUSB238_PDSelection sel;

    switch (v) {
      case 5:  sel = PD_SRC_5V; break;
      case 9:  sel = PD_SRC_9V; break;
      case 12: sel = PD_SRC_12V; break;
      case 15: sel = PD_SRC_15V; break;
      case 18: sel = PD_SRC_18V; break;
      case 20: sel = PD_SRC_20V; break;
      default:
        sendResponse("ERR:INVALID_VOLTAGE", viaBLE);
        return;
    }

    if (husb238.isVoltageDetected(sel)) {
      husb238.selectPD(sel);
      husb238.requestPD();
      sendResponse("OK:SET " + String(v) + "V", viaBLE);
    } else {
      sendResponse("ERR:UNAVAILABLE", viaBLE);
    }
  }

  // PD:SWEEP - Sweep de voltajes
  else if (c == "PD:SWEEP") {
    HUSB238_PDSelection levels[] = {
      PD_SRC_5V, PD_SRC_9V, PD_SRC_12V,
      PD_SRC_15V, PD_SRC_18V, PD_SRC_20V
    };

    for (int i = 0; i < 6; i++) {
      if (husb238.isVoltageDetected(levels[i])) {
        husb238.selectPD(levels[i]);
        husb238.requestPD();
        String msg = "SWEEP " + String((i+1)*5) + "V";
        sendResponse(msg, viaBLE);
        delay(1500);
      }
    }
    sendResponse("SWEEP DONE", viaBLE);
  }

  // CURR:GET? - Corriente actual
  else if (c == "CURR:GET?") {
    HUSB238_CurrentSetting curr = husb238.getPDSrcCurrent();
    String response = "CURR=" + getCurrentString(curr);
    sendResponse(response, viaBLE);
  }

  // CURR:MAX?<voltage> - Corriente máxima para voltaje
  else if (c.startsWith("CURR:MAX?")) {
    int v = c.substring(9).toInt();
    HUSB238_PDSelection sel;

    switch (v) {
      case 5:  sel = PD_SRC_5V; break;
      case 9:  sel = PD_SRC_9V; break;
      case 12: sel = PD_SRC_12V; break;
      case 15: sel = PD_SRC_15V; break;
      case 18: sel = PD_SRC_18V; break;
      case 20: sel = PD_SRC_20V; break;
      default:
        sendResponse("ERR:INVALID_VOLTAGE", viaBLE);
        return;
    }

    if (husb238.isVoltageDetected(sel)) {
      HUSB238_CurrentSetting curr = husb238.currentDetected(sel);
      String response = "MAX_CURR@" + String(v) + "V=" + getCurrentString(curr);
      sendResponse(response, viaBLE);
    } else {
      sendResponse("ERR:UNAVAILABLE", viaBLE);
    }
  }

  // Comando desconocido
  else {
    sendResponse("ERR:UNKNOWN_CMD", viaBLE);
  }
}

// ========================================
// FUNCIONES AUXILIARES
// ========================================
String getCurrentString(HUSB238_CurrentSetting curr) {
  switch (curr) {
    case CURRENT_0_5_A:  return "0.5A";
    case CURRENT_0_7_A:  return "0.7A";
    case CURRENT_1_0_A:  return "1.0A";
    case CURRENT_1_25_A: return "1.25A";
    case CURRENT_1_5_A:  return "1.5A";
    case CURRENT_1_75_A: return "1.75A";
    case CURRENT_2_0_A:  return "2.0A";
    case CURRENT_2_25_A: return "2.25A";
    case CURRENT_2_50_A: return "2.50A";
    case CURRENT_2_75_A: return "2.75A";
    case CURRENT_3_0_A:  return "3.0A";
    case CURRENT_3_25_A: return "3.25A";
    case CURRENT_3_5_A:  return "3.5A";
    case CURRENT_4_0_A:  return "4.0A";
    case CURRENT_4_5_A:  return "4.5A";
    case CURRENT_5_0_A:  return "5.0A";
    default: return "UNKNOWN";
  }
}
