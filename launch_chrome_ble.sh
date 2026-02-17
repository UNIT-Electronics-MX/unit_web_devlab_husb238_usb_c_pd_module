#!/bin/bash

echo "=== Lanzador de Chrome con Web Bluetooth para Linux ==="
echo ""
echo "Este script configura Chrome para Web Bluetooth en Linux"
echo ""

# Cerrar todas las instancias de Chrome
echo "1. Cerrando instancias de Chrome existentes..."
killall chrome 2>/dev/null
killall google-chrome 2>/dev/null
killall chromium 2>/dev/null
killall chromium-browser 2>/dev/null
sleep 2

# Detectar qué navegador está instalado
if command -v google-chrome &> /dev/null; then
    CHROME_CMD="google-chrome"
elif command -v chromium &> /dev/null; then
    CHROME_CMD="chromium"
elif command -v chromium-browser &> /dev/null; then
    CHROME_CMD="chromium-browser"
else
    echo "❌ Error: No se encontró Chrome/Chromium instalado"
    exit 1
fi

echo "✅ Usando: $CHROME_CMD"
echo ""

# URL de la aplicación
URL="https://unit-electronics-mx.github.io/unit_web_devlab_husb238_usb_c_pd_module/test-ble.html"

echo "2. Lanzando Chrome con flags de Web Bluetooth habilitados..."
echo ""
echo "Flags activados:"
echo "  --enable-features=WebBluetooth"
echo "  --enable-experimental-web-platform-features"
echo "  --enable-web-bluetooth-new-permissions-backend"
echo ""

# Lanzar Chrome con los flags necesarios
$CHROME_CMD \
  --enable-features=WebBluetooth \
  --enable-experimental-web-platform-features \
  --enable-web-bluetooth-new-permissions-backend \
  --new-window \
  "$URL" &

echo "✅ Chrome lanzado con Web Bluetooth habilitado"
echo ""
echo "Si aún no funciona, intenta:"
echo "1. Ve a chrome://flags"
echo "2. Busca 'Web Bluetooth'"
echo "3. Activa todas las opciones relacionadas"
echo "4. Reinicia Chrome"
echo ""
echo "Nota: En Linux, es posible que necesites ejecutar Chrome como superusuario"
echo "para acceso completo a Bluetooth (NO RECOMENDADO para uso regular)"
