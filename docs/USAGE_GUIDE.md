# HubOLED Library - Comprehensive Usage Guide

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Hardware Support](#hardware-support)
4. [Installation](#installation)
5. [Getting Started](#getting-started)
6. [API Reference](#api-reference)
7. [Code Examples](#code-examples)
8. [Best Practices](#best-practices)
9. [Troubleshooting](#troubleshooting)
10. [Performance Considerations](#performance-considerations)

## Introduction

The HubOLED library provides a unified, efficient interface for controlling small OLED displays on robotics projects. It abstracts the differences between various OLED display types, offering a simple, consistent API while maintaining excellent performance and memory efficiency.

### Key Benefits
- **Unified API**: Works seamlessly with multiple display types
- **Memory Efficient**: Uses stack-based buffers instead of heap allocation
- **Zero Dynamic Allocation**: No `String` or `std::vector` usage prevents heap fragmentation
- **Feature Rich**: Headers, scrolling, brightness control, and more
- **Safe**: Bounds checking and null pointer guards throughout

## Features

### Core Features
- ✅ Multiple display type support (Grove, SSD1306)
- ✅ Configurable multi-line headers
- ✅ Text alignment (left, center)
- ✅ Brightness control (0-255)
- ✅ Display inversion
- ✅ Hardware scrolling
- ✅ Number and float formatting
- ✅ Bitmap drawing
- ✅ Line-by-line and stream-style printing

### Safety Features
- ✅ Bounds checking on all operations
- ✅ Null pointer protection
- ✅ Initialization state tracking
- ✅ Maximum header line limits

### Performance Features
- ✅ Stack-based string buffers (no heap fragmentation)
- ✅ Minimal memory footprint
- ✅ Efficient text rendering
- ✅ Direct hardware access

## Hardware Support

### Supported Display Types

| Display Type | Enum Value | Resolution | Width (chars) | Height (lines) |
|-------------|------------|------------|---------------|----------------|
| Grove 0.96" OLED | `OLED_TYPE_GROVE` | 128x64 | 16 | 8 |
| SSD1306 Mini OLED | `OLED_TYPE_SSD1306` | 128x64 | 24 | 8 |
| None/Disabled | `OLED_TYPE_NONE` | N/A | N/A | N/A |

### Wiring

Both display types use I2C communication:
- **SDA**: Data line (typically GPIO 21 on ESP32)
- **SCL**: Clock line (typically GPIO 22 on ESP32)
- **VCC**: 3.3V or 5V (depending on display module)
- **GND**: Ground

## Installation

### PlatformIO (Recommended)

Add to your `platformio.ini`:

```ini
lib_deps = 
    https://github.com/demo-ninjas/hub-robot-oled.git
```

### Manual Installation

1. Clone the repository into your `lib` folder
2. Include the header in your code: `#include <hub_oled.h>`

## Getting Started

### Basic Setup

```cpp
#include <hub_oled.h>

// Create display object (choose your display type)
HubOLED display(OLED_TYPE_GROVE);  // or OLED_TYPE_SSD1306

void setup() {
    // Initialize the display
    display.init();
    
    // Display a simple message
    display.setLine(0, "Hello, World!", true);  // centered
}

void loop() {
    // Your code here
}
```

### With Header

```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_SSD1306);

void setup() {
    display.init();
    
    // Set a header (will appear at top of screen)
    display.setHeader("Robot Status");
    
    // Content appears below header
    display.setLine(0, "Battery: 100%", false);
    display.setLine(1, "Mode: Auto", false);
}
```

## API Reference

### Constructor & Initialization

#### `HubOLED(OledDisplayType oled_type)`
Creates a new HubOLED instance for the specified display type.

**Parameters:**
- `oled_type`: Display type (`OLED_TYPE_GROVE`, `OLED_TYPE_SSD1306`, or `OLED_TYPE_NONE`)

**Example:**
```cpp
HubOLED display(OLED_TYPE_GROVE);
```

---

#### `void init()`
Initializes the display hardware. Must be called in `setup()` before using the display.

**Example:**
```cpp
void setup() {
    display.init();
}
```

---

#### `bool isInitialized() const`
Returns whether the display has been successfully initialized.

**Returns:** `true` if initialized, `false` otherwise

**Example:**
```cpp
if (display.isInitialized()) {
    display.setLine(0, "Ready!");
}
```

---

### Display Properties

#### `uint8_t getHeight() const`
Returns the total height of the display in lines.

**Returns:** Number of text lines (typically 8)

---

#### `uint8_t getWidth() const`
Returns the width of the display in characters.

**Returns:** Number of characters per line (16 for Grove, 24 for SSD1306)

---

#### `uint8_t getContentHeight() const`
Returns the available content height (excluding header lines).

**Returns:** Number of lines available for content

**Example:**
```cpp
uint8_t available_lines = display.getContentHeight();
// If header has 2 lines and display has 8 total, returns 6
```

---

#### `uint8_t getContentStartLine() const`
Returns the first line number available for content (after header).

**Returns:** Starting line for content (equals header line count)

---

#### `OledDisplayType getDisplayType() const`
Returns the display type configured for this instance.

**Returns:** Display type enum value

---

### Text Output

#### `void setLine(uint8_t line, const char* msg, bool centered = false)`
Sets text on a specific line in the content area.

**Parameters:**
- `line`: Line number (0-based, relative to content area)
- `msg`: Text to display (C-string)
- `centered`: `true` to center text, `false` for left-aligned (default: `false`)

**Example:**
```cpp
display.setLine(0, "Status: OK", false);      // Left-aligned
display.setLine(1, "Ready", true);             // Centered
```

---

#### `void setLine(uint8_t line, const String& msg, bool centered = false)`
String version of setLine for Arduino String objects.

**Parameters:** Same as above, but accepts Arduino `String`

**Example:**
```cpp
String status = "Battery: " + String(batteryPercent) + "%";
display.setLine(0, status, false);
```

---

#### `void println(const char* msg, bool centered = false)`
Prints a line and auto-advances to next line (wraps to start when full).

**Parameters:**
- `msg`: Text to display
- `centered`: `true` to center, `false` for left-aligned

**Example:**
```cpp
display.println("Line 1");
display.println("Line 2");
display.println("Centered", true);
```

---

#### `void print(const char* msg)` / `void print(const String& msg)`
Prints a left-aligned line with auto-advance.

**Example:**
```cpp
display.print("Status:");
display.print("Running");
```

---

#### `void printNumber(uint8_t line, long number, bool centered = false)`
Formats and displays a long integer on the specified line.

**Parameters:**
- `line`: Line number in content area
- `number`: Integer to display
- `centered`: Center the number

**Example:**
```cpp
long distance = 1234;
display.printNumber(0, distance, true);  // Shows "1234" centered
```

---

#### `void printFloat(uint8_t line, float number, uint8_t decimal_places = 2, bool centered = false)`
Formats and displays a floating-point number.

**Parameters:**
- `line`: Line number
- `number`: Float value
- `decimal_places`: Decimal precision (default: 2)
- `centered`: Center the number

**Example:**
```cpp
float voltage = 3.7456;
display.printFloat(0, voltage, 2, true);  // Shows "3.75" centered
display.printFloat(1, voltage, 3, false); // Shows "3.746" left-aligned
```

---

### Display Control

#### `void clear(bool print_header = true)`
Clears the entire display.

**Parameters:**
- `print_header`: If `true`, redraws the header after clearing (default: `true`)

**Example:**
```cpp
display.clear();        // Clear and redraw header
display.clear(false);   // Clear everything including header
```

---

#### `void clearContent()`
Clears only the content area, preserving the header.

**Example:**
```cpp
display.clearContent();  // Header remains visible
```

---

#### `void setBrightness(uint8_t brightness)`
Sets the display brightness.

**Parameters:**
- `brightness`: Brightness level (0-255, where 255 is maximum)

**Example:**
```cpp
display.setBrightness(128);  // 50% brightness
display.setBrightness(255);  // Maximum brightness
display.setBrightness(32);   // Dim
```

---

#### `void setInverted(bool inverted)`
Inverts display colors (white becomes black and vice versa).

**Parameters:**
- `inverted`: `true` for inverted, `false` for normal

**Example:**
```cpp
display.setInverted(true);   // Invert colors
display.setInverted(false);  // Normal colors
```

---

#### `void displayOn()` / `void displayOff()`
Turns the display on or off (saves power when off).

**Example:**
```cpp
display.displayOff();  // Turn off to save power
delay(1000);
display.displayOn();   // Turn back on
```

---

### Header Management

#### `void setHeader(const char* header_lines[], uint8_t count)`
Sets multiple header lines from an array of C-strings.

**Parameters:**
- `header_lines`: Array of C-strings
- `count`: Number of header lines (max: 3)

**Example:**
```cpp
const char* headers[] = {"Robot v1.0", "Status Monitor"};
display.setHeader(headers, 2);
```

---

#### `void setHeader(const char* header)`
Sets header from a single string (newlines create multiple lines).

**Parameters:**
- `header`: Header text (use `\n` for multiple lines)

**Example:**
```cpp
display.setHeader("Robot v1.0\nStatus Monitor");
```

---

#### `void setHeaderLine(uint8_t index, const char* text)`
Updates a single header line.

**Parameters:**
- `index`: Header line index (0-2)
- `text`: Text for this header line

**Example:**
```cpp
display.setHeaderLine(0, "Robot v1.0");
display.setHeaderLine(1, "Battery: 85%");
```

---

#### `void printHeader()`
Redraws the header on screen.

**Example:**
```cpp
display.printHeader();  // Refresh header display
```

---

#### `void clearHeader()`
Removes the header and frees up those lines for content.

**Example:**
```cpp
display.clearHeader();  // Remove header, all 8 lines now available
```

---

#### `uint8_t getHeaderLineCount() const`
Returns the number of header lines currently configured.

**Returns:** Number of header lines (0-3)

---

### Scrolling

#### `void scrollLeft(uint8_t start_page = 0, uint8_t end_page = 7, uint8_t speed = Scroll_5Frames)`
Starts hardware horizontal scrolling to the left.

**Parameters:**
- `start_page`: Starting line (0-7)
- `end_page`: Ending line (0-7)
- `speed`: Scroll speed (use `Scroll_*Frames` constants)

**Speed Constants:**
- `Scroll_2Frames` (fastest)
- `Scroll_3Frames`
- `Scroll_5Frames` (default)
- `Scroll_25Frames`
- `Scroll_64Frames`
- `Scroll_128Frames`
- `Scroll_256Frames` (slowest)

**Example:**
```cpp
display.scrollLeft(2, 7, Scroll_5Frames);  // Scroll lines 2-7 left
```

---

#### `void scrollRight(uint8_t start_page = 0, uint8_t end_page = 7, uint8_t speed = Scroll_5Frames)`
Starts hardware scrolling to the right.

**Parameters:** Same as `scrollLeft()`

**Example:**
```cpp
display.scrollRight(0, 7, Scroll_3Frames);  // Fast scroll right
```

---

#### `void stopScroll()`
Stops any active scrolling.

**Example:**
```cpp
display.stopScroll();
```

---

### Advanced Features

#### `void setCursor(uint8_t row, uint8_t col)`
Manually positions the cursor (for direct text output).

**Parameters:**
- `row`: Row number (0-7)
- `col`: Column number (0-15 for Grove, 0-23 for SSD1306)

**Example:**
```cpp
display.setCursor(2, 5);  // Position at row 2, column 5
```

---

#### `void drawBitmap(const uint8_t* bitmap, int num_bytes, uint8_t bmp_width, uint8_t row, uint8_t col)`
Draws a bitmap image on the display at a specified position.

**Parameters:**
- `bitmap`: Pointer to bitmap data array (each byte represents 8 vertical pixels)
- `num_bytes`: Number of bytes in bitmap
- `bmp_width`: Width of the bitmap in bytes (number of columns)
- `row`: Starting row position (0-7)
- `col`: Starting column position (0-15 for Grove, 0-23 for SSD1306)

**Note:** Each byte in the bitmap represents 8 vertical pixels. The bitmap is drawn in horizontal addressing mode, moving down one row after every `bmp_width` bytes.

**Example:**
```cpp
// A 16x16 pixel bitmap (4 rows of 16 bytes each)
uint8_t logo[] = {
    0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
    0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
    0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
    0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03
};
display.drawBitmap(logo, sizeof(logo), 16, 2, 4);  // Draw at row 2, column 4
```

---

#### `void fillRect(uint8_t row, uint8_t col, uint8_t w, char fill_char = ' ')`
Fills a rectangular area with a character.

**Parameters:**
- `row`: Starting row
- `col`: Starting column
- `w`: Width in characters
- `fill_char`: Character to fill with (default: space)

**Example:**
```cpp
display.fillRect(3, 0, 16, '-');  // Draw horizontal line
display.fillRect(2, 5, 10, '*');  // Fill with asterisks
```

---

## Code Examples

### Example 1: Simple Status Display

```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_GROVE);

void setup() {
    display.init();
    display.setHeader("Robot Status");
    
    display.setLine(0, "Initializing...", true);
    delay(2000);
    
    display.setLine(0, "Ready!", true);
}

void loop() {
    // Update status periodically
    static unsigned long lastUpdate = 0;
    if (millis() - lastUpdate > 1000) {
        lastUpdate = millis();
        
        float uptime = millis() / 1000.0;
        display.setLine(1, "Uptime:", false);
        display.printFloat(2, uptime, 1, false);
    }
}
```

---

### Example 2: Sensor Data Display

```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_SSD1306);

void setup() {
    display.init();
    
    const char* headers[] = {"Sensor Dashboard", "---"};
    display.setHeader(headers, 2);
}

void loop() {
    // Read sensors (example values)
    float temperature = readTemperature();
    int humidity = readHumidity();
    float pressure = readPressure();
    
    // Display sensor data
    display.setLine(0, "Temp:", false);
    display.printFloat(0, temperature, 1, false);
    
    display.setLine(1, "Humidity:", false);
    display.printNumber(1, humidity, false);
    
    display.setLine(2, "Pressure:", false);
    display.printFloat(2, pressure, 2, false);
    
    delay(2000);
}
```

---

### Example 3: Menu System

```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_GROVE);
int menuSelection = 0;
const int menuItems = 4;

void setup() {
    display.init();
    display.setHeader("Main Menu");
    updateMenu();
}

void updateMenu() {
    display.clearContent();
    
    const char* items[] = {"Start", "Settings", "Stats", "Exit"};
    
    for (int i = 0; i < menuItems; i++) {
        char line[24];
        if (i == menuSelection) {
            sprintf(line, "> %s", items[i]);
        } else {
            sprintf(line, "  %s", items[i]);
        }
        display.setLine(i, line, false);
    }
}

void loop() {
    // Handle menu navigation (example)
    // updateMenu() when selection changes
}
```

---

### Example 4: Progress Bar

```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_GROVE);

void showProgress(const char* task, int percent) {
    display.clearContent();
    
    display.setLine(0, task, true);
    
    // Draw progress bar
    int barWidth = display.getWidth() - 2;
    int filled = (barWidth * percent) / 100;
    
    char bar[20];
    bar[0] = '[';
    for (int i = 0; i < barWidth; i++) {
        bar[i + 1] = (i < filled) ? '=' : ' ';
    }
    bar[barWidth + 1] = ']';
    bar[barWidth + 2] = '\0';
    
    display.setLine(1, bar, true);
    
    // Show percentage
    char pct[10];
    sprintf(pct, "%d%%", percent);
    display.setLine(2, pct, true);
}

void setup() {
    display.init();
    display.setHeader("Loading...");
    
    for (int i = 0; i <= 100; i += 10) {
        showProgress("Installing", i);
        delay(500);
    }
    
    display.clear();
    display.setLine(0, "Complete!", true);
}

void loop() {}
```

---

### Example 5: Scrolling Marquee

```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_SSD1306);

void setup() {
    display.init();
    
    display.setLine(0, "Scrolling Demo", true);
    display.setLine(2, "This text will scroll!", false);
    display.setLine(3, "Continuously moving...", false);
    
    delay(2000);
    
    // Start scrolling lines 2-5
    display.scrollLeft(2, 5, Scroll_5Frames);
}

void loop() {
    // Scrolling runs automatically in hardware
}
```

---

### Example 6: Multi-Display Support

```cpp
#include <hub_oled.h>

// Support multiple displays
HubOLED* display = nullptr;

void setup() {
    // Auto-detect or configure display type
    #ifdef USE_GROVE_DISPLAY
        display = new HubOLED(OLED_TYPE_GROVE);
    #else
        display = new HubOLED(OLED_TYPE_SSD1306);
    #endif
    
    display->init();
    
    if (display->isInitialized()) {
        display->setHeader("System Ready");
        display->setLine(0, "Display OK", true);
    }
}

void loop() {
    if (display && display->isInitialized()) {
        // Use display...
    }
}
```

---

### Example 7: Battery Monitor

```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_GROVE);

void setup() {
    display.init();
    display.setHeader("Battery Monitor");
}

void displayBattery(float voltage, int percent) {
    display.clearContent();
    
    // Voltage
    display.setLine(0, "Voltage:", false);
    display.printFloat(0, voltage, 2, false);
    
    // Percentage with visual bar
    char bar[20] = "|";
    int bars = percent / 10;
    for (int i = 0; i < 10; i++) {
        strcat(bar, (i < bars) ? "=" : " ");
    }
    strcat(bar, "|");
    
    display.setLine(1, bar, true);
    display.printNumber(2, percent, true);
    
    // Warning if low
    if (percent < 20) {
        display.setLine(3, "LOW BATTERY!", true);
        display.setInverted(true);
        delay(500);
        display.setInverted(false);
    }
}

void loop() {
    float voltage = readBatteryVoltage();
    int percent = calculatePercent(voltage);
    
    displayBattery(voltage, percent);
    delay(5000);
}
```

---

## Best Practices

### Memory Management
1. **Avoid String objects**: Use `const char*` or character arrays
   ```cpp
   // Good
   display.setLine(0, "Status OK", false);
   
   // Avoid (causes heap allocation)
   String msg = "Status " + status;
   display.setLine(0, msg, false);
   ```

2. **Use stack buffers**: For dynamic text, use `sprintf` or `snprintf`
   ```cpp
   char buffer[25];
   sprintf(buffer, "Temp: %.1f", temperature);
   display.setLine(0, buffer, false);
   ```

3. **Reuse buffers**: Declare buffers once and reuse them
   ```cpp
   static char line_buffer[25];
   // Reuse line_buffer throughout your code
   ```

### Performance
1. **Minimize updates**: Only redraw when content changes
   ```cpp
   static int last_value = -1;
   if (sensor_value != last_value) {
       display.printNumber(0, sensor_value);
       last_value = sensor_value;
   }
   ```

2. **Use clearContent() wisely**: Don't clear unnecessarily
   ```cpp
   // Good: Update specific lines
   display.setLine(0, "New value", false);
   
   // Avoid: Clearing and redrawing everything
   display.clearContent();
   display.setLine(0, "New value", false);
   ```

3. **Batch updates**: Group related updates together
   ```cpp
   // Update multiple lines at once
   display.setLine(0, "Line 1", false);
   display.setLine(1, "Line 2", false);
   display.setLine(2, "Line 3", false);
   ```

### Power Management
1. **Adjust brightness**: Lower brightness saves power
   ```cpp
   display.setBrightness(128);  // 50% brightness
   ```

2. **Turn off when not needed**:
   ```cpp
   display.displayOff();  // Deep sleep
   // ... later ...
   display.displayOn();
   ```

### Error Handling
1. **Check initialization**:
   ```cpp
   if (!display.isInitialized()) {
       // Handle error - use serial output or LED indicator
       return;
   }
   ```

2. **Validate inputs**:
   ```cpp
   if (line < display.getContentHeight()) {
       display.setLine(line, text, false);
   }
   ```

### Header Usage
1. **Keep headers concise**: Max 3 lines, short text
   ```cpp
   display.setHeader("App v1.0");  // Good
   ```

2. **Update header sparingly**: Headers rarely change
   ```cpp
   // Set once in setup()
   display.setHeader("Robot Control");
   ```

## Troubleshooting

### Display Not Working
- **Check I2C wiring**: Verify SDA/SCL connections
- **Check power**: Ensure 3.3V or 5V supply is stable
- **Verify display type**: Ensure correct enum in constructor
- **Check initialization**: Call `init()` in `setup()`

### Text Not Appearing
- **Call init()**: Display must be initialized
- **Check line numbers**: Ensure line < content height
- **Verify text length**: Text longer than width is truncated
- **Clear first**: Sometimes clearing helps: `display.clear()`

### Garbled Display
- **Reset display**: Call `init()` again
- **Check I2C bus speed**: Some displays need slower I2C
- **Power cycle**: Turn display off and on

### Memory Issues
- **Avoid String**: Use C-strings (`const char*`)
- **Check stack usage**: Large buffers on stack can overflow
- **Monitor heap**: Use `ESP.getFreeHeap()` to check available memory

### Performance Issues
- **Reduce update frequency**: Don't update every loop iteration
- **Optimize text**: Pre-format text when possible
- **Use hardware features**: Scrolling, inversion run in hardware

## Performance Considerations

### Memory Footprint
- **Fixed allocation**: ~100 bytes for HubOLED object
- **No dynamic allocation**: All buffers are stack-based
- **Header storage**: MAX_HEADER_LINES × (MAX_LINE_CHARS + 1) bytes

### Update Speed
- **I2C bottleneck**: Display updates limited by I2C speed (~100-400 kHz)
- **Full line update**: ~2-5ms per line on typical displays
- **Scrolling**: Hardware scrolling has no CPU overhead

### CPU Usage
- **Minimal**: Most operations complete in microseconds
- **No polling**: Library doesn't use interrupts or background tasks
- **Efficient**: Direct hardware access, minimal overhead

### Best Practices for Performance
1. Update only changed content
2. Use appropriate update intervals (100-1000ms typical)
3. Leverage hardware features (scrolling, brightness)
4. Batch related updates
5. Avoid frequent full screen clears

---

## Advanced Topics

### Custom Fonts
The SSD1306 driver supports custom fonts. See the underlying library documentation for font format details.

### Multiple Displays
Create multiple HubOLED instances for multiple displays (requires separate I2C addresses or buses).

### Integration with RTOS
The library is RTOS-safe as it doesn't use global state (except the underlying display drivers).

---

## License
See LICENSE file for details.

## Contributing
Contributions welcome! Please submit issues and pull requests on GitHub.

