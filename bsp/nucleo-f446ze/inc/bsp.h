/**
 * @file bsp.h
 * @brief Peripheral definition on Nucleo-F446ZE board
 *
 */
#pragma once

#include "f4.hpp"
/**
 * @brief Contains board support package
 *
 */
namespace bsp
{
	using namespace stm32::f4;
	/**
	 * @brief Definition of nucleo-f446ze specific peripherals
	 *
	 * @tparam target_system_clock_hz Requested system clock speed
	 */
	template <uint32_t target_system_clock_hz>
	struct nucleo_f446ze
	{
		using LD_Green = GpioPin<GpioB, 0, GpioPinMode::Output>; //!< Green LED at PB0
		using LD_Blue = GpioPin<GpioB, 7, GpioPinMode::Output>;	 //!< Blue LED at PB7
		using LD_Red = GpioPin<GpioB, 14, GpioPinMode::Output>;	 //!< Red LED at PB14
		using B1 = GpioPin<GpioC, 13, GpioPinMode::Input>;		 //!< Blue button (down left) at PC13

		/**
		 * @brief Init every peropheral.
		 *
		 */
		static inline void init()
		{
			init_print();
			LD_Green::init();
			LD_Blue::init();
			LD_Red::init();
			B1::init();
		}
	};
} // namespace bsp
