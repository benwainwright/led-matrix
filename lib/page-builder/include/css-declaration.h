#ifndef CSS_DECLARATION_H
#define CSS_DECLARATION_H

#include <string>

class CssDeclaration
{
    std::string property;
    std::string value;

public:
    CssDeclaration(std::string property, std::string value);
    void render(std::ostream &out) const;
};

#endif