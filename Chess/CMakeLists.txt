cmake_minimum_required (VERSION 3.15)

project (Chess)

# New CMake versions map C++20 to /std:c++20 instead of c++latest, so <format>
# and other unstable ABI features aren't supported. Use C++23 for such versions
if (MSVC AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.21)
    set(CMAKE_CXX_STANDARD 23)
else ()
    set(CMAKE_CXX_STANDARD 20)
endif ()

set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options (/W4 /permissive- /Zc:externConstexpr /Zc:inline)
endif ()

add_executable (Chess ""
        include/Piece.h
        include/Board.h
        include/Rook.h
        include/King.h
        include/Queen.h
        include/Bishop.h
        include/GameValidator.h
        include/Knight.h
        include/Pawn.h
        include/PriorityQueue.h
        include/Exceptions.h
        include/MoveValidator.h
        include/Helper.h
        include/ThreadPool.h
        src/Board.cpp
        src/Rook.cpp
        src/King.cpp
        src/Queen.cpp
        src/Bishop.cpp
        src/GameValidator.cpp
        src/Knight.cpp
        src/Pawn.cpp
        src/PriorityQueue.cpp
        src/Exceptions.cpp
        src/MoveValidator.cpp
        src/Helper.cpp
        src/Threadpool.cpp
       )


add_subdirectory (include)
add_subdirectory (src)



