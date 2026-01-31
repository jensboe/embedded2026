# Embedded2026

The project provides a modular architecture for microcontroller  development.
Currently focused on STM32F4 and tested with a STM32F446 controller.
But there will be support for more controller in the future.

**Note:** This project is under active development. Documentation is updated continuously.


## 🏗️ Project Structure

```
embedded2026/
├── mcal/                      # Microcontroller Abstraction Layer
│   ├── CMakeLists.txt
│   └── stm32/                 # STM32-specific implementations
│       └── ...
├── projects/                  # Application projects
│   ├── nucleof446ze/
│   │   └── blinky/           # Example project (LED blink)
│   └── ...
├── external/                  # External dependencies
│   ├── CMSIS_5/              # ARM CMSIS-5 core libraries
│   └── cmsis-device-f4/      # STM32F4 device files
├── tools/                     # Build tools
│   └── arm-gcc-toolchain.cmake
├── CMakeLists.txt            # Root CMake configuration
└── CMakePresets.json         # CMake preset configuration
```

## 🔧 Requirements

- **CMake** >= 4.0
- **ARM GCC Toolchain**: `arm-none-eabi-gcc`
- **Ninja** or **Make** (build system)
