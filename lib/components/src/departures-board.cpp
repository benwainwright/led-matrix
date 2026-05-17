#include "departures-board.h"

DeparturesBoard::DeparturesBoard(size_t displayWidth, std::function<void(DeparturesBoard&)> onTick)
    :

      rows(std::vector<DepartureRow>{DepartureRow(displayWidth), DepartureRow(displayWidth),
                                     DepartureRow(displayWidth), DepartureRow(displayWidth)}),
      onTick(onTick) {};

void DeparturesBoard::setDepartures(const std::vector<Departure>& departures) {
  if (departures.size() < 4) {
    return;
  }
  for (int i = 0; i < 4; i++) {
    rows[i].setContent(departures[i]);
  }
}

void DeparturesBoard::tick() {
  if (onTick != nullptr) {
    onTick(*this);
  }
}

std::vector<std::shared_ptr<RenderableText>> DeparturesBoard::getText() {
  std::vector<std::shared_ptr<RenderableText>> text;

  for (auto& row : rows) {
    text.push_back(row.getText());
  }

  return text;
}
