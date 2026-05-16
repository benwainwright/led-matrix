#include "html-node.h"
#include <Pagebuilder.h>

#include <memory>
std::unique_ptr<HtmlNode> pageMarkup(std::unique_ptr<HtmlNode> form) {
  auto flex = CssDeclaration("display", "flex");
  auto gap = CssDeclaration("gap", "1rem");
  auto padding = CssDeclaration("padding", "0.5rem");

  auto formRow = std::make_unique<CssSelector>(
      "form div", std::initializer_list<CssDeclaration>{flex, gap, padding});

  auto header = tag("head", children(tag("style", children(std::move(formRow))),
                                     tag("title", "Site Configuration")));

  auto body = tag("body", children(tag("h1", "Configuration"), std::move(form)));

  return tag("html", children(std::move(header), std::move(body)));
}