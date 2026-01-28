add_library(stm32f446ze STATIC)

target_include_directories(stm32f446ze PUBLIC
    inc
)

target_compile_definitions(stm32f446ze PUBLIC
    STM32F446xx
)
target_compile_options(stm32f446ze PUBLIC
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
)

target_link_options(stm32f446ze PUBLIC
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
)

target_link_libraries(stm32f446ze PUBLIC
    cmsisdevicef4
    mcal
)

target_link_options(stm32f446ze PUBLIC
    -T${CMAKE_CURRENT_SOURCE_DIR}/STM32F446ZETX_FLASH.ld
    --specs=nano.specs
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections
    -Wl,--start-group -lc -lm -Wl,--end-group
    -Wl,--print-memory-usage
    -Wl,--start-group -lstdc++ -lsupc++ -Wl,--end-group
)
