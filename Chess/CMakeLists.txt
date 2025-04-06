cmake_minimum_required (VERSION 3.15)

project (Chess)

# Standard version logic
if (MSVC AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.21)
    set(CMAKE_CXX_STANDARD 23)
else ()
    set(CMAKE_CXX_STANDARD 20)
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags for MSVC
if (MSVC)
    add_compile_options (/W4 /permissive- /Zc:externConstexpr /Zc:inline)
endif ()

# Include headers
include_directories(include)

# Gather all source files from src/
file(GLOB SOURCES src/*.cpp)

# Create the executable with all sources
add_executable(Chess ${SOURCES})
