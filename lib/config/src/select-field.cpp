#include <Pagebuilder.h>

#include "select-field.h"

SelectField::SelectField(const std::string& name, const std::string& label,
                         std::vector<SelectOption> options)
    : options(std::move(options)), nameValue(name) {}

std::unique_ptr<HtmlNode> SelectField::markup() const {
    return tag("div",
               children(
                   tag("label", children(text(label.c_str())), attrs({{"for", nameValue.c_str()}})),
                   tag("select")