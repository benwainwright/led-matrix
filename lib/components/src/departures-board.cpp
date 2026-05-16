#include "departures-board.h"

DeparturesBoard::DeparturesBoard(std::shared_ptr<MatrixPanel_I2S_DMA> display, size_t displayWidth)
    :

      rows(std::vector<DepartureRow>{
          DepartureRow(display, displayWidth), DepartureRow(display, displayWidth),
          DepartureRow(display, displayWidth), DepartureRow(display, displayWidth)

      }) {};

void DeparturesBoard::tick(std::vector<Departure> departures) {
  if (departures.size() < 4) {
    return;
  }
  for (int i = 0; i < 4; i++) {
    rows[i].setContent(departures[i]);
  }
}

std::vector<std::shared_ptr<RenderableText>> DeparturesBoard::getText() {
  std::vector<std::shared_ptr<RenderableText>> text;

  for (auto& row : rows) {
    text.push_back(row.getText());
  }

  return text;
}