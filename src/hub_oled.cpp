#include "hub_oled.h"

// Constructor
HubOLED::HubOLED(OledDisplayType oled_type) 
  : oled_type(oled_type),
    oled_start_line(0),
    height(8),
    width(16),
    header_count(0),
    initialized(false),
    current_brightness(255),
    is_inverted(false) {
  // Initialize header lines to empty strings
  for (uint8_t i = 0; i < MAX_HEADER_LINES; i++) {
    header_lines[i][0] = '\0';
  }
}

// Initialize the display
void HubOLED::init() {
  if (oled_type == OLED_TYPE_NONE) {
    initialized = false;
    return;
  }
  
  if (oled_type == OLED_TYPE_GROVE) {    
    SeeedOled.init();
    SeeedOled.clearDisplay();
    SeeedOled.setNormalDisplay();
    SeeedOled.setPageMode();
    height = 8;
    width = 16;
  } else if (oled_type == OLED_TYPE_SSD1306) {
    ssd1306_oled.init();
    ssd1306_oled.setNormalDisplay();
    ssd1306_oled.setPageMode();
    ssd1306_oled.clearDisplay();
    ssd1306_oled.setFont(font5x7);
    ssd1306_oled.setTextXY(0, 0);
    height = 8;
    width = 24;
  }

  initialized = true;
  delay(50);
  printHeader();
}

bool HubOLED::isInitialized() const {
  return initialized;
}

// Display Properties
uint8_t HubOLED::getHeight() const {
  return height;
}

uint8_t HubOLED::getWidth() const {
  return width;
}

OledDisplayType HubOLED::getDisplayType() const {
  return oled_type;
}

uint8_t HubOLED::getContentHeight() const {
  return height - oled_start_line;
}

uint8_t HubOLED::getContentStartLine() const {
  return oled_start_line;
}

// Header Management
void HubOLED::setHeader(const char* header_lines_arr[], uint8_t count) {
  if (!initialized) return;
  
  header_count = (count < MAX_HEADER_LINES) ? count : MAX_HEADER_LINES;
  for (uint8_t i = 0; i < header_count; i++) {
    strncpy(header_lines[i], header_lines_arr[i], MAX_LINE_CHARS);
    header_lines[i][MAX_LINE_CHARS] = '\0';  // Ensure null termination
  }
  oled_start_line = header_count;
}

void HubOLED::setHeader(const char* header) {
  if (!initialized || !header) return;
  
  header_count = 0;
  size_t start = 0;
  size_t len = strlen(header);
  
  for (size_t i = 0; i <= len && header_count < MAX_HEADER_LINES; i++) {
    if (header[i] == '\n' || header[i] == '\0') {
      size_t line_len = i - start;
      if (line_len > MAX_LINE_CHARS) {
        line_len = MAX_LINE_CHARS;
      }
      strncpy(header_lines[header_count], header + start, line_len);
      header_lines[header_count][line_len] = '\0';
      header_count++;
      start = i + 1;
    }
  }
  
  oled_start_line = header_count;
}

void HubOLED::setHeaderLine(uint8_t index, const char* text) {
  if (!initialized || !text || index >= MAX_HEADER_LINES) return;
  
  strncpy(header_lines[index], text, MAX_LINE_CHARS);
  header_lines[index][MAX_LINE_CHARS] = '\0';
  
  if (index >= header_count) {
    header_count = index + 1;
    oled_start_line = header_count;
  }
}

void HubOLED::printHeader() {
  if (!initialized) return;
  
  for (uint8_t i = 0; i < header_count; i++) {
    setLine(i, header_lines[i], true);
  }
}

void HubOLED::clearHeader() {
  if (!initialized) return;
  
  for (uint8_t i = 0; i < header_count; i++) {
    clearLine(i);
    header_lines[i][0] = '\0';
  }
  header_count = 0;
  oled_start_line = 0;
}

uint8_t HubOLED::getHeaderLineCount() const {
  return header_count;
}

// Helper method to write text to display at specific row
void HubOLED::writeToDisplay(uint8_t row, const char* text) {
  if (!initialized || row >= height) return;
  
  if (oled_type == OLED_TYPE_GROVE) {
    SeeedOled.setTextXY(row, 0);
    SeeedOled.putString(text);
  } else if (oled_type == OLED_TYPE_SSD1306) {
    ssd1306_oled.setTextXY(row, 0);
    ssd1306_oled.putString(text);
  }
}

// Helper method to clear a specific line
void HubOLED::clearLine(uint8_t row) {
  if (!initialized || row >= height) return;
  
  char empty_line[MAX_LINE_CHARS + 1];
  memset(empty_line, ' ', width);
  empty_line[width] = '\0';
  writeToDisplay(row, empty_line);
}

// Text Operations - char* version (most efficient)
void HubOLED::setLine(uint8_t line, const char* msg, bool centered) {
  if (!initialized || !msg) return;
  
  // Calculate actual row accounting for header
  uint8_t row = oled_start_line + line;
  if (row >= height) return;
  
  // Build output line efficiently using stack buffer
  char output_line[MAX_LINE_CHARS + 1];
  size_t msg_len = strlen(msg);
  if (msg_len > width) {
    msg_len = width;
  }
  
  size_t padding_left = 0;
  size_t padding_right = width - msg_len;
  
  if (centered && msg_len < width) {
    padding_left = (width - msg_len) / 2;
    padding_right = width - msg_len - padding_left;
  }
  
  // Fill with spaces and message
  memset(output_line, ' ', padding_left);
  memcpy(output_line + padding_left, msg, msg_len);
  memset(output_line + padding_left + msg_len, ' ', padding_right);
  output_line[width] = '\0';
  
  writeToDisplay(row, output_line);
}

// String version (convenience wrapper)
void HubOLED::setLine(uint8_t line, const String& msg, bool centered) {
  setLine(line, msg.c_str(), centered);
}

// Print to next available line (auto-advance)
static uint8_t current_print_line = 0;

void HubOLED::println(const char* msg, bool centered) {
  if (!initialized) return;
  setLine(current_print_line, msg, centered);
  current_print_line++;
  if (current_print_line >= getContentHeight()) {
    current_print_line = 0;
  }
}

void HubOLED::println(const String& msg, bool centered) {
  println(msg.c_str(), centered);
}

void HubOLED::print(const char* msg) {
  println(msg, false);
}

void HubOLED::print(const String& msg) {
  println(msg.c_str(), false);
}

// Number printing
void HubOLED::printNumber(uint8_t line, long number, bool centered) {
  if (!initialized) return;
  
  char buffer[24];
  ltoa(number, buffer, 10);
  setLine(line, buffer, centered);
}

void HubOLED::printFloat(uint8_t line, float number, uint8_t decimal_places, bool centered) {
  if (!initialized) return;
  
  char buffer[24];
  dtostrf(number, 0, decimal_places, buffer);
  setLine(line, buffer, centered);
}

// Display Control
void HubOLED::clear(bool print_header) {
  if (!initialized) return;
  
  if (oled_type == OLED_TYPE_GROVE) {
    SeeedOled.clearDisplay();
  } else if (oled_type == OLED_TYPE_SSD1306) {
    for (uint8_t i = 0; i < height; i++) {
      clearLine(i);
    }
  }

  current_print_line = 0;
  
  if (print_header) {
    printHeader();
  }
}

void HubOLED::clearContent() {
  if (!initialized) return;
  
  for (uint8_t i = oled_start_line; i < height; i++) {
    clearLine(i);
  }
  current_print_line = 0;
}

void HubOLED::setBrightness(uint8_t brightness) {
  if (!initialized) return;
  
  current_brightness = brightness;
  
  if (oled_type == OLED_TYPE_GROVE) {
    SeeedOled.setBrightness(brightness);
  } else if (oled_type == OLED_TYPE_SSD1306) {
    ssd1306_oled.setBrightness(brightness);
  }
}

void HubOLED::setInverted(bool inverted) {
  if (!initialized) return;
  
  is_inverted = inverted;
  
  if (oled_type == OLED_TYPE_GROVE) {
    if (inverted) {
      SeeedOled.setInverseDisplay();
    } else {
      SeeedOled.setNormalDisplay();
    }
  } else if (oled_type == OLED_TYPE_SSD1306) {
    if (inverted) {
      ssd1306_oled.setInverseDisplay();
    } else {
      ssd1306_oled.setNormalDisplay();
    }
  }
}

void HubOLED::displayOn() {
  if (!initialized) return;
  
  if (oled_type == OLED_TYPE_GROVE) {
    SeeedOled.sendCommand(SeeedOLED_Display_On_Cmd);
  } else if (oled_type == OLED_TYPE_SSD1306) {
    ssd1306_oled.displayOn();
  }
}

void HubOLED::displayOff() {
  if (!initialized) return;
  
  if (oled_type == OLED_TYPE_GROVE) {
    SeeedOled.sendCommand(SeeedOLED_Display_Off_Cmd);
  } else if (oled_type == OLED_TYPE_SSD1306) {
    ssd1306_oled.displayOff();
  }
}

// Scrolling
void HubOLED::scrollLeft(uint8_t start_page, uint8_t end_page, uint8_t speed) {
  if (!initialized) return;
  
  if (oled_type == OLED_TYPE_GROVE) {
    SeeedOled.setHorizontalScrollProperties(Scroll_Left, start_page, end_page, speed);
    SeeedOled.activateScroll();
  } else if (oled_type == OLED_TYPE_SSD1306) {
    ssd1306_oled.setHorizontalScrollProperties(false, start_page, end_page, speed);
    ssd1306_oled.activateScroll();
  }
}

void HubOLED::scrollRight(uint8_t start_page, uint8_t end_page, uint8_t speed) {
  if (!initialized) return;
  
  if (oled_type == OLED_TYPE_GROVE) {
    SeeedOled.setHorizontalScrollProperties(Scroll_Right, start_page, end_page, speed);
    SeeedOled.activateScroll();
  } else if (oled_type == OLED_TYPE_SSD1306) {
    ssd1306_oled.setHorizontalScrollProperties(true, start_page, end_page, speed);
    ssd1306_oled.activateScroll();
  }
}

void HubOLED::stopScroll() {
  if (!initialized) return;
  
  if (oled_type == OLED_TYPE_GROVE) {
    SeeedOled.deactivateScroll();
  } else if (oled_type == OLED_TYPE_SSD1306) {
    ssd1306_oled.deactivateScroll();
  }
}

// Cursor positioning
void HubOLED::setCursor(uint8_t row, uint8_t col) {
  if (!initialized || row >= height) return;
  
  if (oled_type == OLED_TYPE_GROVE) {
    SeeedOled.setTextXY(row, col);
  } else if (oled_type == OLED_TYPE_SSD1306) {
    ssd1306_oled.setTextXY(row, col);
  }
}

// Advanced Features
void HubOLED::drawBitmap(const uint8_t* bitmap, int num_bytes, uint8_t bmp_width, uint8_t row, uint8_t col) {
  if (!initialized || !bitmap) return;
  

  // Each byte represents 8 vertical pixels, so draw the bitmap moving down a row after every bmp_width bytes
  for (uint8_t r = 0; r < num_bytes / bmp_width; r++) {
    setCursor(row + r, col);
    // Draw the bitmap for the current row
    if (oled_type == OLED_TYPE_GROVE) {
      SeeedOled.drawBitmap((unsigned char*)(bitmap + r * bmp_width), bmp_width);
    } else if (oled_type == OLED_TYPE_SSD1306) {
      ssd1306_oled.drawBitmap((unsigned char*)(bitmap + r * bmp_width), bmp_width);
    }
  }
}

void HubOLED::fillRect(uint8_t row, uint8_t col, uint8_t w, char fill_char) {
  if (!initialized || row >= height || col >= width) return;

  uint8_t fill_width = (w < (width - col)) ? w : (width - col);

  // Create a buffer with the fill_char and write the whole segment at once
  char buffer[MAX_LINE_CHARS + 1];
  memset(buffer, fill_char, fill_width);
  buffer[fill_width] = '\0';

  // Set cursor and write the buffer
  setCursor(row, col);
  if (oled_type == OLED_TYPE_GROVE) {
    SeeedOled.putString(buffer);
  } else if (oled_type == OLED_TYPE_SSD1306) {
    ssd1306_oled.putString(buffer);
  }
}
