#ifndef RENDERER_H
#define RENDERER_H

#include <Arduino.h>
#include "page.h"

class Renderer
{
    std::vector<Page> pages;
    uint8_t page;

public:
    Renderer(std::vector<Page> pages);
    void render();
    void showPage(uint8_t number);
};
#endif