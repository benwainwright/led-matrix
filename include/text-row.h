#ifndef TEXT_ROW_H
#define TEXT_ROW_H
#include <Arduino.h>
#include "text.h"

class TextRow
{
private:
    std::vector<Text> row;
    size_t fontSize;

public:
    TextRow(std::vector<Text> row);
    size_t size();
    bool isDirty() const;
    String rowString() const;
    Text &operator[](size_t index);
};
#endif
