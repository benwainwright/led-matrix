#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <Arduino.h>
#include "text-row.h"

class Renderable
{
public:
    virtual std::vector<TextRow> text();
};
#endif