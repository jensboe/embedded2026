/**
 * @file bsp.h
 * @brief Peripheral definition on Nucleo-F446ZE board
 *
 */
#pragma once

#include "gpio.hpp"
#include "utils.hpp"
/**
 * @brief Contains board support package
 *
 */
namespace bsp
{
	using namespace stm32::f4;
	using LD_Green = GpioPin<GpioB, 0, GpioPinMode::Output>; //!< Green LED at PB0
	using LD_Blue = GpioPin<GpioB, 7, GpioPinMode::Output>;	 //!< Blue LED at PB7
	using LD_Red = GpioPin<GpioB, 14, GpioPinMode::Output>;	 //!< Red LED at PB14
	using B1 = GpioPin<GpioC, 13, GpioPinMode::Input>;		 //!< Blue button (down left) at PC13

	/**
	 * @brief Init every peropheral.
	 *
	 */
	void init()
	{
		LD_Green::init();
		LD_Blue::init();
		LD_Red::init();
		B1::init();
	}
} // namespace bsp
