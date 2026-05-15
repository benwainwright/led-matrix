#include "form.h"
#include "formData.h"

#include <sstream>

Form::Form(std::vector<std::unique_ptr<Field>> fields) : fields(std::move(fields)) {}

void Form::render(std::ostream &out)
{
}

void Form::handleSubmission(const std::string &formData)
{
    auto data = parseFormData(formData);

    for (auto &field : fields)
    {
        if (data.find(field->name()) != data.end())
        {
            auto theNewValue = data[field->name()];
            field->handle(theNewValue);
        }
    }
}

std::unique_ptr<HtmlNode> Form::markup() const
{
    std::vector<std::unique_ptr<HtmlNode>> fieldNodes;

    for (const auto &field : fields)
    {
        fieldNodes.push_back(field->markup());
    }

    fieldNodes.push_back(tag("button", children(text("Save")), attrs({{"type", "submit"}})));

    return tag("form",
               std::move(fieldNodes),
               attrs({{"method", "POST"}}));
}