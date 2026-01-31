#pragma once
#include <concepts>
#include <cstdint>

enum class GpioPinMode
{
	Input,
	Output,
};

template <typename T>
concept GpioPort = requires(T t, uint8_t pin, GpioPinMode mode) {
	{ T::enable() } -> std::same_as<void>;
	{ T::disable() } -> std::same_as<void>;
	{ T::template setMode<5, GpioPinMode::Output>() } -> std::same_as<void>;
	{ T::template writeHigh<5>() } -> std::same_as<void>;
	{ T::template writeLow<5>() } -> std::same_as<void>;
	{ T::template read<5>() } -> std::same_as<bool>;
};
