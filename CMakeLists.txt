cmake_minimum_required(VERSION 3.5.0)
project(life_gl VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB_RECURSE INTERNAL_SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${INTERNAL_SOURCES} external/glad/src/glad.c)

add_subdirectory(external/GLFW)
add_subdirectory(external/glm)

target_include_directories(${PROJECT_NAME}
    PUBLIC include
    PUBLIC external/GLFW/include
    PUBLIC external/glad/include
    PUBLIC external/glm
)

target_link_libraries(${PROJECT_NAME} glfw)
