#include "html-node.h"
#include <Pagebuilder.h>

#include <memory>
std::unique_ptr<HtmlNode> pageMarkup(std::unique_ptr<HtmlNode> form) {
  auto flex = CssDeclaration("display", "flex");
  auto gap = CssDeclaration("gap", "1rem");
  auto padding = CssDeclaration("padding", "0.5rem");
  auto formRow = std::make_unique<CssSelector>(
      "form div", std::initializer_list<CssDeclaration>{flex, gap, padding});

  auto labelWidth = CssDeclaration("width", "stretch");
  auto labelMaxWidth = CssDeclaration("max-width", "12rem");
  auto formRowLabel = std::make_unique<CssSelector>(
      "form div label", std::initializer_list<CssDeclaration>{labelWidth, labelMaxWidth});

  auto inputWidth = CssDeclaration("width", "stretch");
  auto inputPadding = CssDeclaration("padding", "0 0.5rem");
  auto formRowInput = std::make_unique<CssSelector>(
      "form div input, form div select",
      std::initializer_list<CssDeclaration>{inputWidth, inputPadding});

  auto bodyMaxWidth = CssDeclaration("max-width", "40rem");
  auto font = CssDeclaration("font-family", "sans-serif");
  auto lineHeight = CssDeclaration("line-height", "2rem");
  auto bodyStyle = std::make_unique<CssSelector>(
      "body", std::initializer_list<CssDeclaration>{font, lineHeight, bodyMaxWidth});

  auto submitRowPadding = CssDeclaration("padding", "0.5rem");
  auto submitRowMargin = CssDeclaration("margin-top", "1rem");
  auto submitRow = std::make_unique<CssSelector>(
      ".submitRow", std::initializer_list<CssDeclaration>{submitRowPadding, submitRowMargin});

  auto buttonWidth = CssDeclaration("width", "10rem");
  auto buttonHeight = CssDeclaration("height", "2rem");
  auto submitButton = std::make_unique<CssSelector>(
      ".submitRow button", std::initializer_list<CssDeclaration>{buttonWidth, buttonHeight});

  auto header =
      tag("head", children(tag("style", children(std::move(formRow), std::move(formRowLabel),
                                                 std::move(bodyStyle), std::move(formRowInput),
                                                 std::move(submitButton), std::move(submitRow))),
                           tag("title", "Screen Configuration")));

  auto body =
      tag("body",
          children(tag("h1", "Screen Configuration"),
                   tag("p", children(text("Note: Device will be restarted after you press save"))),
                   std::move(form)));

  return tag("html", children(std::move(header), std::move(body)));
}
