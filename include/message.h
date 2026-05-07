#ifndef MESSAGE_H
#define MESSAGE_H
#define X_CENTRED -1
#define Y_CENTRED -1

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

class Message
{

private:
    uint8_t size;
    int8_t x;
    int8_t y;

    MatrixPanel_I2S_DMA *display;

    void render(const char *message, int8_t x, int8_t y);
    uint16_t getWidthOffsetForCentre(const char *message);
    uint16_t getHeightOffsetForCentre(const char *message);

public:
    Message(
        MatrixPanel_I2S_DMA *display,
        uint8_t sizeInit,
        int8_t xInit,
        int8_t yInit);

    void write(const char *message);
    void write(String message);
};

#endif
