#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
    std::cout << "It's ALIVE" << std::endl;

    GLFWwindow* window;
    if (!glfwInit())
    {
        std::cout << "Failed to init glfw\n";
    }

    window = glfwCreateWindow(1200, 600, "Minimum GL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}