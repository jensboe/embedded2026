add_library(nucleo-f446ze)

target_sources(nucleo-f446ze
    PRIVATE
    ${CMAKE_SOURCE_DIR}/external/cmsis-device-f4/Source/Templates/system_stm32f4xx.c
    ${CMAKE_SOURCE_DIR}/external/cmsis-device-f4/Source/Templates/gcc/startup_stm32f446xx.s
)
target_include_directories(nucleo-f446ze PUBLIC
    inc
)

target_compile_definitions(nucleo-f446ze PUBLIC
    STM32F446xx
)
target_link_libraries(nucleo-f446ze PUBLIC
    cmsisdevicef4
)

target_link_options(nucleo-f446ze PUBLIC
    -T${CMAKE_SOURCE_DIR}/mcal/stm32/f4/STM32F446ZETX_FLASH.ld
    -Wl,-Map=${TARGET_NAME}.map
)
