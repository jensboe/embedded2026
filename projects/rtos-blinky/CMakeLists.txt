add_executable(rtos-blinky)

target_sources(rtos-blinky
    PRIVATE
    src/main.cpp
)

target_link_libraries(rtos-blinky PRIVATE
    nucleo-f446ze
    freertos_kernel
    freertos_config
)
target_link_options(rtos-blinky PRIVATE
    -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/rtos-blinky.map
)

add_library(freertos_config INTERFACE)

target_include_directories(freertos_config SYSTEM
    INTERFACE
    inc
)
target_link_libraries(freertos_config INTERFACE
    cmsisdevicef4
)

target_compile_definitions(freertos_config
    INTERFACE
    projCOVERAGE_TEST=0
)
