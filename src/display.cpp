#include <Arduino.h>
#include "globals.h"
#include "constants.h"
#include "clock.h"
#include "media-display.h"

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

    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    initDisplay();

    MediaDisplay media = MediaDisplay(display.get());

    while (true)
    {
        display->setBrightness8(state.brightness());

        if (state.page() == String(CLOCK_PAGE))
        {
            display->setFont(&andala4pt7b);
            theClock.tick();
            media.force();
        }
        else if (state.page() == String(MEDIA_PAGE))
        {
            display->setFont(nullptr);
            media.setPlaying(state.playing());
            media.tick(state.artist(), state.title());
            theClock.forceRerender();
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
