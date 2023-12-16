#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


static void GLFWErrorCallback(int error, const char* description)
{
    std::cout << "GLFW error: " << description;
}

static void GLFWKeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    std::cout << "It's ALIVE" << std::endl;

    GLFWwindow* window;
    if (!glfwInit())
    {
        std::cout << "Failed to init glfw\n";
    }

    glfwSetErrorCallback(GLFWErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    window = glfwCreateWindow(1200, 600, "Minimum GL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, GLFWKeyCallback);

    glfwMakeContextCurrent(window);
    if (!gladLoadGL())
    {
        std::cout << "Error occured during opengl extension (glad) loading\n";
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