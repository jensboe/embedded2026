/**
 * @file bsp.h
 * @brief Board support package for Nucleo-F446ZE
 */

#pragma once

#include <mp-units/systems/si.h>

#include "f4.hpp"

namespace bsp
{
	/**
	 * @brief Nucleo-F446ZE peripheral definitions.
	 *
	 * @tparam target_system_clock_hz Requested system clock frequency
	 */
	template <mp_units::quantity<mp_units::si::hertz, uint32_t> target_system_clock_hz>
	struct nucleo_f446ze
	{
		using LD_Green = stm32::f4::GpioPin<stm32::f4::GpioB, 0, stm32::f4::GpioPinMode::Output>; //!< Green LED at PB0
		using LD_Blue = stm32::f4::GpioPin<stm32::f4::GpioB, 7, stm32::f4::GpioPinMode::Output>;  //!< Blue LED at PB7
		using LD_Red = stm32::f4::GpioPin<stm32::f4::GpioB, 14, stm32::f4::GpioPinMode::Output>;  //!< Red LED at PB14
		using B1 =
			stm32::f4::GpioPin<stm32::f4::GpioC, 13, stm32::f4::GpioPinMode::Input>; //!< Blue user button at PC13

		/**
		 * @brief Supply voltage in millivolts.
		 *
		 */
		static constexpr std::uint32_t supply_voltage_mV = 3300;

		/**
		 * @brief Clock tree configuration.
		 *
		 */
		using clock = stm32::f4::clock_tree<target_system_clock_hz,
											{8 * mp_units::si::unit_symbols::MHz, mcal::clock::sources::clock}>;

		using Delay = stm32::f4::DelayImpl<target_system_clock_hz>; //!< System clock based delay utility

		/**
		 * @brief Initialize the board peripherals.
		 *
		 */
		static inline void init() noexcept
		{
			// Configure Flash latency according to RM0390, Table 5
			if constexpr (supply_voltage_mV > 2700)
			{
				using namespace stm32::f4;

				if constexpr (target_system_clock_hz < 30 * mp_units::si::unit_symbols::MHz)
					FLASH->ACR |= FLASH_ACR_LATENCY_0WS;
				else if constexpr (target_system_clock_hz < 60 * mp_units::si::unit_symbols::MHz)
					FLASH->ACR |= FLASH_ACR_LATENCY_1WS;
				else if constexpr (target_system_clock_hz < 90 * mp_units::si::unit_symbols::MHz)
					FLASH->ACR |= FLASH_ACR_LATENCY_2WS;
				else if constexpr (target_system_clock_hz < 120 * mp_units::si::unit_symbols::MHz)
					FLASH->ACR |= FLASH_ACR_LATENCY_3WS;
				else if constexpr (target_system_clock_hz < 150 * mp_units::si::unit_symbols::MHz)
					FLASH->ACR |= FLASH_ACR_LATENCY_4WS;
				else if constexpr (target_system_clock_hz < 180 * mp_units::si::unit_symbols::MHz)
					FLASH->ACR |= FLASH_ACR_LATENCY_5WS;
			}

			// Initialize clock tree and peripherals
			clock::init();
			stm32::f4::init_print();
			LD_Green::init();
			LD_Blue::init();
			LD_Red::init();
			B1::init();
		}
	};
} // namespace bsp
