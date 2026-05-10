#include <Arduino.h>
#include "globals.h"
#include "constants.h"
#include "clock.h"
#include "media-display.h"

#include "page.h"
#include "renderer.h"
#include "andala.h"

#include <Adafruit_GFX.h>

void initDisplay()
{
    HUB75_I2S_CFG::i2s_pins _pins = {R1_PIN, G1_PIN, B1_PIN, R2_PIN, G2_PIN, B2_PIN, A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, LAT_PIN, OE_PIN, CLK_PIN};
    HUB75_I2S_CFG mxconfig(
        DISPLAY_WIDTH,
        DISPLAY_HEIGHT,
        1,
        _pins);

    mxconfig.driver = HUB75_I2S_CFG::FM6126A;
    mxconfig.clkphase = false;
    mxconfig.min_refresh_rate = 120;
    mxconfig.i2sspeed = HUB75_I2S_CFG::HZ_16M;

    display = std::make_unique<MatrixPanel_I2S_DMA>(mxconfig);
    display->begin();
    display->setFont(&andala4pt7b);

    theClock.setDisplay(display.get());
}

void displayLoop(void *parameter)
{
    initDisplay();

    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    auto hour = Text("00", Color{255, 255, 255});
    auto divider = Text(":", Color{0, 255, 0});
    auto minutes = Text("00", Color{255, 255, 255});

    auto clockPage = Page(display.get(), {TextRow({hour, divider, minutes})});

    auto artist = Text("David Bowie", Color{93, 93, 93});
    auto title = Text("Space Oddity", Color{255, 255, 255});
    auto mediaPage = Page(display.get(), {
                                             TextRow({artist}),
                                             TextRow({title}),
                                         });

    auto renderer = Renderer({clockPage, mediaPage});
    String activePage;

    while (true)
    {
        display->setBrightness8(state.brightness());

        const String requestedPage = state.page();

        if (requestedPage == String(CLOCK_PAGE))
        {
            renderer.showPage(0);
        }
        else if (requestedPage == String(MEDIA_PAGE))
        {
            renderer.showPage(1);
        }

        renderer.render();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
