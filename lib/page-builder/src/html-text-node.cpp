
#include "html-text-node.h"
#include "html-node.h"
#include <memory>
#include <sstream>
#include <vector>

HtmlTextNode::HtmlTextNode(std::string text) : text(text) {}

void HtmlTextNode::render(std::ostream& out) const { out << text; }
