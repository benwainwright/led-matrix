#ifndef TEXT_ROW_H
#define TEXT_ROW_H
#include <Arduino.h>
#include "text.h"

class TextRow
{
private:
    std::vector<Text> row;
    size_t fontSizeValue;

public:
    TextRow(std::vector<Text> row);
    TextRow(std::vector<Text> row, size_t fontSize);
    size_t size();
    size_t fontSize();
    bool isDirty() const;
    String rowString() const;
    Text &operator[](size_t index);
};
#endif
