# project
set(name "kaleido")
cmake_minimum_required(VERSION 3.10)
project(${name} CXX)

# clang setting
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE STRING "C++ compiler" FORCE)
set(CMAKE_CXX_STANDARD 26)

# src
file(GLOB_RECURSE SRC src/*.cpp)
add_executable(${name} ${SRC})

# link std library staticly
target_link_options(${name} PRIVATE -static-libgcc -static-libstdc++)

# include header
target_include_directories(${name} PUBLIC include/)

# add third party dependencies here
# add_subdirectory(./vendor/hierro2d-cpp)
# target_link_libraries(${name} PUBLIC hierro)
add_subdirectory(./vendor/hierro)
add_subdirectory(./vendor/xwrap)
target_link_libraries(${name} PUBLIC hierro xwrap)
