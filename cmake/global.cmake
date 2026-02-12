add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -fdata-sections
    -ffunction-sections
    -Werror
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>
    $<$<COMPILE_LANGUAGE:CXX>:-fconcepts-diagnostics-depth=5>
    -fstack-usage
    -flto=auto
)

add_link_options(
    -Wl,--gc-sections
    -Wl,--start-group -lc -lm -Wl,--end-group
    -Wl,--print-memory-usage
    -Wl,--start-group -lstdc++ -lsupc++ -Wl,--end-group
    -flto=auto
)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g3")
endif()
if(CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -g0")
endif()
