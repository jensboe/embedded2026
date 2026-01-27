# ARM GCC Toolchain File
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Compiler location
find_program(ARM_GCC arm-none-eabi-gcc REQUIRED)
find_program(ARM_CXX arm-none-eabi-g++ REQUIRED)
find_program(ARM_AR arm-none-eabi-ar REQUIRED)
find_program(ARM_OBJCOPY arm-none-eabi-objcopy REQUIRED)
find_program(ARM_OBJDUMP arm-none-eabi-objdump REQUIRED)
find_program(ARM_SIZE arm-none-eabi-size REQUIRED)

# Set compilers
set(CMAKE_C_COMPILER ${ARM_GCC})
set(CMAKE_CXX_COMPILER ${ARM_CXX})
set(CMAKE_AR ${ARM_AR})
set(CMAKE_OBJCOPY ${ARM_OBJCOPY})
set(CMAKE_OBJDUMP ${ARM_OBJDUMP})
set(CMAKE_SIZE ${ARM_SIZE})

# Don't run the linker during compiler tests
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Compiler flags
set(ARM_COMMON_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${ARM_COMMON_FLAGS}" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ARM_COMMON_FLAGS}" CACHE STRING "" FORCE)

# Optimization flags
set(CMAKE_C_FLAGS_DEBUG "-g -O0" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_RELEASE "-O2" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-O2" CACHE STRING "" FORCE)
