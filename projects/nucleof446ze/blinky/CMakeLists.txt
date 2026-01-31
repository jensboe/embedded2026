add_executable(blinky)

target_sources(blinky
    PRIVATE
    src/main.cpp
    src/syscalls.c
    src/sysmem.c
    ${CMAKE_SOURCE_DIR}/external/cmsis-device-f4/Source/Templates/system_stm32f4xx.c
    ${CMAKE_SOURCE_DIR}/external/cmsis-device-f4/Source/Templates/gcc/startup_stm32f446xx.s
)
target_compile_definitions(blinky PUBLIC
    STM32F446xx
)

target_link_libraries(blinky PRIVATE cmsisdevicef4)
target_link_options(blinky PUBLIC
    -T${CMAKE_SOURCE_DIR}/mcal/stm32/f4/STM32F446ZETX_FLASH.ld
    -Wl,-Map=${TARGET_NAME}.map
)
