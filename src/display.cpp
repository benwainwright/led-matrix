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

void displayLoop(void* parameter)

{
  App* app = static_cast<App*>(parameter);

  initDisplay(app);

  ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

  auto clock = Clock(app->display);
  clock.init();
  auto media = MediaDisplay(app->display, DISPLAY_WIDTH);

  auto clockPage = Page(app->display, clock.getText());
  auto mediaPage = Page(app->display, media.getText(), 2);

  auto renderer = Renderer({clockPage, mediaPage});

  while (true) {
    clock.tick();
    media.tick(app->state.title(), app->state.artist());

    app->display->setBrightness8(app->state.brightness());

    const String requestedPage = app->state.page();

    if (requestedPage == String(CLOCK_PAGE)) {
      renderer.showPage(0);
    } else if (requestedPage == String(MEDIA_PAGE)) {
      renderer.showPage(1);
    }

    renderer.render();
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}
