add_executable(blinky)

target_sources(blinky
    PRIVATE
    src/main.cpp
    src/syscalls.c
    src/sysmem.c
)

target_link_libraries(blinky PRIVATE
    nucleo-f446ze
    mp-units::mp-units
)
target_link_options(blinky PRIVATE
    -Wl,-Map=blinky.map
)
