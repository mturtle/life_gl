#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

class Renderer
{
public:
    Renderer(const int renderWidth, const int renderHeight);
    ~Renderer();
    void Draw();

private:
    static void GLFWErrorCallback(int error, const char* description);
    static void GLFWKeyCallback(GLFWwindow* window,  int key, int scanCode, int action, int mods);

public:
    GLFWwindow* render_window;

private:
    glm::vec3 backColor = glm::vec3(0.25f, 0.25f, 1.0f);
    std::vector<int> objects;
};