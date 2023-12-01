cmake_minimum_required(VERSION 3.5)

include(lib.cmake)

project(regex_compiler)

# Compile as executable
add_executable(main src/main.cpp)
set(CMAKE_CXX_STANDARD 20)
if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    define(DEBUG)
    define(CPUF_C_STRING_DEBUG)
endif()
target_include_directories(main PRIVATE "src/cpuf" "src/lib")
set_target_properties(
    main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Generate assembly code
add_custom_command(
    TARGET main
    POST_BUILD
    COMMAND g++ ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp -S -fverbose-asm -O3 -I${CMAKE_CURRENT_SOURCE_DIR}/src/cpuf -I${CMAKE_CURRENT_SOURCE_DIR}/src/lib -o ${CMAKE_BINARY_DIR}/bin/main.s
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
# run executable
add_custom_command(
    TARGET main
    POST_BUILD
    COMMAND ${CMAKE_BINARY_DIR}/bin/main.exe ${CMAKE_CURRENT_SOURCE_DIR}/test/test.txt
)
