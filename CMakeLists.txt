cmake_minimum_required(VERSION 3.10)
project(demo)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH "C:/msys64/mingw64/lib/cmake")

find_package(glfw3 REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    C:/msys64/mingw64/include
)

add_executable(demo
    src/main.cpp
    src/glad.c
    src/shader.cpp 
    src/EBO.cpp
    src/VAO.cpp
    src/VBO.cpp    
    src/stb.cpp
)

target_link_libraries(demo
    glfw
    opengl32
)
