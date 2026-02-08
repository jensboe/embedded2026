add_library(cmsisdevicef4)

target_include_directories(cmsisdevicef4 PUBLIC
    ${CMAKE_SOURCE_DIR}/external/cmsis-device-f4/Include
)
target_sources(cmsisdevicef4 PRIVATE
    ${CMAKE_SOURCE_DIR}/external/cmsis-device-f4/Source/Templates/system_stm32f4xx.c
    src/startup.cpp
)

target_include_directories(cmsisdevicef4 PUBLIC
    inc
)

target_link_libraries(cmsisdevicef4 PUBLIC
    mcal
)

target_compile_options(cmsisdevicef4 PUBLIC
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
)

target_link_options(cmsisdevicef4 PUBLIC
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
)

target_link_libraries(cmsisdevicef4 PUBLIC
    CMSIS_5
)
