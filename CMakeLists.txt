cmake_minimum_required(VERSION 3.5)

include(lib.cmake)

project(regex_compiler)

# Compile as executable
add_executable(main src/main.cpp)
set(CMAKE_CXX_STANDARD 20)
if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    cxx_flag(DDEBUG, DCPUF_C_STRING_DEBUG)
endif()
target_include_directories(main PRIVATE "src/cpuf")
set_target_properties(
    main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Generate assembly code
add_custom_command(
    TARGET main
    POST_BUILD
    COMMAND g++ ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp -S -O3 -I${CMAKE_CURRENT_SOURCE_DIR}/src/cpuf -o ${CMAKE_BINARY_DIR}/bin/main.s
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
