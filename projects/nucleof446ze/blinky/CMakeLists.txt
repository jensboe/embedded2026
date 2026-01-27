add_executable(blinky)
target_sources(blinky
    PRIVATE
    src/main.cpp
    src/syscalls.c
    src/sysmem.c
)
target_link_options(blinky PRIVATE
    -T${CMAKE_CURRENT_SOURCE_DIR}/src/STM32F446ZETX_FLASH.ld
)
target_link_libraries(blinky PRIVATE stm32f446ze)
