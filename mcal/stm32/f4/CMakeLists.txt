add_library(cmsisdevicef4 INTERFACE)
target_include_directories(cmsisdevicef4 INTERFACE
    ${CMAKE_SOURCE_DIR}/external/cmsis-device-f4/Include
)

target_include_directories(cmsisdevicef4 INTERFACE
    inc
)

target_link_libraries(cmsisdevicef4 INTERFACE
    mcal
)

target_compile_options(cmsisdevicef4 INTERFACE
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
)

target_link_options(cmsisdevicef4 INTERFACE
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
)
target_link_libraries(cmsisdevicef4 INTERFACE
    CMSIS_5
)
