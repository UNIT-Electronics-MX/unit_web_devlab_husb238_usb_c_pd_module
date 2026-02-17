#!/bin/bash

echo "=== Diagnóstico de Bluetooth para Web BLE ==="
echo ""

# 1. Verificar servicio Bluetooth
echo "1. Estado del servicio Bluetooth:"
systemctl status bluetooth | grep -E "Active:|Loaded:" || echo "   ⚠️  Servicio bluetooth no encontrado"
echo ""

# 2. Verificar adaptador Bluetooth
echo "2. Adaptadores Bluetooth disponibles:"
if command -v bluetoothctl &> /dev/null; then
    bluetoothctl list || echo "   ⚠️  No se detectaron adaptadores"
else
    echo "   ⚠️  bluetoothctl no está instalado"
fi
echo ""

# 3. Verificar estado del adaptador
echo "3. Estado del adaptador:"
if command -v hciconfig &> /dev/null; then
    hciconfig -a | head -5 || echo "   ⚠️  No se puede verificar estado"
else
    echo "   ℹ️  hciconfig no disponible (usa bluetoothctl)"
fi
echo ""

# 4. Escanear dispositivos BLE
echo "4. Escaneando dispositivos BLE cercanos (10 segundos)..."
echo "   Buscando 'HUSB238'..."
if command -v timeout &> /dev/null; then
    timeout 10s bluetoothctl scan on 2>&1 | grep -i "HUSB238\|Device" || echo "   ⚠️  HUSB238 no encontrado en el escaneo"
else
    echo "   ℹ️  Escaneo manual requerido"
fi
echo ""

# 5. Verificar Chrome
echo "5. Navegador Chrome/Chromium:"
if command -v google-chrome &> /dev/null; then
    google-chrome --version
elif command -v chromium &> /dev/null; then
    chromium --version
elif command -v chromium-browser &> /dev/null; then
    chromium-browser --version
else
    echo "   ⚠️  Chrome/Chromium no encontrado"
fi
echo ""

echo "=== Soluciones rápidas ==="
echo ""
echo "Si el servicio está inactivo:"
echo "  sudo systemctl start bluetooth"
echo "  sudo systemctl enable bluetooth"
echo ""
echo "Si el adaptador está 'down':"
echo "  sudo hciconfig hci0 up"
echo ""
echo "Para habilitar Web Bluetooth en Chrome:"
echo "  1. Ir a chrome://flags"
echo "  2. Buscar 'Experimental Web Platform features'"
echo "  3. Activar y reiniciar"
echo ""
echo "URL de prueba:"
echo "  https://unit-electronics-mx.github.io/unit_web_devlab_husb238_usb_c_pd_module/test-ble.html"
