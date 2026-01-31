#include "delay.hpp"
#include "gpio.hpp"

using namespace mcal::stm32::f4;

using LD_Green = GpioPin<GpioB, 0, GpioPinMode::Output>;
using LD_Blue = GpioPin<GpioB, 7, GpioPinMode::Output>;
using LD_Red = GpioPin<GpioB, 14, GpioPinMode::Output>;
using Delay = DelayImpl<16'000'000>;

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
		Delay::ms(500);
		LD_Green::clear();
		LD_Blue::clear();
		LD_Red::clear();
		Delay::ms(500);
	}

	return 0;
}
