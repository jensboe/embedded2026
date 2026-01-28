add_executable(blinky)

target_sources(blinky
    PRIVATE
    src/main.cpp
    src/syscalls.c
    src/sysmem.c
)

target_link_libraries(blinky PRIVATE stm32f446ze)

# Add build information output
add_build_info_target(blinky)
