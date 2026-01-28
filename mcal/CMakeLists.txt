add_library(CMSIS_5 INTERFACE)
target_include_directories(CMSIS_5 INTERFACE
    ${CMAKE_SOURCE_DIR}/external/CMSIS_5/CMSIS/Core/Include
)

add_library(mcal INTERFACE)
target_include_directories(mcal INTERFACE
    inc
)



add_subdirectory(STM32)
