#include "html-tag-node.h"
#include "html-node.h"
#include "html-text-node.h"
#include <memory>
#include <sstream>
#include <vector>

static std::vector<std::unique_ptr<HtmlNode>> textNodes(std::string text) {
  std::vector<std::unique_ptr<HtmlNode>> nodes;
  nodes.push_back(std::make_unique<HtmlTextNode>(std::move(text)));
  return nodes;
}

HtmlTagNode::HtmlTagNode(std::string name, std::vector<std::unique_ptr<HtmlNode>> nodes)
    : HtmlTagNode(std::move(name), std::move(nodes), {})

{}

HtmlTagNode::HtmlTagNode(std::string name, std::map<std::string, std::string> attributes)
    : HtmlTagNode(std::move(name), {}, std::move(attributes)) {}

HtmlTagNode::HtmlTagNode(std::string name, std::vector<std::unique_ptr<HtmlNode>> nodes,
                         std::map<std::string, std::string> attributes)
    : name(std::move(name)), nodes(std::move(nodes)), attributes(std::move(attributes)) {}

HtmlTagNode::HtmlTagNode(std::string name, std::string textContent)
    : HtmlTagNode(std::move(name), textNodes(textContent), {}) {}

HtmlTagNode::HtmlTagNode(std::string name, std::string textContent)
    : HtmlTagNode(std::move(name), textNodes(textContent), {}) {}

void HtmlTagNode::render(std::ostream& out) const {
  out << "<" << name;

  for (const auto& pair : attributes) {
    out << " " << pair.first << "=\"" << pair.second << "\" ";
  }

  out << ">";

  for (const auto& child : nodes) {
    child->render(out);
  }

  out << "</" << name << ">";
}
