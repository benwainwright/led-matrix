
#ifndef DEPARTURES_BOARD_H
#define DEPARTURES_BOARD_H

#include <rtt.h>

#include "departures-row.h"
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <Rendering.h>

class DeparturesBoard {
private:
  std::vector<DepartureRow> rows;

public:
  DeparturesBoard(std::shared_ptr<MatrixPanel_I2S_DMA> display, size_t displayWidth);

  void tick(std::vector<Departure> departures);

  std::vector<std::shared_ptr<RenderableText>> getText();
};

#endif