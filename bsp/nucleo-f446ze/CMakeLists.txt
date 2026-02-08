add_library(nucleo-f446ze INTERFACE)


target_include_directories(nucleo-f446ze INTERFACE
    inc
)

target_compile_definitions(nucleo-f446ze INTERFACE
    STM32F446xx
    HSE_VALUE=8000000
)
target_link_libraries(nucleo-f446ze INTERFACE
    cmsisdevicef4
)

target_compile_definitions(cmsisdevicef4 PRIVATE
    STM32F446xx
    HSE_VALUE=8000000
)

target_link_options(nucleo-f446ze INTERFACE
    -T${CMAKE_SOURCE_DIR}/mcal/stm32/f4/STM32F446ZETX_FLASH.ld
)
