# HUSB238 USB-C PD Controller - Web Bluetooth

[![Deploy to GitHub Pages](https://github.com/UNIT-Electronics-MX/unit_web_devlab_husb238_usb_c_pd_module/actions/workflows/deploy-gh-pages.yml/badge.svg)](https://github.com/UNIT-Electronics-MX/unit_web_devlab_husb238_usb_c_pd_module/actions/workflows/deploy-gh-pages.yml)
[![GitHub Pages](https://img.shields.io/badge/demo-live-brightgreen)](https://unit-electronics-mx.github.io/unit_web_devlab_husb238_usb_c_pd_module/)

Web-based control for the HUSB238 USB-C Power Delivery module via Bluetooth Low Energy.

## Live Demo

**Try it now**: [https://unit-electronics-mx.github.io/unit_web_devlab_husb238_usb_c_pd_module/](https://unit-electronics-mx.github.io/unit_web_devlab_husb238_usb_c_pd_module/)

Requirements: Chrome/Edge browser with Bluetooth enabled. ESP32 + HUSB238 hardware must be programmed and powered.

## Features

- Control USB-C PD voltage negotiation (5V, 9V, 12V, 15V, 18V, 20V)
- Read current and voltage status
- Monitor connection state
- Automatic voltage sweep
- Web-based interface (no installation required)

## Hardware

- ESP32-H2 (Pulsar H2) or compatible ESP32 board
- HUSB238 USB-C PD module
- I2C connection:
  - SDA: GPIO12
  - SCL: GPIO22

## Quick Start

### 1. Flash Firmware

1. Open Arduino IDE
2. Install Adafruit_HUSB238 library
3. Open `husb238/husb238_ble.ino`
4. Select your ESP32 board
5. Upload sketch

### 2. Connect

1. Open the [web application](https://unit-electronics-mx.github.io/unit_web_devlab_husb238_usb_c_pd_module/)
2. Click "Connect to HUSB238"
3. Select "HUSB238" from Bluetooth devices
4. Control voltages from the web interface

## SCPI Commands

The firmware supports SCPI-like commands via BLE or Serial:

```
*IDN?              - Device identification
STAT?              - USB-C connection status
PD:LIST?           - List available voltages
PD:GET?            - Get current voltage
PD:SET<voltage>    - Set voltage (5, 9, 12, 15, 18, 20)
PD:SWEEP           - Sweep all available voltages
CURR:GET?          - Get current
CURR:MAX?<voltage> - Get max current for voltage
```

## Project Structure

```
├── husb238/
│   └── husb238_ble.ino    # ESP32 firmware
├── docs/
│   ├── index.html         # Web application
│   └── script-husb238.js  # BLE logic
└── .github/
    └── workflows/
        └── deploy-gh-pages.yml  # Auto-deployment
```

## Development

Local testing:

```bash
cd docs
python3 -m http.server 8000
```

Open `http://localhost:8000` in Chrome/Edge.

## Troubleshooting

**Device not found**: Ensure ESP32 is powered and BLE is initialized (check serial monitor).

**Service not found**: Clear browser BLE cache at `chrome://bluetooth-internals` and forget the device.

**Connection fails**: Verify I2C pins match your hardware configuration.

## License

MIT License - UNIT Electronics
