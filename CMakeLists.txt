cmake_minimum_required(VERSION 3.30)
project(BlockKuzushi C)

set(CMAKE_C_STANDARD 11)

include_directories("C:/raylib/w64devkit/x86_64-w64-mingw32/include")
link_directories("C:/raylib/w64devkit/x86_64-w64-mingw32/lib")

add_executable(BlockKuzushi main.c)

target_link_libraries(BlockKuzushi raylib opengl32 gdi32 winmm)