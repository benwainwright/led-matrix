#include "css-declaration.h"

#include <iostream>
#include <sstream>

CssDeclaration::CssDeclaration(std::string property, std::string value)
    : property(std::move(property)), value(std::move(value)) {}

void CssDeclaration::render(std::ostream& out) const { out << property << ": " << value << ";\n"; }
