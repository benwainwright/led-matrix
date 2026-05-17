#ifndef PAGE_H
#define PAGE_H

#include "renderable-text-row.h"
#include "renderable.h"
#include "text-row.h"
#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

class Page {
private:
  bool pageDirty;
  std::unique_ptr<Renderable> rows;
  std::shared_ptr<MatrixPanel_I2S_DMA> display;
  size_t gap;
  const GFXfont* defaultFont;
  bool verticallyAlignRows;
  void renderRow(RenderableTextRow& row, uint8_t index);
  void updateRow(RenderableTextRow& row, uint8_t index);
  void positionRowContents(RenderableTextRow& row, const GFXfont* defaultFont);

  void clearText(Text& textItem, int size);
  int16_t getHeightOffsetForCentre(int16_t x, int16_t y, const char* message, uint8_t index, uint8_t count,
                                   const GFXfont* font, size_t fontSize);
  int16_t getWidthOffsetForCentre(int16_t x, int16_t y, const char* message);
  void renderText(Text& textItem, int size);
  int16_t getWidthOfTextItem(const Text& text, int16_t x, int16_t y);
  bool isDirty();

public:
  Page(std::shared_ptr<MatrixPanel_I2S_DMA> display, std::unique_ptr<Renderable> rows, const GFXfont* defaultFont,
       size_t gap = 1, bool verticallyAlignRows = true);
  void setRow(uint8_t rowNumber, std::vector<Text> row);
  void render();
  void clear();
  void tick();
  void init();
  void setDirty();
};
#endif
