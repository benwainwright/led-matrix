#include "css-selector.h"
#include <sstream>

CssSelector::CssSelector(std::string selector, std::vector<CssDeclaration> declarations)
    : selector(std::move(selector)), declarations(std::move(declarations)) {}

void CssSelector::render(std::ostream& out) const {
  out << selector << " {\n";

  for (auto& declaration : declarations) {
    out << "  ";
    declaration.render(out);
  }

  out << "}\n";
}