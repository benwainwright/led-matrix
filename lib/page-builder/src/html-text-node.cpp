
#include "html-text-node.h"
#include "html-node.h"
#include <vector>
#include <sstream>
#include <memory>

HtmlTextNode::HtmlTextNode(std::string text) : text(text)
{
}

void HtmlTextNode::render(std::ostream &out) const
{
    out << text;
}
