#include <Arduino.h>
#include "globals.h"
#include "clock.h"

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

    display = std::make_unique<MatrixPanel_I2S_DMA>(mxconfig);
    display->begin();
}

void displayLoop(void *parameter)
{

    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    initDisplay();
    while (true)
    {
        String brightnessState = state.brightness.state();
        uint8_t brightness = brightnessState.length() > 0 ? constrain(brightnessState.toInt(), 0L, 255L) : 100;
        display->setBrightness8(brightness);
        switch (state.page)
        {
        case CLOCK:
            renderClock();
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
