#ifndef HTML_TAG_H
#define HTML_TAG_H

#include <string>
#include <vector>
#include <memory>
#include <map>

#include "html-node.h"

class HtmlTagNode : public HtmlNode
{
private:
  std::string name;
  std::vector<std::unique_ptr<HtmlNode>> nodes;
  std::map<std::string, std::string> attributes;

public:
  HtmlTagNode(
      std::string name,
      std::vector<std::unique_ptr<HtmlNode>> nodes,
      std::map<std::string, std::string> attributes);

  HtmlTagNode(
      std::string name,
      std::map<std::string, std::string> attributes);

  HtmlTagNode(
      std::string name,
      std::vector<std::unique_ptr<HtmlNode>> nodes);

  HtmlTagNode(
      std::string name,
      std::string textContent);

  void render(std::ostream &out) const override;
};

#endif