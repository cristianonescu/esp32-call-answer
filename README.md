# ESP32 Call Answer/Decline

**Physical call buttons for your phone** using ESP32 as HFP Hands-Free device.

## Target Users
- Old people
- Kids
- People that cannot use touchscreens

## Features
# ESP32 Hands-Free Profile (HFP) client for call control buttons. Answer/hangup incoming calls via physical buttons on both Android & iPhone. Pure ESP-IDF Classic Bluetooth implementation.
- 📞 **Answer GPIO 12** | **Hangup GPIO 14**
- ✅ Works with cellular, FaceTime, WhatsApp calls
- ⚡ No audio routing - pure call control
- 🔌 Plug & pair - automatic HFP connection during calls
- ✅ Works with Android & iPhone  
- ✅ Automatic HFP connection during calls
- ✅ No phone modification needed
- ✅ Battery-powered friendly (low power when idle)

## Wiring
![ESP-32 pinout.](https://github.com/cristianonescu/esp32-call-answer/blob/main/pinout.png?raw=true)
- ESP32 GPIO12 ← Answer Button ← GND
- ESP32 GPIO14 ← Hangup Button ← GND


## Setup (manual):
- Install Espressif-IDE https://docs.espressif.com/projects/espressif-ide/en/latest/downloads.html
- Import project
- Configure Launch Target (on). Press on the drop-down, click on New Launch Target, ESP Target.
- Build
- Flash

## Setup (automatically):
- Flash the latest release on your board.

## 🚀 Flash Binary

### Download
Latest Release: https://github.com/cristianonescu/esp32-call-answer/releases/

### Flash (easy)
- `pip install esptool`
- `esptool.py --chip esp32 --port COM3 write_flash 0x0 esp32-call-buttons.bin` (download the bin from Releases)

###Flash Instructions for Users
## Method 1: ESPTool (Recommended)
- `esptool.py --chip esp32 --port COM3 --baud 921600 write_flash 0x0 esp32-call-buttons.bin`
- Linux/Mac: `esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 921600 write_flash 0x0 esp32-call-buttons.bin`

## Method 2: Web Flashers
1. https://espressif.github.io/esptool-js/
2. Drag & drop esp32-call-buttons.bin
3. Connect ESP32 → FLASH → Done!
   
## Method 3: Arduino IDE
1. Tools → Board → "ESP32 Dev Module"
2. Sketch → "Show Sketch Folder" → copy .bin
3. ESP32 Sketch Data Upload → Select .bin → Upload

## Method 4: PlatformIO
- `platformio run --target upload --upload-port /dev/ttyUSB0`
- or drag .bin to PIO uploader

## ✅ Compatible Boards:
- ESP32-D0WD	ESP32-DevKitC, ESP32-WROOM-32, NodeMCU-32S, FireBeetle-ESP32	Full Classic BT 4.2
- ESP32-D0WDR2 (V3)	ESP32-WROOM-32D/E/U, ESP32-WROVER	Most common, proven
- ESP32-D2WD	ESP32-Solo-1	Smaller footprint
- ESP32-PICO-D4	ESP32-PICO-Kit	Tiny modules
- ESP32-U4WDH	ESP32-S3? No - ESP32-U series	Dual-core, same BT
- ESP32-H2	ESP32-H2-DevKitM-1	Bluetooth 5 LE-only, no full Classic HFP 
​
## ❌ Not Compatible Boards:
- ESP32-S2/S3/C3/C6 → BLE 5.0 only, no Classic BT/HFP
- ESP32-C5 → WiFi 6 + BLE only
- ESP32-C61 → BLE only
