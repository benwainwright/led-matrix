#ifndef HYDRATABLE_FIELD_H
#define HYDRATABLE_FIELD_H
#include "field.h"

template <typename Derived> class HydratableField : public Field {
protected:
  std::function<void(Derived&)> hydrate;
  virtual std::unique_ptr<HtmlNode> getMarkup() = 0;

public:
  std::unique_ptr<HtmlNode> markup() override {
    this->runHydrate();
    return this->getMarkup();
  }

  HydratableField(std::function<void(Derived&)> hydrate, const std::string& defaultValue)
      : Field(defaultValue), hydrate(std::move(hydrate)) {}

  void runHydrate() {
    if (hydrate) {
      hydrate(static_cast<Derived&>(*this));
    }
  }
};
#endif