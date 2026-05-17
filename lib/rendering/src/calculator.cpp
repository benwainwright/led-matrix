#include "calculator.h"
#include "masked-display.h"
#include "pgm-read-glyph-ptr.h"

int calculateWidth(const char* string, const GFXfont* font, int fontSize) {
  int length = strlen(string);
  int advance = 0;
  for (int i = 0; i < length; i++) {
    auto c = string[i];
    GFXglyph* glyph = pgm_read_glyph_ptr(font, c - font->first);
    advance += fontSize * glyph->xAdvance;
  }
  return advance;
}

int16_t getRenderedWidth(MaskedDisplay& display, std::string content, int x, int y) {

  int16_t x1;
  int16_t y1;
  uint16_t w;
  uint16_t h;

  display.getTextBounds(content.c_str(), x, y, &x1, &y1, &w, &h);
  return w;
}

int16_t getRenderedHeight(MaskedDisplay& display, std::string content, int x, int y) {

  int16_t x1;
  int16_t y1;
  uint16_t w;
  uint16_t h;

  display.getTextBounds(content.c_str(), x, y, &x1, &y1, &w, &h);
  return h;
}

int16_t getBoundaryX(MaskedDisplay& display, std::string content, int x, int y) {

  int16_t x1;
  int16_t y1;
  uint16_t w;
  uint16_t h;

  display.getTextBounds(content.c_str(), x, y, &x1, &y1, &w, &h);
  return x1;
}

int16_t getBoundaryY(MaskedDisplay& display, std::string content, int x, int y) {

  int16_t x1;
  int16_t y1;
  uint16_t w;
  uint16_t h;

  display.getTextBounds(content.c_str(), x, y, &x1, &y1, &w, &h);
  return y1;
}