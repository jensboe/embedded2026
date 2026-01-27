add_library(CMSIS_5 INTERFACE)
target_include_directories(CMSIS_5 INTERFACE
    ${CMAKE_SOURCE_DIR}/external/CMSIS_5/CMSIS/Core/Include
)

add_library(cmsisdevicef4 INTERFACE)
target_include_directories(cmsisdevicef4 INTERFACE
    ${CMAKE_SOURCE_DIR}/external/cmsis-device-f4/Include
)
target_sources(cmsisdevicef4 INTERFACE
    ${CMAKE_SOURCE_DIR}/external/cmsis-device-f4/Source/Templates/system_stm32f4xx.c
    ${CMAKE_SOURCE_DIR}/external/cmsis-device-f4/Source/Templates/gcc/startup_stm32f446xx.s
)

target_link_libraries(cmsisdevicef4 INTERFACE
    CMSIS_5
)

add_library(stm32f446ze STATIC)

target_compile_definitions(stm32f446ze PUBLIC
    STM32F446xx
)

target_link_libraries(stm32f446ze PUBLIC
    cmsisdevicef4
)
