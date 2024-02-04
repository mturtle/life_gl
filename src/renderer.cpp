#include "renderer.h"

#include <iostream>
#include <dirent.h>
#include <fstream>

#include "mesh.h"

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

void Renderer::Render()
{
    BeginFrame();

    for (const std::shared_ptr<MeshObject> object : objects)
    {
        object->Render();
    }

    EndFrame();
}

void Renderer::BeginFrame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::EndFrame()
{
    glfwSwapBuffers(render_window);
}

void Renderer::LinkPrograms()
{
    // for each vertex shader, find a matching fragment shader and link them together
    for (auto& shader_entry : vertex_shaders)
    {
        const std::string& base_name = shader_entry.first;
        std::shared_ptr<Shader> vertex_shader = shader_entry.second;

        if (fragment_shaders.find(base_name) != fragment_shaders.end())
        {
            std::shared_ptr<Shader> fragment_shader = fragment_shaders[base_name];
            std::shared_ptr<ShaderProgram> shader_program = std::make_shared<ShaderProgram>(vertex_shader, fragment_shader);
            if (shader_program->IsValid())
            {
                shader_programs.emplace(base_name, shader_program);
            }
        }
    }
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

bool Shader::LoadShaderSource(const std::string& shaderPath, std::string& shaderSource)
{
    std::string line;
    std::ifstream shader_filestream(shaderPath);
    if (shader_filestream.is_open())
    {
        while (getline(shader_filestream, line))
        {
            shaderSource += line + "\n";
        }
        shader_filestream.close();
        return true;
    }
    else
    {
        std::cout << "Failed to open file: " << shaderPath << std::endl;
        return false;
    }
}

void Renderer::LoadShaders(const std::string& resourcePath)
{
    // load all shaders from resourcePath, expecting a .vert and .frag file for each shader,
    // and store them in the shaders map
    DIR* dir;
    struct dirent* ent;

    if ((dir = opendir(resourcePath.c_str())) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            std::string fileName(ent->d_name);
            std::cout << "Loading resource: " << fileName << std::endl;
            std::string baseFileName = fileName.substr(0, fileName.find_last_of("."));

            if (fileName.find(".vert") != std::string::npos)
            {
                std::shared_ptr<Shader> vert_shader = std::make_shared<Shader>(resourcePath, baseFileName, ShaderType::Vertex);

                if (vert_shader->IsValid())
                {
                    vertex_shaders.emplace(baseFileName, vert_shader);
                }
            }
            else if (fileName.find(".frag") != std::string::npos)
            {
                std::shared_ptr<Shader> frag_shader = std::make_shared<Shader>(resourcePath, baseFileName, ShaderType::Fragment);

                if (frag_shader->IsValid())
                {
                    fragment_shaders.emplace(baseFileName, frag_shader);
                }
            }
        }
        closedir(dir);

        // now link all matching vertex and fragment shaders together
        LinkPrograms();
    }
    else
    {
        std::cout << "Failed to open directory: " << resourcePath << std::endl;
    }
}

std::shared_ptr<ShaderProgram> Renderer::GetShaderProgram(const std::string& shaderProgramName)
{
    if (shader_programs.find(shaderProgramName) != shader_programs.end())
    {
        return shader_programs[shaderProgramName];
    }
    else
    {
        std::cout << "Failed to find shader program: " << shaderProgramName << std::endl;
        return nullptr;
    }
}

void Renderer::AddObject(std::shared_ptr<MeshObject> object)
{
    objects.push_back(object);
}

Shader::Shader(const std::string& shaderPath, const std::string& shaderFile, const ShaderType shaderType)
: name(shaderFile)
{
    shader_type = shaderType;
    std::string shaderSource;
    std::string shaderFullPath = shaderPath + "/" + shaderFile + (shaderType == ShaderType::Vertex ? ".vert" : ".frag");
    
    if (LoadShaderSource(shaderFullPath, shaderSource))
    {
        shader_id = glCreateShader(shaderType == ShaderType::Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
        const GLchar* shaderSourcePtr = shaderSource.c_str();
        glShaderSource(shader_id, 1, &shaderSourcePtr, NULL);
        glCompileShader(shader_id);

        GLint compileStatus;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compileStatus);
        if (compileStatus != GL_TRUE)
        {
            std::cout << "Failed to compile " << (shaderType == ShaderType::Vertex ? "vertex" : "fragment") << " shader: " << shaderFile << std::endl;
            GLint logLength;
            glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &logLength);
            GLchar* log = new GLchar[logLength + 1];
            glGetShaderInfoLog(shader_id, logLength, NULL, log);
            std::cout << log << std::endl;
            delete[] log;

            glDeleteShader(shader_id);
            shader_id = GL_FALSE;
        }
        else
        {
            std::cout << "Successfully compiled shader: " << shaderFile << " id: " << shader_id << std::endl;
        }
    }
}

Shader::~Shader()
{
    glDeleteShader(shader_id);
}

ShaderProgram::ShaderProgram(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader)
    : name(vertexShader->name)
{
    if (!vertexShader->IsValid() || !fragmentShader->IsValid())
    {
        std::cout << "Failed to create shader program, invalid shader inputs\n";
        shader_program_id = GL_FALSE;
        return;
    }

    shader_program_id = glCreateProgram();
    glAttachShader(shader_program_id, vertexShader->GetShaderId());
    glAttachShader(shader_program_id, fragmentShader->GetShaderId());
    glLinkProgram(shader_program_id);

    GLint linkStatus;
    glGetProgramiv(shader_program_id, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE)
    {
        std::cout << "Failed to link shader program" << std::endl;
        GLint logLength;
        glGetProgramiv(shader_program_id, GL_INFO_LOG_LENGTH, &logLength);
        GLchar* log = new GLchar[logLength + 1];
        glGetProgramInfoLog(shader_program_id, logLength, NULL, log);
        std::cout << log << std::endl;
        delete[] log;

        glDeleteProgram(shader_program_id);
        shader_program_id = GL_FALSE;
    }
    else
    {
        std::cout << "Successfully linked shader program: " << name << " id: " << shader_program_id << std::endl;
    }
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(shader_program_id);
}

void ShaderProgram::Bind()
{
    glUseProgram(shader_program_id);
}

void ShaderProgram::Unbind()
{
    glUseProgram(0);
}

void ShaderProgram::SetUniform(const std::string &uniformName, const glm::vec3 &vector)
{
    GLint uniformLocation = glGetUniformLocation(shader_program_id, uniformName.c_str());
    if (uniformLocation != -1)
    {
        glUniform3fv(uniformLocation, 1, &vector[0]);
    }
    else
    {
        std::cout << "Failed to find uniform: " << uniformName << std::endl;
    }
}

void ShaderProgram::SetUniform(const std::string &uniformName, const glm::mat4 &matrix)
{
    GLint uniformLocation = glGetUniformLocation(shader_program_id, uniformName.c_str());
    if (uniformLocation != -1)
    {
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &matrix[0][0]);
    }
    else
    {
        std::cout << "Failed to find uniform: " << uniformName << std::endl;
    }
}
