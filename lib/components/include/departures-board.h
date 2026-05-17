
#ifndef DEPARTURES_BOARD_H
#define DEPARTURES_BOARD_H

#include <rtt.h>

#include "departures-row.h"
#include "renderable.h"
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <Rendering.h>

class DeparturesBoard : public Renderable {
private:
  std::vector<DepartureRow> rows;
  std::function<void(DeparturesBoard&)> onTick;

public:
  DeparturesBoard(size_t displayWidth, std::function<void(DeparturesBoard&)> onTick);

  void tick() override;
  void setDepartures(std::vector<Departure> departures);
  std::vector<std::shared_ptr<RenderableText>> getText() override;
};

#endif