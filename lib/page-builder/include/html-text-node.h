
#ifndef HTML_TEXT_TAG_H
#define HTML_TEXT_TAG_H

#include <string>
#include <vector>
#include <memory>
#include <map>

#include "html-node.h"

class HtmlTextNode : public HtmlNode
{
private:
    std::string text;

public:
    HtmlTextNode(std::string text);

    void render(std::ostream &out) const;
};

#endif
