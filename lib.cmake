# function to add something to variable
function(add, varaible, value)
    set(${variable}, "${{variable}}${value}")
endfunction(add, varaible, value)
# function to add cxx flags
function(cxx_flag)
    foreach(flag IN LISTS ARGN)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -${flag}")
    endforeach()
endfunction()
# function to add compiler argument
function(cxx_arg, arg)
    set(CMAKE_CXX_FLAGS, "${CMAKE_CXX_FLAGS} ${arg}")
endfunction(cxx_arg, arg)