# Tiny OLED Display Module

This is a basic library for displaying text on two small OLED display modules (Grove 0.96 module + the SSD1306 module).

This library is dependent on the [Hub Robot Core](https://github.com/demo-ninjas/hub-robot-core) library - be sure to include it in your project when adding this module.

## External Libraries

This module embeds two external OLED display libraries: 

### ACROBATIC SSD1306

This library is used for supporting SSD1306 based OLED screens.

A point in time copy of this library is stored in this repo.

The library is maintained here: https://github.com/datasith/Ai_Ardulib_SSD1306

### SeeedOLED

This library is used for supporting the small Grove OLED displays that the Hub has.

A point in time copy of this library is stored in this repo.

The library is maintained by SeeedStudio here: https://github.com/Seeed-Studio/OLED_Display_128X64


## Dev Machine Setup

Make sure you have the following installed on your machine: 

* A C/C++ compiler + standard dev tools installed (gcc, git, cmake etc...)
* PlatformIO Tools (https://platformio.org/)
* VSCode (https://code.visualstudio.com/)

Install the following VSCode Extensions: 

* C/C++ Extension pack (https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack) [This includes the C/C++ Extension]
* CMake Tools (https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
* PlatformIO IDE (https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide)

Install the `Arduino Espressif32` Framework in PlatformIO and make sure an ESP32 toolchain is installed (We typically use `ESP32S3`, eg. `toolchain-xtensa-esp32s3`).

## Publish

This library is intended to be used as a dependency for a Platform.io app.

The `library.json` describes the library and dependencies to Platform.io.

increment the version number when making changes you want to be used by dependent libraries.

Currently, not published to PlatformIO, load the library dependency directly via the GitHub URL.

