#include "text-func.h"
#include <memory>

std::unique_ptr<HtmlNode> text(std::string name)
{
    return std::make_unique<HtmlTextNode>(std::move(name));
}