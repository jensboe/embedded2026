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
		static constexpr auto supply_voltage_mV = 3300;
		/**
		 * @brief Clock tree with an external 8'000'000 MHz clock
		 *
		 * Clocktree will be configired do match requested target_system_clock_hz

		 *
		 */
		using clock = clock_tree<target_system_clock_hz, {8'000'000, mcal::clock::sources::clock}>;

		using Delay = DelayImpl<target_system_clock_hz>; //!< Configure delay utility with System clock

		/**
		 * @brief Init every peropheral.
		 *
		 */
		static inline void init()
		{
			// Flash latency must be configured like table 5 in RM0390

			if constexpr (supply_voltage_mV > 2700)
			{
				if constexpr (target_system_clock_hz < 30'000'000)
				{
					FLASH->ACR |= FLASH_ACR_LATENCY_0WS;
				}
				else if constexpr (target_system_clock_hz < 60'000'000)
				{
					FLASH->ACR |= FLASH_ACR_LATENCY_1WS;
				}
				else if constexpr (target_system_clock_hz < 90'000'000)
				{
					FLASH->ACR |= FLASH_ACR_LATENCY_2WS;
				}
				else if constexpr (target_system_clock_hz < 120'000'000)
				{
					FLASH->ACR |= FLASH_ACR_LATENCY_3WS;
				}
				else if constexpr (target_system_clock_hz < 150'000'000)
				{
					FLASH->ACR |= FLASH_ACR_LATENCY_4WS;
				}
				else if constexpr (target_system_clock_hz < 180'000'000)
				{
					FLASH->ACR |= FLASH_ACR_LATENCY_5WS;
				}
			}
			clock::init();
			init_print();
			LD_Green::init();
			LD_Blue::init();
			LD_Red::init();
			B1::init();
		}
	};
} // namespace bsp
