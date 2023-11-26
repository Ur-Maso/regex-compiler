cmake_minimum_required(VERSION 3.5)
# function to add something to variable
function(add, varaible, value)
    set(${variable}, "${{variable}}${value}")
endfunction(add, varaible, value)
# function to add cxx flags
function(cxx_flag, flag)
    set(CMAKE_CXX_FLAGS, "${CMAKE_CXX_FLAGS} -${flag}")
endfunction(cxx_flag, flag)
#function to add compiler argument
function(cxx_arg, arg)
    set(CMAKE_CXX_FLAGS, "${CMAKE_CXX_FLAGS} ${arg}")
endfunction(cxx_arg, arg)

project(regex_compiler)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 20)
cxx_flag("O3")
add_executable(main main.cpp)
target_include_directories(main PRIVATE cpuf)