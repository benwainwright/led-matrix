#ifndef PAGE_MARKUP_H
#define PAGE_MARKUP_H

#include <memory>
#include "html-node.h"

std::unique_ptr<HtmlNode> pageMarkup(std::unique_ptr<HtmlNode> form);

#endif