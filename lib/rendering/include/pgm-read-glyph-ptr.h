#include <Adafruit_GFX.h>

// Stolen from
// https://github.com/adafruit/Adafruit-GFX-Library/blob/ac6d7c3869a693d406f77b9bfcd486b0673169f0/Adafruit_GFX.cpp#L65-L75
// I don't pretend to understand this

inline GFXglyph* pgm_read_glyph_ptr(const GFXfont* gfxFont, uint8_t c) {
#ifdef __AVR__
  return &(((GFXglyph*)pgm_read_pointer(&gfxFont->glyph))[c]);
#else
  return gfxFont->glyph + c;
#endif //__AVR__
}