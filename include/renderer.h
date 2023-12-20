#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <memory>

class MeshObject;


enum class ShaderType
{
    Vertex,
    Fragment
};

class Shader
{
public:
    Shader() = default;
    Shader(const std::string& shaderPath, const std::string& shaderFile, const ShaderType shaderType);
    ~Shader();
    bool IsValid() const { return shader_id != GL_FALSE; }
    int GetShaderId() const { return shader_id; }

private:
    bool LoadShaderSource(const std::string& shaderPath, std::string& shaderSource);

public:
    const std::string& name;

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
    int GetProgramId() const { return shader_program_id; }
    void Bind();
    void Unbind();
    void SetUniform(const std::string& uniformName, const glm::vec3& vector);
    void SetUniform(const std::string& uniformName, const glm::mat4& matrix);

public:
    const std::string& name;

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
    std::shared_ptr<ShaderProgram> GetShaderProgram(const std::string& shaderProgramName);
    void AddObject(std::shared_ptr<MeshObject> object);

private:
    void LinkPrograms();

    static void GLFWErrorCallback(int error, const char* description);
    static void GLFWKeyCallback(GLFWwindow* window,  int key, int scanCode, int action, int mods);

public:
    GLFWwindow* render_window;

private:
    glm::vec3 backColor = glm::vec3(0.25f, 0.25f, 1.0f);
    std::vector<std::shared_ptr<MeshObject>> objects;
    std::unordered_map<std::string, std::shared_ptr<Shader>> vertex_shaders;
    std::unordered_map<std::string, std::shared_ptr<Shader>> fragment_shaders;
    std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> shader_programs;
};