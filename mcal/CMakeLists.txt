add_library(CMSIS_5 INTERFACE)
target_include_directories(CMSIS_5 INTERFACE
    ${CMAKE_SOURCE_DIR}/external/CMSIS_5/CMSIS/Core/Include
)

add_library(mcal INTERFACE)
target_include_directories(mcal INTERFACE
    inc
)
target_link_libraries(
    mcal INTERFACE
    mp-units::mp-units
)

target_link_options(mcal INTERFACE
    --specs=nano.specs
)

add_subdirectory(STM32)
