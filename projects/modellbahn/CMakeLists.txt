add_executable(modellbahn)

target_sources(modellbahn
    PRIVATE
    src/main.cpp
    src/syscalls.c
    src/sysmem.c
)

target_link_libraries(modellbahn PRIVATE
    modellbahn-adapter-a
)
target_link_options(modellbahn PRIVATE
    -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/modellbahn.map
)
