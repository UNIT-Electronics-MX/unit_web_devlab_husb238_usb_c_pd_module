# 🚀 Inicio Rápido - HUSB238 Web Bluetooth

## 📦 ¿Qué tengo?

Has recibido una **aplicación web completa** para controlar el módulo HUSB238 USB-C Power Delivery mediante Bluetooth desde tu navegador.

## 📁 Archivos Creados

### 🌐 Aplicación Web (carpeta `docs/`)
- **index-husb238.html** - Aplicación principal (¡empieza aquí!)
- **script-husb238.js** - Lógica de control BLE
- **test-ble.html** - Página de prueba simple
- **diagrama.html** - Explicación visual del sistema

### 🔧 Firmware (carpeta `husb238/`)
- **husb238_ble.ino** - Código para ESP32 con soporte BLE

### 📚 Documentación
- **README_BLE.md** - Guía completa detallada
- **RESUMEN.md** - Resumen de la implementación
- **INICIO_RAPIDO.md** - Este archivo

## ⚡ Empezar en 5 Minutos

### 1️⃣ Prepara el Hardware (2 min)

```
Conecta:
ESP32 GPIO6  → HUSB238 SDA
ESP32 GPIO7  → HUSB238 SCL
ESP32 GND    → HUSB238 GND
ESP32 3.3V   → HUSB238 VCC
```

### 2️⃣ Carga el Firmware (2 min)

1. Abre **Arduino IDE**
2. Instala librería: **Adafruit_HUSB238**
3. Abre: `husb238/husb238_ble.ino`
4. Selecciona tu placa ESP32
5. Sube el código ⬆️

### 3️⃣ Prueba la Conexión (30 seg)

Abre **Monitor Serial** (115200 baudios)

Deberías ver:
```
========================================
HUSB238 USB-C PD Controller with BLE
========================================
Inicializando HUSB238... OK
Inicializando BLE... OK
========================================
Sistema listo!
BLE: Esperando conexiones...
========================================
```

✅ Si ves esto, ¡estás listo!
❌ Si no, revisa las conexiones

### 4️⃣ Abre la App Web (30 seg)

**Opción A - Directo (más fácil):**
```
1. Ve a la carpeta: docs/
2. Doble click en: index-husb238.html
3. Se abrirá en tu navegador
```

**Opción B - Servidor local (recomendado):**
```bash
cd docs/
python -m http.server 8000
# Abre: http://localhost:8000/index-husb238.html
```

**Opción C - Prueba rápida:**
```
Abre: docs/test-ble.html
```

### 5️⃣ Conecta y Usa (1 min)

1. En la página web, click **"Conectar BLE"**
2. Selecciona el dispositivo **"HUSB238"**
3. Espera el indicador verde ✅
4. Click **"Escanear Voltajes Disponibles"**
5. Click en el voltaje que quieras (ej: **12V**)

¡Listo! 🎉

## 🎯 ¿Qué Puedo Hacer?

### Controles Disponibles:

| Acción | Descripción |
|--------|-------------|
| 🔍 **Escanear Voltajes** | Ve qué voltajes soporta tu cargador |
| ⚡ **Seleccionar Voltaje** | Click en 5V, 9V, 12V, 15V, 18V o 20V |
| 🔄 **Actualizar Estado** | Refresca la información |
| ⚡ **Sweep** | Prueba todos los voltajes automáticamente |
| 📊 **Ver Corriente** | Consulta la corriente disponible |

### Información que Ves:

- ✅ **Estado USB-C**: CONECTADO / DESCONECTADO
- ⚡ **Voltaje Actual**: El voltaje negociado
- 🔋 **Corriente**: Cuánta corriente está disponible
- 📝 **Log**: Todos los comandos y respuestas

## 🎨 Interfaz

```
┌─────────────────────────────────────┐
│  🔌 HUSB238 - USB-C PD Controller   │
│  Estado: ● CONECTADO                │
│  [Conectar BLE] [Desconectar]       │
├─────────────────────────────────────┤
│  Estado del Dispositivo             │
│  ┌───────┬───────┬───────┐          │
│  │ USB-C │ Volt. │ Corr. │          │
│  │  ✅   │  12V  │ 3.0A  │          │
│  └───────┴───────┴───────┘          │
├─────────────────────────────────────┤
│  Voltajes Disponibles               │
│  [5V] [9V] [12V✓] [15V] [18V] [20V]│
│  [🔍 Escanear] [⚡ Sweep]           │
├─────────────────────────────────────┤
│  Registro de Actividad              │
│  [12:30] 📤 CMD: PD:SET12           │
│  [12:30] 📥 OK:SET 12V              │
│  [12:30] 📥 CURR=3.0A               │
└─────────────────────────────────────┘
```

## 🌐 Navegadores Compatible

✅ **Chrome** (PC/Mac/Android)
✅ **Edge** (PC/Mac/Android)
✅ **Opera** (PC/Mac/Android)

❌ Safari (no soporta Web Bluetooth)
❌ Firefox (no soporta Web Bluetooth)

## 📱 Dispositivos Compatibles

✅ Computadoras Windows/Mac/Linux
✅ Laptops con Bluetooth
✅ Tablets Android con Bluetooth
✅ Smartphones Android con Bluetooth

❌ iPhone/iPad (Safari no soporta Web Bluetooth)

## 🔧 Troubleshooting Rápido

### ❌ No aparece el dispositivo

**Solución:**
```
1. Verifica que el ESP32 esté encendido
2. Abre Monitor Serial, debe decir "BLE: Esperando conexiones..."
3. Activa Bluetooth en tu PC/móvil
4. Refresca la página web
```

### ❌ "Web Bluetooth not supported"

**Solución:**
```
1. Usa Chrome, Edge u Opera
2. Verifica que sea versión reciente
3. En Android, usa Chrome
4. NO uses Safari ni Firefox
```

### ❌ No detecta voltajes

**Solución:**
```
1. Conecta un cargador USB-C PD al HUSB238
2. Debe ser un cargador que soporte Power Delivery
3. Click en "Actualizar Estado"
4. El estado debe decir "CONECTADO"
```

### ❌ No cambia el voltaje

**Solución:**
```
1. Verifica que el voltaje tenga ✅ (disponible)
2. Algunos cargadores no soportan todos los voltajes
3. Mira el log de actividad para errores
```

## 🎓 Archivos de Ayuda

Si necesitas más información:

- 📖 **README_BLE.md** - Guía completa y detallada
- 📊 **diagrama.html** - Explicación visual del sistema
- 🧪 **test-ble.html** - Para probar conectividad
- 📝 **RESUMEN.md** - Resumen técnico completo

## 💡 Comandos de Prueba

Si abres `test-ble.html`, puedes probar estos comandos:

```
*IDN?         → Identificación
STAT?         → Estado USB-C
PD:LIST?      → Listar voltajes
PD:GET?       → Voltaje actual
PD:SET12      → Poner 12V
CURR:GET?     → Corriente actual
PD:SWEEP      → Probar todos
```

## 🎉 ¡Ya Está!

Ahora tienes:
- ✅ Control inalámbrico del HUSB238
- ✅ Interfaz web profesional
- ✅ Monitoreo en tiempo real
- ✅ Sin necesidad de apps
- ✅ Multi-plataforma
- ✅ Código abierto

## 📞 ¿Problemas?

1. Revisa **README_BLE.md** para guía detallada
2. Verifica Monitor Serial para logs del ESP32
3. Abre Console del navegador (F12) para errores web
4. Usa **test-ble.html** para debugging simple

---

**¡Disfruta tu sistema HUSB238 Web Bluetooth!** 🚀

*Desarrollado por UNIT Electronics - DevLab*
