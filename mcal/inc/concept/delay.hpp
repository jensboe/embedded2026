
#pragma once
#include <concepts>
#include <cstdint>
namespace mcal
{
	template <typename T>
	concept Delay = requires(T t, uint32_t duration) {
		{ T::ms(duration) } -> std::same_as<void>;
		{ T::µs(duration) } -> std::same_as<void>;
	};
} // namespace mcal
