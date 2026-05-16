#ifndef CSS_SELECTOR_H
#define CSS_SELECTOR_H

#include <vector>

#include "css-declaration.h"
#include "html-node.h"

class CssSelector : public HtmlNode {
private:
  std::string selector;
  std::vector<CssDeclaration> declarations;

public:
  CssSelector(std::string selector, std::vector<CssDeclaration>);

  void render(std::ostream& out) const;
};

#endif