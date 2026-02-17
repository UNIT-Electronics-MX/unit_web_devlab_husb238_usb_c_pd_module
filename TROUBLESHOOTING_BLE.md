# Solución de Problemas - Web Bluetooth

## Problema: "No compatible devices found"

### 1. Verificar el ESP32

**En el Monitor Serial del Arduino IDE (115200 baud):**

Deberías ver algo como esto al iniciar:
```
========================================
HUSB238 USB-C PD Controller with BLE
UNIT Electronics - DevLab
========================================
Inicializando HUSB238... OK
Inicializando BLE... OK
========================================
Sistema listo!
BLE: Esperando conexiones...
Serial: Listo para recibir comandos SCPI
========================================
```

Si ves:
- `Inicializando HUSB238... ERROR` → Verifica el cableado I2C (SDA=GPIO6, SCL=GPIO7)
- No aparece nada → Verifica que el firmware esté cargado correctamente

### 2. Verificar el Navegador

**Requisitos:**
- **Chrome** 56+ o **Edge** 79+ (en Windows/Linux/macOS)
- **NO funciona en:** Firefox, Safari, navegadores móviles (excepto Android Chrome con flag)

**Habilitar Web Bluetooth (si es necesario):**

1. Ir a `chrome://flags/` 
2. Buscar "Web Bluetooth"
3. Activar "Experimental Web Platform features"
4. Reiniciar el navegador

**Verificar permisos:**
- En Chrome → Configuración → Privacidad y seguridad → Configuración de sitios → Bluetooth
- Asegúrate de que el sitio tenga permiso para usar Bluetooth

### 3. Verificar Bluetooth del Sistema

**Windows:**
```
- Configuración → Bluetooth y dispositivos
- Asegúrate de que Bluetooth esté ENCENDIDO
```

**Linux:**
```bash
# Verificar estado
systemctl status bluetooth

# Habilitar si está deshabilitado
sudo systemctl start bluetooth
sudo systemctl enable bluetooth

# Verificar adaptador
bluetoothctl
> power on
> scan on
```

**macOS:**
```
- Preferencias del Sistema → Bluetooth
- Asegúrate de que esté ACTIVADO
```

### 4. Prueba de Conexión Directa

**Paso 1:** Abrir el Monitor Serial (115200 baud)

**Paso 2:** Verificar que BLE esté transmitiendo

**Paso 3:** En la página web, abre la consola del navegador (F12) y verifica si hay errores

**Paso 4:** Prueba el comando de escaneo manual:

Abre la consola del navegador y ejecuta:
```javascript
navigator.bluetooth.requestDevice({
  filters: [{ name: 'HUSB238' }],
  optionalServices: ['4fafc201-1fb5-459e-8fcc-c5c9c331914b']
})
.then(device => console.log('✅ Encontrado:', device.name))
.catch(error => console.log('❌ Error:', error));
```

### 5. Verificar Alcance y Señal

- **Distancia:** Mantén el ESP32 a menos de 5 metros del computador
- **Interferencias:** Aleja el ESP32 de:
  - Routers WiFi
  - Hornos microondas
  - Otros dispositivos Bluetooth
- **Antena:** Si tu ESP32 tiene antena externa, asegúrate de que esté conectada

### 6. Reinicio Completo

1. **Desconectar el ESP32** del USB
2. **Cerrar todas las pestañas** del navegador relacionadas con Web Bluetooth
3. **Reiniciar el navegador**
4. **Conectar el ESP32** nuevamente
5. **Esperar 5 segundos** a que inicie BLE
6. **Abrir la página** de test: https://unit-electronics-mx.github.io/unit_web_devlab_husb238_usb_c_pd_module/test-ble.html
7. **Hacer clic en "Conectar"**

### 7. Prueba con otro Dispositivo BLE (Opcional)

Si tienes otro dispositivo BLE (como un teléfono), puedes verificar que el ESP32 esté transmitiendo usando apps como:
- **Android:** nRF Connect
- **iOS:** LightBlue Explorer

Busca un dispositivo llamado **"HUSB238"** con el servicio UUID `4fafc201-1fb5-459e-8fcc-c5c9c331914b`

### 8. Mensajes de Error Comunes

| Error | Causa | Solución |
|-------|-------|----------|
| `NotFoundError: User cancelled` | Usuario canceló el diálogo | Normal - intenta de nuevo |
| `NotFoundError: No Bluetooth adapter` | Adaptador BT deshabilitado | Habilita Bluetooth en el sistema |
| `SecurityError` | Página no es HTTPS | Usa GitHub Pages (https://) |
| `NotSupportedError` | Navegador incompatible | Usa Chrome/Edge |
| `NetworkError` | ESP32 fuera de alcance | Acerca el dispositivo |

### 9. Logs de Depuración

**En el Monitor Serial:**
```
BLE: Cliente conectado      → Conexión establecida ✅
BLE: Cliente desconectado   → Dispositivo se desconectó
BLE: Reiniciando advertising → Esperando nueva conexión
```

**En la Consola del Navegador (F12):**
```
🔍 Buscando HUSB238...
✅ Dispositivo encontrado: HUSB238
🔗 Conectado al GATT
📡 Servicio obtenido
✅ Características obtenidas
🔔 Notificaciones habilitadas
🎉 ¡Conexión establecida!
```

### 10. Si Nada Funciona

**Verifica la placa ESP32:**
- Algunas placas ESP32 baratas tienen problemas con BLE
- Verifica que tu placa sea compatible con BLE (ESP32, ESP32-C3, ESP32-S3)
- El **ESP32-S2** NO tiene BLE (solo WiFi)
- El **ESP8266** NO tiene BLE

**Prueba el firmware básico:**
```cpp
#include <BLEDevice.h>

void setup() {
  Serial.begin(115200);
  BLEDevice::init("TEST");
  BLEDevice::startAdvertising();
  Serial.println("BLE Test Ready");
}

void loop() {
  delay(1000);
}
```

Si este código básico funciona, el problema está en el firmware HUSB238.

---

## Contacto

Si después de seguir estos pasos aún tienes problemas:
1. Anota el modelo EXACTO de tu ESP32
2. Copia los mensajes del Monitor Serial
3. Copia los errores de la consola del navegador
4. Abre un issue en GitHub con toda esta información
