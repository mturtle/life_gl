#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <memory>


enum class ShaderType
{
    Vertex,
    Fragment
};

class Shader
{
public:
    Shader() = default;
    Shader(const std::string& shaderPath, const ShaderType shaderType);
    ~Shader();
    bool IsValid() const { return shader_id != GL_FALSE; }
    int GetShaderId() const { return shader_id; }

private:
    bool LoadShaderSource(const std::string& shaderPath, std::string& shaderSource);

private:
    int shader_id;
    ShaderType shader_type;
};

class ShaderProgram
{
public:
    ShaderProgram() = default;
    ShaderProgram(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader);
    ~ShaderProgram();
    bool IsValid() const { return shader_program_id != GL_FALSE; }

private:
    int shader_program_id;
};

class Renderer
{
public:
    Renderer(const int renderWidth, const int renderHeight);
    ~Renderer();
    void Draw();
    void LoadShaders(const std::string& resourcePath);

private:
    void LinkPrograms();

    static void GLFWErrorCallback(int error, const char* description);
    static void GLFWKeyCallback(GLFWwindow* window,  int key, int scanCode, int action, int mods);

public:
    GLFWwindow* render_window;

private:
    glm::vec3 backColor = glm::vec3(0.25f, 0.25f, 1.0f);
    std::vector<int> objects;
    std::unordered_map<std::string, std::shared_ptr<Shader>> vertex_shaders;
    std::unordered_map<std::string, std::shared_ptr<Shader>> fragment_shaders;
    std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> shader_programs;
};