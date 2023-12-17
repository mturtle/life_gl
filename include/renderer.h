#pragma once

#include <vector>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

using namespace glm;

class Renderer
{
public:
    Renderer(const int renderWidth, const int renderHeight);
    ~Renderer();
    void Draw();
    void LoadShaders(const std::string& resourcePath);

private:
    static void GLFWErrorCallback(int error, const char* description);
    static void GLFWKeyCallback(GLFWwindow* window,  int key, int scanCode, int action, int mods);

public:
    GLFWwindow* render_window;

private:
    vec3 backColor = vec3(0.25f, 0.25f, 1.0f);
    std::vector<int> objects;
};