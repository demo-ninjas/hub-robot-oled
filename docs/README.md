# HubOLED Documentation

Welcome to the HubOLED library documentation!

## Documentation Files

### 📘 [USAGE_GUIDE.md](USAGE_GUIDE.md)
**Comprehensive reference guide** covering everything you need to know about the HubOLED library:
- Complete API reference with all methods
- Hardware support information
- Best practices and performance tips
- Troubleshooting guide
- Memory management strategies

**Start here if:** You need detailed information about specific features, want to understand the library architecture, or need to troubleshoot issues.

---

### ⚡ [QUICK_REFERENCE.md](QUICK_REFERENCE.md)
**Quick lookup guide** with concise syntax and common patterns:
- Essential initialization code
- Common operations at a glance
- Memory-efficient code patterns
- Display type comparison table
- Scroll speed constants

**Start here if:** You know what you want to do and just need a quick syntax reminder.

---

### 💡 [EXAMPLES.md](EXAMPLES.md)
**20+ ready-to-use code examples** covering real-world use cases:
- Basic text output
- Sensor data displays
- User interface (menus, dialogs)
- Animations and effects
- Utility displays (battery, WiFi, graphs)

**Start here if:** You want to see working code examples that you can adapt for your project.

---

## Quick Start

### 1. Basic Setup (30 seconds)
```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_GROVE);  // or OLED_TYPE_SSD1306

void setup() {
    display.init();
    display.setLine(0, "Hello, World!", true);
}

void loop() {}
```

### 2. Choose Your Path

| If you want to... | Go to... |
|-------------------|----------|
| Learn all features in depth | [USAGE_GUIDE.md](USAGE_GUIDE.md) |
| See quick syntax examples | [QUICK_REFERENCE.md](QUICK_REFERENCE.md) |
| Copy/paste working examples | [EXAMPLES.md](EXAMPLES.md) |

---

## Common Use Cases

### Displaying Sensor Data
See [EXAMPLES.md - Example 5: Multi-Sensor Dashboard](EXAMPLES.md#example-5-multi-sensor-dashboard)

### Creating a Menu System  
See [EXAMPLES.md - Example 7: Menu System](EXAMPLES.md#example-7-menu-system)

### Showing Progress  
See [EXAMPLES.md - Example 10: Progress Bar](EXAMPLES.md#example-10-progress-bar)

### Battery Monitoring
See [EXAMPLES.md - Example 15: Battery Monitor](EXAMPLES.md#example-15-battery-monitor)

---

## Key Features

✅ **Memory Efficient** - No dynamic allocation, safe for embedded systems  
✅ **Multiple Displays** - Support for Grove and SSD1306 OLED displays  
✅ **Feature Rich** - Headers, scrolling, brightness, alignment, and more  
✅ **Easy to Use** - Simple, consistent API across display types  
✅ **Well Documented** - Complete guides with 20+ examples  

---

## Library Structure

```
hub_oled.h/cpp
├── Initialization & Properties
│   ├── Constructor & init()
│   └── Display info getters
├── Text Output
│   ├── setLine() - Specific line
│   ├── println() - Auto-advance
│   └── printNumber/Float()
├── Display Control
│   ├── clear() / clearContent()
│   ├── Brightness & inversion
│   └── Display on/off
├── Header Management
│   ├── setHeader()
│   └── Header utilities
├── Scrolling
│   ├── scrollLeft/Right()
│   └── stopScroll()
└── Advanced Features
    ├── setCursor()
    ├── drawBitmap()
    └── fillRect()
```

---

## Hardware Requirements

| Component | Notes |
|-----------|-------|
| **Display** | Grove 0.96" OLED or SSD1306-based OLED |
| **Connection** | I2C (SDA/SCL pins) |
| **Voltage** | 3.3V or 5V (depends on display module) |
| **MCU** | ESP32, Arduino, or compatible |

---

## Support & Contributing

- **Issues**: [GitHub Issues](https://github.com/demo-ninjas/hub-robot-oled/issues)
- **Contributing**: Pull requests welcome!

---

## License

See [LICENSE](../LICENSE) file for details.

---

**Happy coding! 🤖📺**
