/*
#############################################################################
#
# Project Ledstrip dotstar
#
# Sam Zandee 2017
#
#############################################################################
*/

#include "ledstrip.hpp"

LEDstrip::LEDstrip(hwlib::target::pins clockpin, hwlib::target::pins datapin)
    : clock(clockpin)
    , data(datapin)
{
}

/// Sends 1 bit to the strip.
void LEDstrip::sendBit(bool value)
{
    clock.set(0);
    data.set(value);
    clock.set(1);
}

/// Sends 1 byte to the strip
void LEDstrip::sendByte(const uint8_t& value)
{
    for(auto i = 0; i < 8; ++i) {
        sendBit((value << i) & 0x80);
    }
}

/// The strip needs 4 0X00 bytes as a start frame
void LEDstrip::sendstart()
{
    for(int i = 0; i < 4; i++) {
        sendByte(0x00);
    }
}

/// The strip needs 4 0XFF bytes as a end frame
void LEDstrip::sendend()
{
    for(int i = 0; i < 4; i++) {
        sendByte(0xFF);
    }
}

/// This function sets a given color to a given position on the ledstrip
void LEDstrip::setColor(uint32_t posled, uint8_t r, uint8_t g, uint8_t b)
{
    auto posOffset = (posled - 1) * 4;
    LEDarray[posOffset + 3] = r;
    LEDarray[posOffset + 2] = g;
    LEDarray[posOffset + 1] = b;
}

/// This function sets a given brightness to a given position on the ledstrip
void LEDstrip::setBrightness(uint32_t posled, uint8_t brightness)
{
    auto posOffset = (posled - 1) * 4;
    LEDarray[posOffset] = brightness | 0xE0;
}

/// This functions sends the array with all the info to the strip
void LEDstrip::show()
{
    sendstart();
    for(int j = 0; j < numleds; j++) {
        auto posOffset = j * 4;
        sendByte(LEDarray[posOffset]);
        sendByte(LEDarray[posOffset + 1]);
        sendByte(LEDarray[posOffset + 2]);
        sendByte(LEDarray[posOffset + 3]);
    }
    sendend();
}

/// This function sets al the leds to 0
void LEDstrip::clear()
{
    for(int i = 0; i < numleds; i++) {
        setColor((i + 1), 0x00, 0x00, 0x00);
        setBrightness((i + 1), 0x00);
    }
}

/// This function sets all the led to a given brightness
void LEDstrip::setAllBrightness(uint8_t brightness)
{
    for(int i = 0; i < numleds; i++) {
        setBrightness((i + 1), brightness);
    }
}

/// This function sets all the led to a given color
void LEDstrip::setAllColor(uint8_t r, uint8_t g, uint8_t b)
{
    for(int i = 0; i < numleds; i++) {
        setColor((i + 1), r, g, b);
    }
}

/// Moves all leds a position up
void LEDstrip::MoveColorsUp()
{
    auto firstLEDcolor = getColor(1);
    for(unsigned int x = 1; x < numleds; x++) {
        auto color = getColor(x + 1);
        setColor(x, color.red, color.green, color.blue);
    }
    setColor(numleds, firstLEDcolor.red, firstLEDcolor.green, firstLEDcolor.blue);
}

/// gets the color out the array
Color LEDstrip::getColor(uint32_t posled)
{
    Color color;
    auto posOffset = (posled - 1) * 4;
    color.red = LEDarray[posOffset + 3];
    color.green = LEDarray[posOffset + 2];
    color.blue = LEDarray[posOffset + 1];
    return color;
}

/// Makes a rainbow
void LEDstrip::rainbow()
{

    for(unsigned int x = 1; x < numleds - 1; x += 3) {
        setColor(x, 255, 0, 0);
        setColor(x + 1, 0, 255, 0);
        setColor(x + 2, 0, 0, 255);
        setBrightness(x + 0, 31);
        setBrightness(x + 1, 16);
        setBrightness(x + 2, 2);
    }
}
/// Makes a disco
void LEDstrip::disco()
{

    for(unsigned int x = 1; x < numleds - 1; x += 6) {
        setColor(x, 255, 0, 0);
        setColor(x + 1, 0, 255, 0);
        setColor(x + 2, 0, 0, 255);
        setColor(x + 3, 255, 255, 0);
        setColor(x + 4, 0, 255, 255);
        setColor(x + 5, 255, 0, 255);
        setBrightness(x + 0, 31);
        setBrightness(x + 1, 16);
        setBrightness(x + 2, 2);
    }
}

/// A snake through the ledstrip
void LEDstrip::snake(int speed, uint8_t r, uint8_t g, uint8_t b)
{

    setColor(1, b, r, g);
    setColor(2, g, b, r);
    setColor(3, r, g, b);
    setColor(4, r, g, b);
    setColor(5, r, g, b);
    setColor(6, r, g, b);
    setColor(7, r, g, b);
    setColor(8, r, g, b);
    setColor(9, r, g, b);
    setColor(10, r, g, b);
    while(1) {
        MoveColorsUp();
        show();
        hwlib::wait_ms(speed);
    }
}
