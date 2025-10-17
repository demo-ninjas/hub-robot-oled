#ifndef HUB_OLED_H
#define HUB_OLED_H

#include "SeeedOLED/SeeedOLED.h"
#include "ACROBATIC/ACROBOTIC_SSD1306.h"
#include <Arduino.h>

typedef enum {
  OLED_TYPE_NONE = 0,           // No display connected
  OLED_TYPE_GROVE = 1,          // Grove 0.96 OLED Display 
  OLED_TYPE_SSD1306 = 2,        // eg. Adafruit 1306 Mini OLED Display
} OledDisplayType;

// Maximum number of header lines to prevent excessive memory usage
#define MAX_HEADER_LINES 3
// Maximum characters per line (for largest display)
#define MAX_LINE_CHARS 24

class HubOLED {
  private:
    OledDisplayType oled_type;
    uint8_t oled_start_line;
    uint8_t height;
    uint8_t width;
    uint8_t header_count;
    char header_lines[MAX_HEADER_LINES][MAX_LINE_CHARS + 1];  // +1 for null terminator
    bool initialized;
    uint8_t current_brightness;
    bool is_inverted;
    
    // Helper methods
    void writeToDisplay(uint8_t row, const char* text);
    void clearLine(uint8_t row);
    
  public:
    // Constructor & Initialization
    HubOLED(OledDisplayType oled_type);
    void init();
    bool isInitialized() const;
    
    // Display Properties
    uint8_t getHeight() const;
    uint8_t getWidth() const;
    OledDisplayType getDisplayType() const;
    
    // Basic Text Operations
    void setLine(uint8_t line, const char* msg, bool centered = false);
    void setLine(uint8_t line, const String& msg, bool centered = false);
    void println(const char* msg, bool centered = false);
    void println(const String& msg, bool centered = false);
    void print(const char* msg);
    void print(const String& msg);
    
    // Number and Special Output
    void printNumber(uint8_t line, long number, bool centered = false);
    void printFloat(uint8_t line, float number, uint8_t decimal_places = 2, bool centered = false);
    
    // Display Control
    void clear(bool print_header = true);
    void clearContent();  // Clear only content area (preserve header)
    void setBrightness(uint8_t brightness);  // 0-255
    void setInverted(bool inverted);
    void displayOn();
    void displayOff();
    
    // Header Management
    void setHeader(const char* header_lines[], uint8_t count);
    void setHeader(const char* header);
    void setHeaderLine(uint8_t index, const char* text);
    void printHeader();
    void clearHeader();
    uint8_t getHeaderLineCount() const;
    
    // Scrolling (hardware scrolling where supported)
    void scrollLeft(uint8_t start_page = 0, uint8_t end_page = 7, uint8_t speed = Scroll_5Frames);
    void scrollRight(uint8_t start_page = 0, uint8_t end_page = 7, uint8_t speed = Scroll_5Frames);
    void stopScroll();
    
    // Cursor positioning for manual text placement
    void setCursor(uint8_t row, uint8_t col);
    
    // Advanced Features
    void drawBitmap(const uint8_t* bitmap, int num_bytes, uint8_t bmp_width, uint8_t row, uint8_t col);
    void fillRect(uint8_t row, uint8_t col, uint8_t w, char fill_char = ' ');
    
    // Content area helpers (accounts for header offset)
    uint8_t getContentHeight() const;
    uint8_t getContentStartLine() const;
};

#endif // HUB_OLED_H