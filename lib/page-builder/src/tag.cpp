#include "tag.h"

std::unique_ptr<HtmlTagNode> tag(std::string name, std::vector<std::unique_ptr<HtmlNode>> nodes,
                                 std::map<std::string, std::string> attributes) {
  return std::make_unique<HtmlTagNode>(std::move(name), std::move(nodes), std::move(attributes));
}

std::unique_ptr<HtmlTagNode> tag(std::string name, std::map<std::string, std::string> attributes) {

  return std::make_unique<HtmlTagNode>(std::move(name), std::move(attributes));
}

std::unique_ptr<HtmlTagNode> tag(std::string name, std::vector<std::unique_ptr<HtmlNode>> nodes) {
  return std::make_unique<HtmlTagNode>(std::move(name), std::move(nodes));
}

std::unique_ptr<HtmlTagNode> tag(std::string name, std::string textContent) {
  return std::make_unique<HtmlTagNode>(std::move(name), std::move(textContent));
}