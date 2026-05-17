#include "andala.h"
#include "app.h"
#include "constants.h"
#include <Arduino.h>
#include <Components.h>
#include <Rendering.h>

#include "display.h"
#include <Adafruit_GFX.h>

void initDisplay(App* app) {
  HUB75_I2S_CFG::i2s_pins _pins = {R1_PIN,

                                   /**
                                    * I've swapped the blue and green pins round, because
                                    * even though I've wired everything up correctly, blue pixels
                                    * are appearing green and vice versa
                                    */
                                   B1_PIN, G1_PIN,
                                   /**
                                    * End swap
                                    */

                                   R2_PIN,

                                   /**
                                    * See above
                                    */
                                   B2_PIN, G2_PIN,
                                   /** End swap */

                                   A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, LAT_PIN, OE_PIN, CLK_PIN};
  HUB75_I2S_CFG mxconfig(DISPLAY_WIDTH, DISPLAY_HEIGHT, 1, _pins);

  mxconfig.driver = HUB75_I2S_CFG::FM6126A;
  mxconfig.clkphase = false;
  mxconfig.min_refresh_rate = 120;
  mxconfig.i2sspeed = HUB75_I2S_CFG::HZ_16M;

  app->display = std::make_shared<MatrixPanel_I2S_DMA>(mxconfig);
  app->display->begin();
  app->display->setFont(&andala4pt7b);
}

std::map<std::string, std::unique_ptr<Renderable>> setupRenderables(App* app) {
  std::map<std::string, std::unique_ptr<Renderable>> renderables;
  renderables[CLOCK_PAGE] = std::make_unique<Clock>();

  auto updateMedia = [app](MediaDisplay& media) { media.setMedia(app->state.title(), app->state.artist()); };
  renderables[MEDIA_PAGE] = std::make_unique<MediaDisplay>(DISPLAY_WIDTH, updateMedia);

  auto updateDepartures = [app](DeparturesBoard& board) { board.setDepartures(app->departures); };
  renderables[TRAINS_PAGE] = std::make_unique<DeparturesBoard>(DISPLAY_WIDTH, updateDepartures);

  return renderables;
}

void displayLoop(void* parameter)

{
  App* app = static_cast<App*>(parameter);
  initDisplay(app);

  xEventGroupWaitBits(app->finishedDataInitialisationEventGroup, DATA_READY_BIT, pdFALSE, pdFALSE, portMAX_DELAY);

  auto renderables = setupRenderables(app);
  auto renderer = Renderer(app->display, std::move(renderables), CLOCK_PAGE, &andala4pt7b);

  renderer.init();

  while (true) {
    app->display->setBrightness8(app->state.brightness());
    renderer.render(app->state.page().c_str());
    vTaskDelay(pdMS_TO_TICKS(16));
  }
}
