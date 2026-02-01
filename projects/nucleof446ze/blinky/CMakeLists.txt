add_executable(blinky)

target_sources(blinky
    PRIVATE
    src/main.cpp
    src/syscalls.c
    src/sysmem.c
)
target_compile_definitions(blinky PUBLIC
    STM32F446xx
)

target_link_libraries(blinky PRIVATE
    nucleo-f446ze
)
