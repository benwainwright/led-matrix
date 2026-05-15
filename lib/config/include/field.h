#ifndef FIELD_H
#define FIELD_H
#include <Arduino.h>
#include <Preferences.h>
#include <memory>
#include <Pagebuilder.h>

class Field
{
public:
    virtual std::unique_ptr<HtmlNode> markup() const = 0;
    virtual const std::string &name() const = 0;
    void handle(const std::string &value);
    std::string value() const;
};
#endif
