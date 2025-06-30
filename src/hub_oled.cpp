#include "hub_oled.h"
#include <definitions.h>

HubOLED::HubOLED(OledDisplayType oled_type) {
  this->oled_type = oled_type;
  this->oled_start_line = 0;
  this->header = std::vector<String>();
}

void HubOLED::init() {
  if (this->oled_type == OLED_TYPE_GROVE) {    
    SeeedOled.init();                             // Initialze SEEED OLED display
    SeeedOled.clearDisplay();                     // Clear the screen and set start position to top left corner
    SeeedOled.setNormalDisplay();                 // Set display to normal mode (i.e non-inverse mode)
    SeeedOled.setPageMode();                      // Set addressing mode to Page Mode
    this->height = 8;
    this->width = 16;
  } else if (this->oled_type == OLED_TYPE_SSD1306) {
    ssd1306_oled.init();                      // Initialze SSD1306 OLED display
    ssd1306_oled.setNormalDisplay();
    ssd1306_oled.setPageMode();
    ssd1306_oled.clearDisplay();              // Clear screen
    ssd1306_oled.setFont(font5x7);            // Set font type (default 8x8)
    ssd1306_oled.setTextXY(0,0);              // Set cursor position, start of line 0
    this->height = 8;
    this->width = 24;
  }

  delay(50);
  this->printHeader();
}

void HubOLED::setHeader(const std::vector<String>& header_lines) {
  this->header = header_lines;
  this->oled_start_line = header_lines.size();
}

void HubOLED::setHeader(String header) {
  this->header = std::vector<String>();
  size_t start = 0;
  int end = header.indexOf('\n');
  while (end != -1) {
    this->header.push_back(header.substring(start, end));
    start = end + 1;
    end = header.indexOf('\n', start);
  }
  this->header.push_back(header.substring(start));
  this->oled_start_line = this->header.size();
}

void HubOLED::printHeader() {
  for (unsigned int i = 0; i < this->header.size(); i++) {
    this->setLine(i - this->oled_start_line, this->header[i], true);
  }
}

void HubOLED::setLine(unsigned int line, const String& msg, bool centered) {
  unsigned int row = constrain(this->oled_start_line + line, 0, this->height - 1);
  unsigned int padding = this->width - msg.length();
  bool addExtra = false;
  String print_line;
  if (centered) {
    padding = (this->width - msg.length()) / 2;
    addExtra = (this->width - msg.length()) % 2 == 1;
    print_line.reserve(this->width);
    for (unsigned int i = 0; i < padding; ++i) {
      print_line += ' ';
    }
  }

  print_line += msg;

  // Clear the rest of the line
  for (unsigned int i = 0; i < padding; ++i) {
    print_line += ' ';
  }
  if (centered && addExtra) {
    print_line += ' ';
  }
  

  if (this->oled_type == OLED_TYPE_GROVE) {
    SeeedOled.setTextXY(row, 0);
    SeeedOled.putString(print_line.c_str());
  } else if (this->oled_type == OLED_TYPE_SSD1306) {
    ssd1306_oled.setTextXY(row, 0);
    ssd1306_oled.putString(print_line);
  }
}


void HubOLED::clear(bool print_header = true) {
  if (this->oled_type == OLED_TYPE_GROVE) {
    SeeedOled.clearDisplay();
  } else if (this->oled_type == OLED_TYPE_SSD1306) {
    for (int i = 0; i < 8; i++) {
      ssd1306_oled.setTextXY(i, 0);
      ssd1306_oled.putString("                        ");
    }
    // oled.clearDisplay(); // Doesn't work because the library we're using doesn't clear the whole screen
  }

  if (print_header) {
    this->printHeader();
  }
}