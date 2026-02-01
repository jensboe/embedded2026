#include "gpio.hpp"
#include "utils.hpp"
#include <cstdio>
using namespace mcal::stm32::f4;

using LD_Green = GpioPin<GpioB, 0, GpioPinMode::Output>;
using LD_Blue = GpioPin<GpioB, 7, GpioPinMode::Output>;
using LD_Red = GpioPin<GpioB, 14, GpioPinMode::Output>;
using Delay = DelayImpl<16'000'000>;

int main(void)
{
	init_print();
	uint32_t loop_counter = 0;
	LD_Green::init();
	LD_Blue::init();
	LD_Red::init();

	while (1)
	{
		printf("Delay count: %lu\n", ++loop_counter);
		LD_Green::set();
		LD_Blue::set();
		LD_Red::set();
		Delay::ms(500);
		LD_Green::clear();
		LD_Blue::clear();
		LD_Red::clear();
		Delay::ms(500);
	}

	return 0;
}
