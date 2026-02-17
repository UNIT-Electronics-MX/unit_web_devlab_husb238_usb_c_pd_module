# HUSB238 Web Bluetooth - Aplicaciones Web

Esta carpeta contiene las aplicaciones web para controlar el módulo HUSB238 USB-C Power Delivery via Bluetooth.

## 🌐 Demo en Vivo

La aplicación está desplegada automáticamente en GitHub Pages:

**URL Principal**: `https://unit-electronics-mx.github.io/unit_web_devlab_husb238_usb_c_pd_module/`

### Aplicaciones Disponibles:

- **[HUSB238 Control](index-husb238.html)** - Aplicación principal para control del HUSB238
- **[Test BLE](test-ble.html)** - Página de prueba rápida para debugging
- **[Diagrama del Sistema](diagrama.html)** - Explicación visual del sistema
- **[Pulsar H2 Reference](index.html)** - Referencia de implementación Pulsar H2

## 📱 Uso

1. Abre la aplicación en Chrome, Edge u Opera (navegadores compatibles con Web Bluetooth)
2. Asegúrate de tener Bluetooth habilitado en tu dispositivo
3. Haz clic en "Conectar BLE"
4. Selecciona el dispositivo "HUSB238"
5. ¡Listo para usar!

## 🔧 Desarrollo Local

Para probar localmente:

```bash
# Opción 1: Python
cd docs/
python -m http.server 8000
# Abre: http://localhost:8000

# Opción 2: Node.js
cd docs/
npx http-server
# Abre: http://localhost:8080

# Opción 3: PHP
cd docs/
php -S localhost:8000
# Abre: http://localhost:8000
```

## 🚀 Despliegue Automático

Cada vez que se hace push a la rama `main` con cambios en esta carpeta, GitHub Actions automáticamente despliega la nueva versión a GitHub Pages.

### Ver el estado del deployment:

1. Ve a la pestaña "Actions" en el repositorio
2. Busca el workflow "Deploy to GitHub Pages"
3. Verifica que esté en verde ✅

## 📁 Estructura de Archivos

```
docs/
├── index-husb238.html      # Aplicación principal HUSB238
├── script-husb238.js       # Lógica de control BLE
├── test-ble.html           # Página de prueba
├── diagrama.html           # Diagrama visual
├── index.html              # Pulsar H2 (referencia)
├── script-pulsar.js        # Pulsar H2 script
├── bluetooth-icon.svg      # Icono BLE
└── .nojekyll               # Desactiva procesamiento Jekyll
```

## 🔐 Seguridad

- Las aplicaciones web solo funcionan con HTTPS o localhost
- Web Bluetooth requiere interacción del usuario (no puede conectar automáticamente)
- Solo dispositivos autorizados pueden conectarse

## 📝 Notas

- **Compatibilidad**: Chrome, Edge, Opera (no Safari, no Firefox)
- **Plataformas**: Windows, macOS, Linux, Android
- **Requisitos**: Bluetooth habilitado
- **Conexión**: Segura via BLE GATT

---

**Desarrollado por**: UNIT Electronics  
**Licencia**: Ver archivo LICENSE en la raíz del proyecto
