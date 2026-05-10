#include "text-row.h"

TextRow::TextRow(std::vector<Text> row) : TextRow(row, 1) {}
TextRow::TextRow(std::vector<Text> row, size_t fontSize) : row(row), fontSizeValue(fontSize) {}

size_t TextRow::size()
{
    return row.size();
}

bool TextRow::isDirty() const
{
    for (size_t i = 0; i < row.size(); i++)
    {
        if (row[i].isDirty())
        {
            return true;
        }
    }
    return false;
}

Text &TextRow::operator[](size_t index)
{
    return row[index];
}

String TextRow::rowString() const
{
    String buffer;

    for (size_t i = 0; i < row.size(); i++)
    {
        buffer += row[i].content();
    }

    return buffer;
}

size_t TextRow::fontSize()
{
    return fontSizeValue;
}
