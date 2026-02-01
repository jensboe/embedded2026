#include "gpio.hpp"
#include "utils.hpp"
namespace bsp
{
	using namespace stm32::f4;
	using LD_Green = GpioPin<GpioB, 0, GpioPinMode::Output>; //!< Green LED at PB0
	using LD_Blue = GpioPin<GpioB, 7, GpioPinMode::Output>;	 //!< Blue LED at PB7
	using LD_Red = GpioPin<GpioB, 14, GpioPinMode::Output>;	 //!< Red LED at PB14

	void init()
	{
		LD_Green::init();
		LD_Blue::init();
		LD_Red::init();
	}
} // namespace bsp
