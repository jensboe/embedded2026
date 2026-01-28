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
    { T::template setMode<GpioPinMode::Output>(pin) } -> std::same_as<void>;
    { T::writeHigh(pin) } -> std::same_as<void>;
    { T::writeLow(pin) } -> std::same_as<void>;
};