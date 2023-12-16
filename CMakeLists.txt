cmake_minimum_required(VERSION 3.5.0)
project(life_gl VERSION 0.1.0 LANGUAGES C CXX)

add_executable(${PROJECT_NAME} src/main.cpp external/glad/src/glad.c)

add_subdirectory(external/GLFW)

target_include_directories(${PROJECT_NAME} 
    PUBLIC external/GLFW/include
    PUBLIC external/glad/include
)

target_link_libraries(${PROJECT_NAME} glfw)
