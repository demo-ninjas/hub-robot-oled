# HubOLED Code Examples

This document contains practical, ready-to-use examples for the HubOLED library.

## Table of Contents
1. [Basic Examples](#basic-examples)
2. [Sensor Displays](#sensor-displays)
3. [User Interface](#user-interface)
4. [Animation & Effects](#animation--effects)
5. [Utility Displays](#utility-displays)
6. [Graphics & Bitmaps](#graphics--bitmaps)

---

## Basic Examples

### Example 1: Hello World
```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_GROVE);

void setup() {
    display.init();
    display.setLine(0, "Hello, World!", true);
}

void loop() {
    // Nothing to do
}
```

### Example 2: Simple Counter
```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_SSD1306);
int counter = 0;

void setup() {
    display.init();
    display.setHeader("Counter Demo");
}

void loop() {
    display.setLine(0, "Count:", false);
    display.printNumber(1, counter, true);
    counter++;
    delay(1000);
}
```

### Example 3: Multi-Line Text
```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_GROVE);

void setup() {
    display.init();
    display.setHeader("Information");
    
    display.setLine(0, "Line 1: Left", false);
    display.setLine(1, "Line 2: Center", true);
    display.setLine(2, "Line 3: Left", false);
}

void loop() {}
```

---

## Sensor Displays

### Example 4: Temperature Monitor
```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_GROVE);

// Simulated sensor reading
float getTemperature() {
    return 20.0 + (analogRead(A0) / 1023.0) * 10.0;
}

void setup() {
    display.init();
    display.setHeader("Temp Monitor");
}

void loop() {
    float temp = getTemperature();
    
    display.setLine(0, "Temperature:", false);
    display.printFloat(1, temp, 1, true);
    display.setLine(2, "Celsius", true);
    
    delay(2000);
}
```

### Example 5: Multi-Sensor Dashboard
```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_SSD1306);

struct SensorData {
    float temperature;
    int humidity;
    float pressure;
};

SensorData readSensors() {
    SensorData data;
    data.temperature = 22.5;
    data.humidity = 45;
    data.pressure = 1013.25;
    return data;
}

void setup() {
    display.init();
    display.setHeader("Env Monitor");
}

void loop() {
    SensorData data = readSensors();
    
    char line[25];
    
    sprintf(line, "Temp: %.1fC", data.temperature);
    display.setLine(0, line, false);
    
    sprintf(line, "Humid: %d%%", data.humidity);
    display.setLine(1, line, false);
    
    sprintf(line, "Press: %.1f hPa", data.pressure);
    display.setLine(2, line, false);
    
    delay(5000);
}
```

### Example 6: Distance Sensor with Warning
```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_GROVE);
const int WARN_DISTANCE = 30;  // cm

int getDistance() {
    // Simulated ultrasonic sensor
    return random(5, 100);
}

void setup() {
    display.init();
    display.setHeader("Distance Sensor");
}

void loop() {
    int distance = getDistance();
    
    display.setLine(0, "Distance:", false);
    display.printNumber(1, distance, true);
    display.setLine(2, "cm", true);
    
    if (distance < WARN_DISTANCE) {
        display.setLine(3, "!!! WARNING !!!", true);
        display.setInverted(true);
        delay(300);
        display.setInverted(false);
        delay(300);
    } else {
        display.setLine(3, "Safe", true);
        delay(1000);
    }
}
```

---

## User Interface

### Example 7: Menu System
```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_GROVE);

enum MenuItem {
    MENU_START,
    MENU_SETTINGS,
    MENU_STATS,
    MENU_EXIT,
    MENU_COUNT
};

MenuItem currentSelection = MENU_START;

const char* menuText[] = {
    "Start",
    "Settings",
    "Statistics",
    "Exit"
};

void displayMenu() {
    display.clearContent();
    
    for (int i = 0; i < MENU_COUNT; i++) {
        char line[20];
        if (i == currentSelection) {
            sprintf(line, "> %s", menuText[i]);
        } else {
            sprintf(line, "  %s", menuText[i]);
        }
        display.setLine(i, line, false);
    }
}

void setup() {
    display.init();
    display.setHeader("Main Menu");
    displayMenu();
}

void loop() {
    // Simulate menu navigation with buttons
    // Up button: currentSelection--
    // Down button: currentSelection++
    // Select button: execute menu item
    
    // Example: cycle through menu
    static unsigned long lastChange = 0;
    if (millis() - lastChange > 2000) {
        currentSelection = (MenuItem)((currentSelection + 1) % MENU_COUNT);
        displayMenu();
        lastChange = millis();
    }
}
```

### Example 8: Settings Screen
```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_SSD1306);

struct Settings {
    int brightness;
    bool autoMode;
    int speed;
};

Settings settings = {128, true, 50};

void displaySettings() {
    display.clearContent();
    
    char line[25];
    
    sprintf(line, "Brightness: %d", settings.brightness);
    display.setLine(0, line, false);
    
    sprintf(line, "Auto Mode: %s", settings.autoMode ? "ON" : "OFF");
    display.setLine(1, line, false);
    
    sprintf(line, "Speed: %d%%", settings.speed);
    display.setLine(2, line, false);
}

void setup() {
    display.init();
    display.setHeader("Settings");
    displaySettings();
}

void loop() {
    // Update settings based on user input
    // displaySettings() when changed
}
```

### Example 9: Confirmation Dialog
```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_GROVE);

enum DialogResult {
    RESULT_YES,
    RESULT_NO,
    RESULT_PENDING
};

DialogResult showConfirmation(const char* message) {
    display.clear();
    display.setLine(0, message, true);
    display.setLine(2, "Yes", false);
    display.setLine(2, "No", false);  // Align right manually
    
    // Wait for button press
    // Return RESULT_YES or RESULT_NO
    return RESULT_PENDING;
}

void setup() {
    display.init();
    
    DialogResult result = showConfirmation("Delete all?");
    
    if (result == RESULT_YES) {
        display.clear();
        display.setLine(0, "Deleted!", true);
    } else {
        display.clear();
        display.setLine(0, "Cancelled", true);
    }
}

void loop() {}
```

---

## Animation & Effects

### Example 10: Progress Bar
```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_GROVE);

void showProgress(const char* task, int percent) {
    display.clearContent();
    
    display.setLine(0, task, true);
    
    // Calculate bar
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
    
    char pct[10];
    sprintf(pct, "%d%%", percent);
    display.setLine(2, pct, true);
}

void setup() {
    display.init();
    display.setHeader("Loading");
    
    for (int i = 0; i <= 100; i += 5) {
        showProgress("Installing", i);
        delay(200);
    }
    
    display.clear();
    display.setLine(0, "Complete!", true);
}

void loop() {}
```

### Example 11: Blinking Text
```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_GROVE);

void setup() {
    display.init();
    display.setHeader("Alert System");
}

void loop() {
    // Show alert
    display.setLine(0, "ALERT!", true);
    delay(500);
    
    // Clear alert
    display.clearContent();
    delay(500);
}
```

### Example 12: Scrolling Text
```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_SSD1306);

void setup() {
    display.init();
    display.setHeader("News Ticker");
    
    display.setLine(0, "Breaking: Robot learns to code!", false);
    display.setLine(1, "Scientists amazed by AI progress", false);
    
    delay(2000);
    
    // Start hardware scrolling
    display.scrollLeft(2, 3, Scroll_5Frames);
}

void loop() {
    // Scrolling continues automatically
}
```

### Example 13: Animation Frames
```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_GROVE);

const char* frames[] = {
    "|",
    "/",
    "-",
    "\\"
};
const int frameCount = 4;

void setup() {
    display.init();
    display.setHeader("Loading...");
}

void loop() {
    static int frame = 0;
    
    display.setLine(0, frames[frame], true);
    frame = (frame + 1) % frameCount;
    
    delay(100);
}
```

---

## Utility Displays

### Example 14: System Info
```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_SSD1306);

void setup() {
    display.init();
    
    const char* headers[] = {"System Info", "----------"};
    display.setHeader(headers, 2);
    
    char line[25];
    
    sprintf(line, "Free RAM: %d", ESP.getFreeHeap());
    display.setLine(0, line, false);
    
    sprintf(line, "CPU Freq: %d MHz", ESP.getCpuFreqMHz());
    display.setLine(1, line, false);
    
    sprintf(line, "Flash: %d MB", ESP.getFlashChipSize() / 1048576);
    display.setLine(2, line, false);
}

void loop() {}
```

### Example 15: Battery Monitor
```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_GROVE);

float getBatteryVoltage() {
    // Read from ADC
    int raw = analogRead(A0);
    return (raw / 1023.0) * 4.2;  // Scale to battery voltage
}

int voltageToPercent(float voltage) {
    // Simple linear mapping (3.0V = 0%, 4.2V = 100%)
    return constrain(((voltage - 3.0) / 1.2) * 100, 0, 100);
}

void displayBattery(float voltage, int percent) {
    char line[25];
    
    sprintf(line, "Volt: %.2fV", voltage);
    display.setLine(0, line, false);
    
    // Visual bar
    int bars = percent / 10;
    char bar[20] = "|";
    for (int i = 0; i < 10; i++) {
        strcat(bar, (i < bars) ? "=" : " ");
    }
    strcat(bar, "|");
    display.setLine(1, bar, true);
    
    sprintf(line, "%d%%", percent);
    display.setLine(2, line, true);
    
    if (percent < 20) {
        display.setLine(3, "LOW BATTERY!", true);
    }
}

void setup() {
    display.init();
    display.setHeader("Battery");
}

void loop() {
    float voltage = getBatteryVoltage();
    int percent = voltageToPercent(voltage);
    
    displayBattery(voltage, percent);
    delay(5000);
}
```

### Example 16: Network Status
```cpp
#include <hub_oled.h>
#include <WiFi.h>

HubOLED display(OLED_TYPE_SSD1306);

void displayWiFiStatus() {
    display.clearContent();
    
    if (WiFi.status() == WL_CONNECTED) {
        display.setLine(0, "WiFi: Connected", false);
        
        char line[25];
        sprintf(line, "IP: %s", WiFi.localIP().toString().c_str());
        display.setLine(1, line, false);
        
        sprintf(line, "RSSI: %d dBm", WiFi.RSSI());
        display.setLine(2, line, false);
    } else {
        display.setLine(0, "WiFi: Disconnected", false);
        display.setLine(1, "Connecting...", true);
    }
}

void setup() {
    display.init();
    display.setHeader("Network Status");
    
    WiFi.begin("YourSSID", "YourPassword");
    
    while (WiFi.status() != WL_CONNECTED) {
        displayWiFiStatus();
        delay(500);
    }
    
    displayWiFiStatus();
}

void loop() {
    // Update status periodically
    static unsigned long lastUpdate = 0;
    if (millis() - lastUpdate > 10000) {
        displayWiFiStatus();
        lastUpdate = millis();
    }
}
```

### Example 17: Stopwatch
```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_GROVE);

unsigned long startTime = 0;
bool running = false;

void displayTime(unsigned long ms) {
    unsigned long seconds = ms / 1000;
    unsigned long minutes = seconds / 60;
    unsigned long hours = minutes / 60;
    
    seconds %= 60;
    minutes %= 60;
    
    char line[25];
    sprintf(line, "%02lu:%02lu:%02lu", hours, minutes, seconds);
    display.setLine(0, line, true);
}

void setup() {
    display.init();
    display.setHeader("Stopwatch");
    
    startTime = millis();
    running = true;
}

void loop() {
    if (running) {
        unsigned long elapsed = millis() - startTime;
        displayTime(elapsed);
        delay(100);
    }
}
```

### Example 18: Brightness Control Demo
```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_GROVE);

void setup() {
    display.init();
    display.setHeader("Brightness Demo");
    display.setLine(0, "Brightness Test", true);
}

void loop() {
    // Fade in
    for (int i = 0; i <= 255; i += 5) {
        display.setBrightness(i);
        delay(20);
    }
    
    delay(1000);
    
    // Fade out
    for (int i = 255; i >= 0; i -= 5) {
        display.setBrightness(i);
        delay(20);
    }
    
    delay(1000);
}
```

### Example 19: Debug Console
```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_SSD1306);

class DebugConsole {
private:
    HubOLED* disp;
    int nextLine;
    int maxLines;
    
public:
    DebugConsole(HubOLED* d) : disp(d), nextLine(0) {
        maxLines = disp->getContentHeight();
    }
    
    void log(const char* msg) {
        if (nextLine >= maxLines) {
            // Scroll up by clearing and restarting
            disp->clearContent();
            nextLine = 0;
        }
        disp->setLine(nextLine, msg, false);
        nextLine++;
    }
};

DebugConsole console(&display);

void setup() {
    display.init();
    display.setHeader("Debug Log");
    
    console.log("System start");
    delay(1000);
    console.log("Init sensors");
    delay(1000);
    console.log("Connect WiFi");
    delay(1000);
    console.log("Ready!");
}

void loop() {
    static int count = 0;
    char msg[25];
    sprintf(msg, "Msg %d", count++);
    console.log(msg);
    delay(2000);
}
```

---

## Graphics & Bitmaps

### Example 20: Drawing Bitmaps
```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_GROVE);

void setup() {
    display.init();
    display.setHeader("A Square");
    display.clear();
    
    // A bitmap of a 16 x 16 square 
    // Each byte represents 8 vertical pixels
    // Total: 4 rows of 16 bytes = 64 bytes for a 16x16px image
    uint8_t bitmap[] = {
        0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
        0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
        0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
        0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03
    };
    
    // Draw the bitmap at row 2, column 10
    // Parameters: bitmap data, size in bytes, width in bytes, row, column
    display.drawBitmap(bitmap, sizeof(bitmap), 16, 2, 10);
    
    display.setLine(5, "Bitmap Demo", true);
}

void loop() {}
```

### Example 21: Multiple Small Icons
```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_SSD1306);


// 8x8 circle icon
uint8_t iconCircle[] = {
    0x3C,0x42,0x81,0x81,0x81,0x81,0x42,0x3C
};

// 8x8 X icon  
uint8_t iconX[] = {
    0x41,0x22,0x14,0x08,0x14,0x22,0x41,0x00
};

// 8x8 diamond icon
uint8_t iconDiamond[] = {
    0x08,0x1C,0x3E,0x7F,0x3E,0x1C,0x08,0x00
};

// Triangle icon
uint8_t iconTriangle[] = {
    0x08,0x1C,0x3E,0x7F,0x00,0x00,0x00,0x00
};

void setup() {
    // Draw icons in a row
    display.init();
    display.setHeader("Icon Gallery");
    display.clear();

    // Draw icons in a row
    display.drawBitmap(iconCircle, sizeof(iconCircle), 8, 4, 5);
    display.drawBitmap(iconX, sizeof(iconX), 8, 4, 10);
    display.drawBitmap(iconDiamond, sizeof(iconDiamond), 8, 4, 15);
    display.drawBitmap(iconTriangle, sizeof(iconTriangle), 8, 6, 10);
}

void loop() {}
```

### Example 22: Graph Display (Simple)
```cpp
#include <hub_oled.h>

HubOLED display(OLED_TYPE_GROVE);

const int DATA_POINTS = 16;  // Width of display
int dataHistory[DATA_POINTS] = {0};
int dataIndex = 0;

void addDataPoint(int value) {
    dataHistory[dataIndex] = constrain(value, 0, 5);
    dataIndex = (dataIndex + 1) % DATA_POINTS;
}

void drawGraph() {
    display.clearContent();
    
    // Draw each column
    for (int x = 0; x < DATA_POINTS; x++) {
        int height = dataHistory[(dataIndex + x) % DATA_POINTS];
        
        // Draw vertical bar at position x
        for (int y = 0; y < 5; y++) {
            if (y < height) {
                display.fillRect(4 - y, x, 1, '|');
            }
        }
    }
}

void setup() {
    display.init();
    display.setHeader("Graph");
}

void loop() {
    int value = random(0, 6);
    addDataPoint(value);
    drawGraph();
    delay(500);
}
```

---

## Tips for Creating Your Own Examples

1. **Start Simple**: Begin with basic text output, then add features
2. **Test Incrementally**: Verify each feature works before adding more
3. **Use Buffers**: Pre-format complex text with `sprintf`
4. **Check Bounds**: Ensure line numbers are within content height
5. **Update Smartly**: Only redraw when data changes
6. **Consider Timing**: Don't update too frequently (>10Hz is usually wasteful)
7. **Handle Errors**: Check `isInitialized()` before using display
8. **Optimize Memory**: Use C-strings instead of String objects

---

**For more information, see the full USAGE_GUIDE.md**
