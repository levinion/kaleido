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

# enable all wranning
target_compile_options(${name} PRIVATE
    # -Wall
    # -Wextra
    # -Wpedantic
    # -fsanitize=address
#     -g
)

# # include header
target_include_directories(${name} PUBLIC include/)

find_package(PkgConfig REQUIRED)

pkg_check_modules(spdlog REQUIRED spdlog)
target_link_libraries(${name} PRIVATE ${spdlog_LIBRARIES})

pkg_check_modules(cli11 REQUIRED CLI11)
target_link_libraries(${name} PRIVATE ${cli11_LIBRARIES})

include_directories(/usr/include/freetype2)

add_subdirectory(./vendor/hierro)
add_subdirectory(./vendor/xwrap)
add_subdirectory(./vendor/tomlplusplus)
target_link_libraries(${name} PUBLIC hierro xwrap tomlplusplus)

