# ESP32 Call Answer/Decline

**Physical call buttons for your phone** using ESP32 as HFP Hands-Free device.

## Target Users
- Old people
- Kids
- People that cannot use touchscreens

## Features
- ✅ Answer/reject calls (GPIO 12/14)
- ✅ Works with Android & iPhone  
- ✅ Automatic HFP connection during calls
- ✅ No phone modification needed
- ✅ Battery-powered friendly (low power when idle)

## Wiring
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

## Compatible Boards:
✅ ESP32 (Original) - All Variants
Chip	Boards/Modules	Notes
ESP32-D0WD	ESP32-DevKitC, ESP32-WROOM-32, NodeMCU-32S, FireBeetle-ESP32	Full Classic BT 4.2
ESP32-D0WDR2 (V3)	ESP32-WROOM-32D/E/U, ESP32-WROVER	Most common, proven
ESP32-D2WD	ESP32-Solo-1	Smaller footprint
ESP32-PICO-D4	ESP32-PICO-Kit	Tiny modules
ESP32-U4WDH	ESP32-S3? No - ESP32-U series	Dual-core, same BT
✅ ESP32-H2 (Limited Classic BT)
Chip	Boards	Notes
ESP32-H2	ESP32-H2-DevKitM-1	Bluetooth 5 LE-only, no full Classic HFP 
​
## Not Compatible Boards:
❌ NOT Compatible (BLE Only)
ESP32-S2/S3/C3/C6 → BLE 5.0 only, no Classic BT/HFP
ESP32-C5 → WiFi 6 + BLE only
ESP32-C61 → BLE only
