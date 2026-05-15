#ifndef HTML_NODE_H
#define HTML_NODE_H
#include <string>

class HtmlNode
{
public:
    virtual void render(std::ostream &out) const = 0;
};

#endif