#ifndef CHILDREN_H
#define CHILDREN_H

#include <vector>
#include <memory>
#include "html-node.h"

template <typename... Children>
std::vector<std::unique_ptr<HtmlNode>> children(Children &&...c)
{
    std::vector<std::unique_ptr<HtmlNode>> result;
    result.reserve(sizeof...(c));
    (result.push_back(std::move(c)), ...);
    return result;
}

#endif