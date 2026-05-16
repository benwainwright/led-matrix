#ifndef TAG_H
#define TAG_H

#include "html-node.h"
#include "html-tag-node.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

std::unique_ptr<HtmlTagNode> tag(std::string name, std::vector<std::unique_ptr<HtmlNode>> nodes,
                                 std::map<std::string, std::string> attributes);

std::unique_ptr<HtmlTagNode> tag(std::string name, std::map<std::string, std::string> attributes,
                                 std::vector<std::unique_ptr<HtmlNode>> nodes);

std::unique_ptr<HtmlTagNode> tag(std::string name, std::map<std::string, std::string> attributes);

std::unique_ptr<HtmlTagNode> tag(std::string name, std::vector<std::unique_ptr<HtmlNode>> nodes);

std::unique_ptr<HtmlTagNode> tag(std::string name, std::string textContent);

std::unique_ptr<HtmlTagNode> tag(std::string name);

#endif