# function to add something to variable
function(add, varaible, value)
    set(${variable}, "${{variable}}${value}")
endfunction(add, varaible, value)
# function to add cxx flags
function(cxx_flag flag data)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -${flag}{data}")
endfunction()
# function to define a macro
function (define macro value)
    add_definitions(-D${macro}=${value})
endfunction()
function (define macro)
    add_definitions(-D${macro})
endfunction()