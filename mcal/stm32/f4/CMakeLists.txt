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
add_subdirectory(STM32F446ZE)
