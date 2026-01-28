#include <cstdint>
#include "gpio.hpp"
#include "stm32f4xx.h"

using LD_Green = Gpio<Stm32GpioB, 0>;

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
