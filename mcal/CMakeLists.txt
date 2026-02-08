add_library(CMSIS_5 INTERFACE)
target_include_directories(CMSIS_5 INTERFACE
    ${CMAKE_SOURCE_DIR}/external/CMSIS_5/CMSIS/Core/Include
)

add_library(mcal)
target_include_directories(mcal PUBLIC
    inc
)
target_sources(mcal PUBLIC
    src/syscalls.c
    src/sysmem.c
)
target_link_libraries(
    mcal PUBLIC
    mp-units::mp-units
)

target_link_options(mcal PUBLIC
    --specs=nano.specs
)

add_subdirectory(stm32)
