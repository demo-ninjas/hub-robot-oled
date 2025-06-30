#ifndef HUB_OLED_H
#define HUB_OLED_H

#include "SeeedOLED/SeeedOLED.h"
#include "ACROBATIC/ACROBOTIC_SSD1306.h"
#include <string>

typedef enum {
  OLED_TYPE_NONE = 0,           // No display connected
  OLED_TYPE_GROVE = 1,          // Grove 0.96 OLED Display 
	OLED_TYPE_SSD1306 = 2,	      // eg. Adafruit 1306 Mini OLED Display
} OledDisplayType;

#include <vector>

class HubOLED {
  private:
    OledDisplayType oled_type;
    unsigned int oled_start_line;
    unsigned int height = 8;
    unsigned int width = 16;
    std::vector<String> header;
  public:
    HubOLED(OledDisplayType oled_type);
    void init();
    void setLine(unsigned int line, const String& msg, bool centered);
    void clear(bool print_header);
    void setHeader(const std::vector<String>& header_lines);
    void setHeader(String header);
    void printHeader();
};;

#endif // HUB_OLED_H