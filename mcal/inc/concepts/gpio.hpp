/**
 * @file gpio.hpp
 * @brief GPIO abstraction layer for mcal.
 *
 */
#pragma once
#include <concepts>
#include <cstdint>
namespace mcal::concepts
{
	/**
	 * @brief GPIO pin modes.
	 *
	 * @todo expand with more modes (alternate function, analog, pull-up, pull-down)
	 *
	 */
	enum class GpioPinMode
	{
		Input,	//!< Input mode
		Output, //!< Output mode
	};

	/**
	 * @brief GPIO port concept.
	 *
	 * This concept defines the required interface for a GPIO port
	 * implementation. A GPIO port must provide methods to enable/disable
	 * the port clock, set pin modes, and read/write pin states.
	 *
	 * @todo A toggle function is needed as well.
	 *
	 */
	template <typename T>
	concept GpioPort = requires(T t, uint8_t pin, GpioPinMode mode) {
		{ T::enable() } -> std::same_as<void>;
		{ T::disable() } -> std::same_as<void>;
		{ T::template setMode<5, GpioPinMode::Output>() } -> std::same_as<void>;
		{ T::template writeHigh<5>() } -> std::same_as<void>;
		{ T::template writeLow<5>() } -> std::same_as<void>;
		{ T::template read<5>() } -> std::same_as<bool>;
	};
} // namespace mcal::concepts
