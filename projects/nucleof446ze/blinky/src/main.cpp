#include <cstdint>
#include "gpio.hpp"

using LD_Green = GpioPin<GpioB, 0>;

int main(void)
{
    LD_Green::init();

    while (1)
    {
        LD_Green::set();
        LD_Green::clear();
    }

    return 0;
}
