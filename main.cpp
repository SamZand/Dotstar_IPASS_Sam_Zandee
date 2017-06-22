/*
#############################################################################
#
# Project Ledstrip dotstar
#
# Sam Zandee 2017
#
#############################################################################
*/
#include <hwlib.hpp>
#include "ledstrip.hpp"

int main(void)
{
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    LEDstrip ledstrip(/* clock */ hwlib::target::pins::d4, /* data */ hwlib::target::pins::d5);

    ledstrip.clear();
    ledstrip.setAllBrightness(31);
    ledstrip.snake(0, 0, 0, 255);

    // example:
    //    ledstrip.clear();
    //    ledstrip.setAllBrightness(31);
    //    ledstrip.rainbow();
    //    while(1) {
    //        ledstrip.MoveColorsUp();
    //        ledstrip.show();
    //        hwlib::wait_ms(500);
    //    }

    //    // example 2:
    //    ledstrip.clear();
    //    ledstrip.setBrightness(1, 31);        // first led on max brightness
    //    ledstrip.setBrightness(60, 31);       // last led on max brightness
    //    ledstrip.setColor(1, 255, 255, 255);  // first led on white
    //    ledstrip.setColor(60, 255, 255, 255); // last led on white
    //    ledstrip.show();
}