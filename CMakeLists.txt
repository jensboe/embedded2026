cmake_minimum_required(VERSION 4.0)

project(embedded2026 C CXX ASM)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =============================================================================
# Build Configuration Information
# =============================================================================
message(STATUS "")
message(STATUS "embedded2026 - Build Configuration")


# System & Compiler Info
message(STATUS "")
message(STATUS "System Information:")
message(STATUS "  • OS: ${CMAKE_SYSTEM_NAME}")
message(STATUS "  • Processor: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "  • CMake Version: ${CMAKE_VERSION}")

message(STATUS "")
message(STATUS "Compiler Configuration:")
message(STATUS "  • C Compiler: ${CMAKE_C_COMPILER_ID} (${CMAKE_C_COMPILER})")
message(STATUS "  • CXX Compiler: ${CMAKE_CXX_COMPILER_ID} (${CMAKE_CXX_COMPILER})")
message(STATUS "  • C Standard: C${CMAKE_C_STANDARD}")
message(STATUS "  • CXX Standard: C++${CMAKE_CXX_STANDARD}")

# Build Type & Optimization
message(STATUS "")
message(STATUS "Build Configuration:")
message(STATUS "  • Build Type: ${CMAKE_BUILD_TYPE}")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "  • Optimization: Debug (-g -O0)")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "  • Optimization: Release (-O2)")
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    message(STATUS "  • Optimization: Release with Debug Info (-g -O2)")
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    message(STATUS "  • Optimization: Minimal Size (-Os)")
else()
    message(STATUS "  • Optimization: Custom")
endif()

# Compiler Flags
message(STATUS "")
message(STATUS "Compiler Flags:")
message(STATUS "  • C Flags: ${CMAKE_C_FLAGS}")
message(STATUS "  • C Flags (Debug): ${CMAKE_C_FLAGS_DEBUG}")
message(STATUS "  • C Flags (Release): ${CMAKE_C_FLAGS_RELEASE}")
message(STATUS "  • CXX Flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "  • CXX Flags (Debug): ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "  • CXX Flags (Release): ${CMAKE_CXX_FLAGS_RELEASE}")


function(add_build_info_target TARGET_NAME)
    add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo ""
        COMMAND ${CMAKE_COMMAND} -E echo "Building: ${TARGET_NAME}"
        COMMAND ${CMAKE_COMMAND} -E echo ""
        COMMAND ${CMAKE_COMMAND} -E echo "Build Information:"
        COMMAND ${CMAKE_COMMAND} -E echo " * Target: ${TARGET_NAME}"
        COMMAND ${CMAKE_COMMAND} -E echo " * Type: $<TARGET_PROPERTY:${TARGET_NAME},TYPE>"
        COMMAND ${CMAKE_COMMAND} -E echo " * Compiler: ${CMAKE_CXX_COMPILER_ID}"
        COMMAND ${CMAKE_COMMAND} -E echo " * Build Type: ${CMAKE_BUILD_TYPE}"
        COMMAND ${CMAKE_COMMAND} -E echo " * Optimization: ${CMAKE_CXX_FLAGS}"
        COMMAND ${CMAKE_COMMAND} -E echo ""
        VERBATIM
    )

    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo ""
        COMMAND ${CMAKE_COMMAND} -E echo "Build Complete: ${TARGET_NAME}"
        COMMAND ${CMAKE_COMMAND} -E echo ""
        VERBATIM
    )
endfunction()

add_subdirectory(mcal)
add_subdirectory(projects)
