#include <cstdint>
#include "gpio.hpp"

using LD_Green = GpioPin<GpioB, 0>;
using LD_Blue  = GpioPin<GpioB, 7>;
using LD_Red   = GpioPin<GpioB, 14>; 

int main(void)
{
    LD_Green::init();
    LD_Blue::init();
    LD_Red::init();

    while (1)
    {
        LD_Green::set();
        LD_Blue::set();
        LD_Red::set();
        LD_Green::clear();
        LD_Blue::clear();
        LD_Red::clear();
    } 

    return 0;
}
