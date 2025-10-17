# HubOLED Quick Reference

## Initialization
```cpp
#include <hub_oled.h>
HubOLED display(OLED_TYPE_GROVE);  // or OLED_TYPE_SSD1306
display.init();
```

## Basic Text Output
```cpp
// Set specific line (0-based, from content area)
display.setLine(0, "Hello", false);      // Left-aligned
display.setLine(1, "World", true);       // Centered

// Print with auto-advance
display.println("Line 1");
display.println("Line 2", true);  // Centered
```

## Numbers
```cpp
display.printNumber(0, 42);              // Integer
display.printFloat(1, 3.14159, 2);       // Float with 2 decimals
```

## Display Control
```cpp
display.clear();                         // Clear all (redraw header)
display.clear(false);                    // Clear all (no header)
display.clearContent();                  // Clear content only
display.setBrightness(128);              // 0-255
display.setInverted(true);               // Invert colors
display.displayOff();                    // Turn off
display.displayOn();                     // Turn on
```

## Headers
```cpp
display.setHeader("My App");             // Single line
display.setHeader("Line 1\nLine 2");     // Multiple lines

const char* h[] = {"Title", "Subtitle"};
display.setHeader(h, 2);                 // Array

display.clearHeader();                   // Remove header
```

## Scrolling
```cpp
display.scrollLeft(0, 7, Scroll_5Frames);
display.scrollRight(2, 5, Scroll_3Frames);
display.stopScroll();
```

## Information
```cpp
uint8_t height = display.getHeight();           // Total lines
uint8_t width = display.getWidth();             // Chars per line
uint8_t content = display.getContentHeight();   // Lines - header
bool ready = display.isInitialized();
```

## Advanced
```cpp
display.setCursor(row, col);                        // Manual cursor
display.fillRect(row, col, width, 'X');             // Fill area
display.drawBitmap(bitmap, bytes, width, row, col); // Draw bitmap
```

## Common Patterns

### Status Display
```cpp
display.setHeader("Status");
display.setLine(0, "Mode: Auto", false);
display.printNumber(1, battery_percent, true);
```

### Dynamic Updates
```cpp
char buffer[25];
sprintf(buffer, "Temp: %.1fC", temp);
display.setLine(0, buffer, false);
```

### Progress Bar
```cpp
int percent = 75;
int filled = (display.getWidth() * percent) / 100;
char bar[25];
memset(bar, '=', filled);
memset(bar + filled, ' ', display.getWidth() - filled);
bar[display.getWidth()] = '\0';
display.setLine(0, bar, false);
```

## Display Types

| Type | Width | Example |
|------|-------|---------|
| OLED_TYPE_GROVE | 16 chars | Grove 0.96" OLED |
| OLED_TYPE_SSD1306 | 24 chars | Adafruit SSD1306 |
| OLED_TYPE_NONE | N/A | Disabled |

## Scroll Speed Constants
- `Scroll_2Frames` (fastest)
- `Scroll_3Frames`
- `Scroll_5Frames` (default)
- `Scroll_25Frames`
- `Scroll_64Frames`
- `Scroll_128Frames`
- `Scroll_256Frames` (slowest)

## Memory Best Practices
```cpp
// ✅ Good - Use C-strings
display.setLine(0, "Status", false);

// ✅ Good - Use sprintf
char buf[25];
sprintf(buf, "Val: %d", value);
display.setLine(0, buf, false);

// ❌ Avoid - String concatenation
String msg = "Val: " + String(value);  // Heap allocation!
display.setLine(0, msg, false);
```

## Error Prevention
```cpp
// Always initialize
display.init();

// Check before use
if (display.isInitialized()) {
    display.setLine(0, "Ready", true);
}

// Stay within bounds
if (line < display.getContentHeight()) {
    display.setLine(line, text, false);
}
```
