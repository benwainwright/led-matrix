#ifndef PAGE_MARKUP_H
#define PAGE_MARKUP_H

#include "html-node.h"
#include <memory>

std::unique_ptr<HtmlNode> pageMarkup(std::unique_ptr<HtmlNode> form);

#endif