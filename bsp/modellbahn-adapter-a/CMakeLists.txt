add_library(modellbahn-adapter-a INTERFACE)


target_include_directories(modellbahn-adapter-a INTERFACE
    inc
)

target_link_libraries(modellbahn-adapter-a INTERFACE
    nucleo-f446ze
)
