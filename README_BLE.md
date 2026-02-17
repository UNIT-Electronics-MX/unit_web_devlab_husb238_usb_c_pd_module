# HUSB238 USB-C PD Controller - Web Bluetooth

[![Deploy to GitHub Pages](https://github.com/UNIT-Electronics-MX/unit_web_devlab_husb238_usb_c_pd_module/actions/workflows/deploy-gh-pages.yml/badge.svg)](https://github.com/UNIT-Electronics-MX/unit_web_devlab_husb238_usb_c_pd_module/actions/workflows/deploy-gh-pages.yml)
[![GitHub Pages](https://img.shields.io/badge/demo-live-brightgreen)](https://unit-electronics-mx.github.io/unit_web_devlab_husb238_usb_c_pd_module/index-husb238.html)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

Control del módulo HUSB238 USB-C Power Delivery mediante una aplicación web usando Bluetooth Low Energy (BLE).

## 🌐 Demo en Vivo

**Prueba la aplicación ahora**: [https://unit-electronics-mx.github.io/unit_web_devlab_husb238_usb_c_pd_module/index-husb238.html](https://unit-electronics-mx.github.io/unit_web_devlab_husb238_usb_c_pd_module/index-husb238.html)

> ⚠️ **Requisitos**: Navegador Chrome/Edge y Bluetooth habilitado. Necesitas tener el hardware ESP32 + HUSB238 programado y encendido.

## 📋 Descripción

Esta aplicación permite controlar el módulo HUSB238 para negociar diferentes voltajes USB-C Power Delivery (5V, 9V, 12V, 15V, 18V, 20V) desde un navegador web compatible con Web Bluetooth API.

## 🔧 Hardware Requerido

- **Microcontrolador ESP32** (ESP32-C3, ESP32-S3 o similar)
- **Módulo HUSB238** USB-C PD
- Conexión I2C entre ESP32 y HUSB238:
  - SDA → GPIO 6
  - SCL → GPIO 7

## 📦 Bibliotecas Necesarias

Para el firmware Arduino necesitas instalar:

1. **Adafruit_HUSB238** - Control del módulo HUSB238
   ```
   Gestor de bibliotecas → Buscar "Adafruit HUSB238"
   ```

2. **ESP32 BLE Arduino** - Ya incluida en el core ESP32

## 🚀 Instalación

### 1. Cargar el Firmware

1. Abre Arduino IDE
2. Selecciona tu placa ESP32 (Herramientas → Placa)
3. Abre el archivo `husb238_ble.ino`
4. Verifica y carga el sketch en tu ESP32

### 2. Verificar Conexión

Abre el Monitor Serial (115200 baudios) y deberías ver:

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

### 3. Abrir la Aplicación Web

**Opción A - GitHub Pages (Recomendado):**
```
Abre: https://unit-electronics-mx.github.io/unit_web_devlab_husb238_usb_c_pd_module/index-husb238.html
```

**Opción B - Local (archivo):**
1. Navega a la carpeta `docs/`
2. Abre el archivo `index-husb238.html` en un navegador compatible:
   - **Chrome** (Desktop/Android)
   - **Edge** (Desktop/Android)
   - **Opera** (Desktop/Android)
   
   ⚠️ **Nota**: Safari y Firefox no soportan Web Bluetooth actualmente.

**Opción C - Servidor Local:**
```bash
cd docs/
python -m http.server 8000
# Abre: http://localhost:8000/index-husb238.html
```

## 📱 Uso de la Aplicación Web

### Conectar al Dispositivo

1. Haz clic en el botón **"Conectar BLE"**
2. En el diálogo, selecciona el dispositivo **"HUSB238"**
3. Espera a que se establezca la conexión (indicador verde)

### Panel de Estado

- **Conexión USB-C**: Muestra si hay un dispositivo PD conectado
- **Voltaje Actual**: Voltaje negociado actualmente
- **Corriente Actual**: Corriente disponible

### Seleccionar Voltaje

1. Haz clic en **"Escanear Voltajes Disponibles"**
2. Las tarjetas de voltaje se actualizarán mostrando cuáles están disponibles (✅)
3. Haz clic en cualquier voltaje disponible para seleccionarlo
4. El sistema automáticamente negociará el nuevo voltaje

### Funciones Adicionales

- **Sweep**: Recorre automáticamente todos los voltajes disponibles
- **Actualizar Estado**: Refresca la información del dispositivo
- **Registro de Actividad**: Muestra todas las comunicaciones en tiempo real

## 🔌 Comandos SCPI (Serial)

También puedes controlar el dispositivo mediante comandos SCPI por el puerto serial:

| Comando | Descripción | Ejemplo de Respuesta |
|---------|-------------|---------------------|
| `*IDN?` | Identificación del dispositivo | `UNIT-DEVLAB,HUSB238,USBPD,1.0` |
| `STAT?` | Estado de conexión USB-C | `ATTACHED` / `UNATTACHED` |
| `PD:LIST?` | Voltajes disponibles | `5V 9V 12V 15V 20V` |
| `PD:GET?` | Voltaje actual | `PD=12` |
| `PD:SET<v>` | Establecer voltaje | `OK:SET 12V` |
| `PD:SWEEP` | Sweep todos los voltajes | `SWEEP 5V` ... `SWEEP DONE` |
| `CURR:GET?` | Corriente actual | `CURR=3.0A` |
| `CURR:MAX?<v>` | Corriente máxima @ voltaje | `MAX_CURR@12V=3.0A` |

### Ejemplos de Uso Serial

```
> *IDN?
< UNIT-DEVLAB,HUSB238,USBPD,1.0

> STAT?
< ATTACHED

> PD:LIST?
< 5V 9V 12V 15V 20V 

> PD:SET12
< OK:SET 12V

> CURR:MAX?12
< MAX_CURR@12V=3.0A
```

## 🏗️ Arquitectura del Sistema

```
┌─────────────────────┐
│  Navegador Web      │
│  (Chrome/Edge)      │
│                     │
│  index-husb238.html │
│  script-husb238.js  │
└──────────┬──────────┘
           │
           │ Web Bluetooth API
           │
┌──────────▼──────────┐
│  ESP32 con BLE      │
│                     │
│  husb238_ble.ino    │
│  ├─ BLE Server      │
│  ├─ SCPI Parser     │
│  └─ I2C Driver      │
└──────────┬──────────┘
           │
           │ I2C (SDA/SCL)
           │
┌──────────▼──────────┐
│  HUSB238 Module     │
│  USB-C PD IC        │
└─────────────────────┘
```

## 🔐 UUIDs Bluetooth

- **Servicio**: `4fafc201-1fb5-459e-8fcc-c5c9c331914b`
- **Comandos** (Write): `6d68efe5-04b6-4a85-abc4-c2670b7bf7fd`
- **Respuestas** (Read/Notify): `f27b53ad-c63d-49a0-8c0f-9f297e6cc520`

## 🐛 Solución de Problemas

### No aparece el dispositivo en el navegador

1. Verifica que el ESP32 esté encendido y ejecutando el firmware
2. Asegúrate de que el Bluetooth esté habilitado en tu sistema
3. Refresca la página y vuelve a intentar

### Error "Web Bluetooth not supported"

- Asegúrate de usar Chrome, Edge u Opera
- Safari y Firefox no soportan Web Bluetooth
- En dispositivos móviles, usa Chrome o Edge

### No se detectan voltajes

1. Verifica que haya un cargador USB-C PD conectado al HUSB238
2. Haz clic en "Actualizar Estado" para verificar la conexión
3. El estado debe mostrar "CONECTADO"

### El voltaje no cambia

1. Asegúrate de que el voltaje esté marcado como disponible (✅)
2. Algunos cargadores no soportan todos los voltajes
3. Verifica el registro de actividad para mensajes de error

## 📝 Notas Técnicas

- La comunicación BLE tiene un límite de ~20 bytes por paquete
- Se añade un pequeño delay entre comandos para estabilidad
- El sistema soporta control simultáneo por BLE y Serial
- Las respuestas se notifican automáticamente vía BLE

## 🤝 Contribuciones

Este proyecto es parte de UNIT Electronics DevLab. Si encuentras bugs o tienes sugerencias, por favor:

1. Documenta el problema en detalle
2. Incluye logs del Monitor Serial y del Registro de Actividad web
3. Especifica tu hardware (modelo ESP32, versión firmware, etc.)

## 📄 Licencia

Desarrollado por UNIT Electronics
Compatible con productos de la línea DevLab

---

**Versión**: 1.0  
**Fecha**: 2025  
**Autor**: UNIT Electronics Team
