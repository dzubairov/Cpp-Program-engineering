cmake_minimum_required(VERSION 3.27)

# ==========================================================================

project(library_v1 VERSION 24.02.06 LANGUAGES CXX)

# ==========================================================================

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED True)

# ==========================================================================

find_package(Boost 1.84 REQUIRED COMPONENTS)

# ==========================================================================

include_directories(${Boost_INCLUDE_DIRS})

# ==========================================================================

add_library            (library_v1 STATIC source/library.cpp)

target_compile_options (library_v1 PRIVATE -Wall -Wextra -pedantic -O0)