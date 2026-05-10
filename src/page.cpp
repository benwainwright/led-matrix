#include "page.h"

Page::Page(
    MatrixPanel_I2S_DMA *display,
    std::vector<TextRow> rows)
    : pageDirty(true), rows(rows), display(display)
{
}

void Page::setDirty()
{
    pageDirty = true;
}

bool Page::isDirty()
{
    if (pageDirty)
    {
        return true;
    }

    for (size_t i = 0; i < rows.size(); i++)
    {
        if (rows[i].isDirty())
        {
            return true;
        }
    }

    return false;
}

void Page::render()
{
    if (isDirty())
    {
        display->clearScreen();
        Serial.println(rows.size());
        for (size_t i = 0; i < rows.size(); i++)
        {
            renderRow(rows[i], i);
        }
    }
    pageDirty = false;
}

int16_t Page::getWidthOffsetForCentre(const char *message)
{
    if (display == nullptr)
    {
        return 0;
    }

    int16_t x1;
    int16_t y1;
    uint16_t w;
    uint16_t h;

    display->getTextBounds(message, 0, 0, &x1, &y1, &w, &h);
    return ((display->width() - w) / 2) - x1;
}

int16_t Page::getHeightOffsetForCentre(const char *message, uint8_t index, uint8_t count)
{
    if (display == nullptr)
    {
        return 0;
    }

    int16_t x1;
    int16_t y1;
    uint16_t w;
    uint16_t h;

    display->getTextBounds(message, 0, 0, &x1, &y1, &w, &h);
    float centreY = (display->height() - h) / 2.0f - y1;
    float rowOffset = (index - ((count - 1) / 2.0f)) * h;

    return centreY + rowOffset;
}

int16_t Page::getWidthOfTextItem(const Text &text, int16_t x, int16_t y)
{

    if (display == nullptr)
    {
        return 0;
    }

    int16_t x1;
    int16_t y1;
    uint16_t w;
    uint16_t h;

    String content = text.content();
    display->getTextBounds(content.c_str(), x, y, &x1, &y1, &w, &h);
    return w;
}

void Page::renderRow(TextRow &row, uint8_t index)
{
    auto raw = row.rowString();
    display->setTextSize(1);
    display->setTextWrap(false);
    auto widthOffset = getWidthOffsetForCentre(raw.c_str());
    auto heightOffset = getHeightOffsetForCentre(raw.c_str(), index, rows.size());

    display->setCursor(widthOffset, heightOffset);

    for (size_t i = 0; i < row.size(); i++)
    {

        Serial.println();
        Serial.printf("content: %s, x: %d, y: %d", row[i].content(), widthOffset, heightOffset);
        Serial.println();

        display->setTextColor(
            display->color565(
                row[i].color().red,
                row[i].color().green,
                row[i].color().blue));

        display->print(row[i].content());

        row[i].markRendered();
    }
}
