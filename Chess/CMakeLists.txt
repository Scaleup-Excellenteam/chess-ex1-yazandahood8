cmake_minimum_required(VERSION 3.10)
project(ChessGame)

# Set C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for headers
include_directories(include)

# Collect all .cpp files in src/
file(GLOB SOURCES "src/*.cpp")

# Create the executable
add_executable(Chess ${SOURCES})

# Optional: show all warnings
target_compile_options(Chess PRIVATE -Wall -Wextra -pedantic)
