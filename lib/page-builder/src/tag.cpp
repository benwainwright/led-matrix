#include "tag.h"
#include "text-func.h"

std::unique_ptr<HtmlTagNode> tag(std::string name, std::vector<std::unique_ptr<HtmlNode>> nodes,
                                 std::map<std::string, std::string> attributes) {

  return std::make_unique<HtmlTagNode>(std::move(name), std::move(nodes), std::move(attributes));
}

std::unique_ptr<HtmlTagNode> tag(std::string name, std::map<std::string, std::string> attributes,
                                 std::vector<std::unique_ptr<HtmlNode>> nodes) {

  return std::make_unique<HtmlTagNode>(std::move(name), std::move(nodes), std::move(attributes));
}

std::unique_ptr<HtmlTagNode> tag(std::string name, std::map<std::string, std::string> attributes) {
  return std::make_unique<HtmlTagNode>(std::move(name), std::vector<std::unique_ptr<HtmlNode>>{},
                                       std::move(attributes));
}

std::unique_ptr<HtmlTagNode> tag(std::string name, std::vector<std::unique_ptr<HtmlNode>> nodes) {
  return std::make_unique<HtmlTagNode>(std::move(name), std::move(nodes),
                                       std::map<std::string, std::string>{}

  );
}

std::unique_ptr<HtmlTagNode> tag(std::string name, std::string textContent) {
  std::vector<std::unique_ptr<HtmlNode>> nodes;
  nodes.push_back(text(std::move(textContent)));

  return std::make_unique<HtmlTagNode>(std::move(name), std::move(nodes),
                                       std::map<std::string, std::string>{}

  );
}

std::unique_ptr<HtmlTagNode> tag(std::string name) {
  return std::make_unique<HtmlTagNode>(std::move(name), std::vector<std::unique_ptr<HtmlNode>>{},
                                       std::map<std::string, std::string>{}

  );
}