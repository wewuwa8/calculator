project(calculator)

cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing() 

include_directories(./include)

add_subdirectory(thirdparty)
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)
