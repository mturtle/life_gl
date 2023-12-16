#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <iostream>

#include "renderer.h"

int main()
{
    std::cout << "It's ALIVE" << std::endl;

    Renderer renderer(1200, 600);

    while (!glfwWindowShouldClose(renderer.render_window))
    {
        glfwPollEvents();
        renderer.Draw();
    }

    glfwDestroyWindow(renderer.render_window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}