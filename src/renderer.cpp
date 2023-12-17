#include "renderer.h"
#include <iostream>
#include <filesystem>

Renderer::Renderer(const int renderWidth, const int renderHeight)
{
    std::cout << "Initializing renderer\n";
    if (!glfwInit())
    {
        std::cout << "Failed to init glfw\n";
    }

    glfwSetErrorCallback(Renderer::GLFWErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    render_window = glfwCreateWindow(renderWidth, renderHeight, "Minimum GL", NULL, NULL);
    if (!render_window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(render_window, Renderer::GLFWKeyCallback);

    glfwMakeContextCurrent(render_window);
    if (!gladLoadGL())
    {
        std::cout << "Error occured during opengl extension (glad) loading\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glClearColor(backColor.r, backColor.g, backColor.b, 1.0f);
}

Renderer::~Renderer()
{
    glfwTerminate();
}

void Renderer::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwSwapBuffers(render_window);
}

void Renderer::GLFWErrorCallback(int error, const char *description)
{
    std::cout << "GFLW error: " << description;
}

void Renderer::GLFWKeyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void Renderer::LoadShaders(const std::string& resourcePath)
{
    //std::filesystem::directory_iterator(".");

    // for (const auto& entry : std::filesystem::directory_iterator(resourcePath))
    // {
    //     std::cout << entry.path() << std::endl;
    // }
}
