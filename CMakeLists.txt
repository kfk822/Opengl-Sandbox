cmake_minimum_required(VERSION 3.10)

project(OPENGL_SANDBOX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(OPENGL_SANDBOX
        src/main.cpp
        external/includes/glad/glad.c
)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

target_include_directories(OPENGL_SANDBOX PRIVATE external/includes)
target_link_directories(OPENGL_SANDBOX PRIVATE external/libraries)
target_link_libraries(OPENGL_SANDBOX PRIVATE
    glfw3
    opengl32
    gdi32
)