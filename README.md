# Embedded2026

An **ARM Cortex-M embedded project** with STM32F446ZE microcontroller and CMake-based build system.

## 📋 Overview

The project provides a modular architecture for STM32F4 development featuring:
- **MCAL** (Microcontroller Abstraction Layer) for hardware abstraction
- **Project structure** for specific applications
- **CMake** for cross-platform build management
- **ARM GCC Toolchain** for ARM Cortex-M compilation
- **CMSIS-5** and CMSIS-Device-F4 integration

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

Installation of ARM GCC Toolchain:
```bash
# Windows (with winget)
winget install ARM.GnuArmEmbeddedToolchain

# Linux (Debian/Ubuntu)
sudo apt-get install gcc-arm-none-eabi binutils-arm-none-eabi gdb-arm-none-eabi

# macOS (with Homebrew)
brew install arm-none-eabi-gcc
```

## 🏗️ Build Process

### 1. Configure (CMake)
```bash
cmake --preset default
```
or using CMake GUI / VS Code CMake Extension.

### 2. Build
```bash
cmake --build --preset default
```
or:
```bash
cd build && ninja
```

### 3. Output
Compiled binaries are generated in the `build/` directory.

## 📁 Important Directories

| Directory | Description |
|---|---|
| `mcal/` | Hardware abstraction layer (drivers, low-level code) |
| `projects/` | Application projects for specific boards |
| `external/` | Third-party libraries (CMSIS, device support packages) |
| `tools/` | CMake toolchain and build scripts |
| `build/` | Build output (generated) |

## 🎯 Available Projects

### nucleof446ze/blinky
A simple LED blink demo project for the **STM32 Nucleo-F446ZE board**.

**Build:**
```bash
cmake --build --preset default --target blinky
```

## 🔨 Compiler Settings

The ARM GCC Toolchain is configured in [tools/arm-gcc-toolchain.cmake](tools/arm-gcc-toolchain.cmake):

- **Processor**: `cortex-m4`
- **Floating-Point**: `fpv4-sp-d16` (hardware)
- **Compiler Flags**: `-mcpu=cortex-m4 -mthumb -Wall` (among others)

## 🔗 Dependencies

- **CMSIS-5**: ARM Cortex Microcontroller Software Interface Standard
- **CMSIS-Device-F4**: STM32F4 device support package
- **External Git Modules**: See `.gitmodules`

## 📝 License

See individual files and external dependencies for license information.

---

**Note:** This project is under active development. Documentation is updated continuously.
