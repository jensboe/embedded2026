#include <concepts>
#include <cstdint>

enum class GpioPinMode
{
    Input,
    Output,
};

template <typename T>
concept GpioPort = requires(T t, uint8_t pin) {
    { T::enableClock() } -> std::same_as<void>;
    { T::setModeOutput(pin) } -> std::same_as<void>;
    { T::writeHigh(pin) } -> std::same_as<void>;
    { T::writeLow(pin) } -> std::same_as<void>;
};