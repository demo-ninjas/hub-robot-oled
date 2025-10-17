# HubOLED - Tiny OLED Display Library

A memory-safe library for controlling small OLED displays in robotics projects. Supports Grove 0.96" and SSD1306-based OLED modules with a unified, easy-to-use API.

## ✨ Features

- 🎯 **Unified API** - Works seamlessly with multiple display types
- 🚀 **Memory Efficient** - Zero dynamic allocation, stack-based buffers
- 🛡️ **Safe** - Comprehensive bounds checking and null pointer guards
- 📝 **Feature Rich** - Headers, text alignment, scrolling, brightness control
- 📚 **Well Documented** - Comprehensive guides with 20+ working examples
- ⚡ **High Performance** - Minimal overhead, efficient rendering

## 🚀 Quick Start

```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_GROVE);  // or OLED_TYPE_SSD1306

void setup() {
    display.init();
    display.setHeader("Robot v1.0");
    display.setLine(0, "Status: Ready", false);
    display.printFloat(1, 3.14159, 2, true);  // Shows "3.14" centered
}

void loop() {
    // Your code here
}
```

## 📖 Documentation

| Document | Description |
|----------|-------------|
| **[Usage Guide](docs/USAGE_GUIDE.md)** | Complete API reference, best practices, troubleshooting |
| **[Quick Reference](docs/QUICK_REFERENCE.md)** | Fast syntax lookup and common patterns |
| **[Examples](docs/EXAMPLES.md)** | 20+ ready-to-use code examples |

## 🔌 Hardware Support

| Display | Enum Value | Resolution | Chars/Line |
|---------|------------|------------|------------|
| Grove 0.96" OLED | `OLED_TYPE_GROVE` | 128x64 | 16 |
| SSD1306 Mini OLED | `OLED_TYPE_SSD1306` | 128x64 | 24 |

**Wiring:** I2C (SDA/SCL) + Power (3.3V/5V) + Ground

## 📦 Installation

### PlatformIO (Recommended)

Add to your `platformio.ini`:

```ini
lib_deps = 
    https://github.com/demo-ninjas/hub-robot-oled.git
```

## 🎯 Core Features

### Text Output
```cpp
display.setLine(0, "Hello", true);        // Centered text
display.println("Auto-advance");           // Stream-style output
display.printNumber(1, 42);                // Integer
display.printFloat(2, 3.14, 2);           // Float with 2 decimals
```

### Display Control
```cpp
display.clear();                           // Clear all (keep header)
display.clearContent();                    // Clear content only
display.setBrightness(128);                // 0-255
display.setInverted(true);                 // Invert colors
```

### Headers
```cpp
display.setHeader("App Title");            // Single line
display.setHeader("Line 1\nLine 2");       // Multi-line
```

### Scrolling
```cpp
display.scrollLeft(0, 7, Scroll_5Frames);  // Hardware scrolling
display.scrollRight(2, 5, Scroll_3Frames);
display.stopScroll();
```

### Bitmaps
```cpp
uint8_t logo[] = { /* bitmap data */ };
display.drawBitmap(logo, sizeof(logo), 16, 2, 4);  // Draw 16px wide bitmap at row 2, col 4
```

## 💡 Why HubOLED?

### Before (String-based, heap allocation)
```cpp
String msg = "Value: " + String(value);    // ❌ Heap fragmentation
display.print(msg);                         // ❌ Memory leak risk
```

### After (HubOLED, stack-based)
```cpp
char buffer[25];                           // ✅ Stack allocation
sprintf(buffer, "Value: %d", value);       // ✅ Efficient
display.setLine(0, buffer);                // ✅ Safe
```

**Result:** Stable memory usage, no fragmentation, perfect for long-running embedded systems.

## 🔧 API Highlights

| Category | Key Methods |
|----------|-------------|
| **Initialization** | `init()`, `isInitialized()` |
| **Text** | `setLine()`, `println()`, `printNumber()`, `printFloat()` |
| **Display** | `clear()`, `setBrightness()`, `setInverted()` |
| **Headers** | `setHeader()`, `clearHeader()`, `printHeader()` |
| **Scrolling** | `scrollLeft()`, `scrollRight()`, `stopScroll()` |
| **Advanced** | `setCursor()`, `drawBitmap()`, `fillRect()` |
| **Graphics** | `drawBitmap()` for custom icons and images |
| **Info** | `getWidth()`, `getHeight()`, `getContentHeight()` |

## 📊 Example: Sensor Dashboard

```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_SSD1306);

void setup() {
    display.init();
    display.setHeader("Sensor Data");
}

void loop() {
    char line[25];
    
    float temp = readTemperature();
    sprintf(line, "Temp: %.1fC", temp);
    display.setLine(0, line);
    
    int humidity = readHumidity();
    sprintf(line, "Humid: %d%%", humidity);
    display.setLine(1, line);
    
    delay(2000);
}
```

**See [EXAMPLES.md](docs/EXAMPLES.md) for 20+ more examples!**

## 🎓 Learn More

- **Getting Started:** [Quick Reference](docs/QUICK_REFERENCE.md)
- **Full Documentation:** [Usage Guide](docs/USAGE_GUIDE.md)
- **Code Examples:** [Examples Collection](docs/EXAMPLES.md)

## 🔗 Dependencies

This library is dependent on the [Hub Robot Core](https://github.com/demo-ninjas/hub-robot-core) library - be sure to include it in your project when adding this module (if you're usiung platformio this will be automatically included).

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

