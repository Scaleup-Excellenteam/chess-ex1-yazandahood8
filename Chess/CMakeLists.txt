cmake_minimum_required(VERSION 3.10)

project(ChessGame)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add all source files
file(GLOB SOURCES
    *.cpp
)

# Create the executable
add_executable(Chess ${SOURCES})

# Include headers from the current directory
target_include_directories(Chess PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
