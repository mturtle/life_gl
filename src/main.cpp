#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <iostream>
#include <string>

#include "renderer.h"
#include "mesh.h"

int main()
{
    std::cout << std::string("It's ALIVE") << std::endl;

    Renderer renderer(1200, 600);
    renderer.LoadShaders(std::string("../res/shaders"));

    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(std::vector<glm::vec3>{
        glm::vec3(-0.5f, -0.5f, 0.0f),
        glm::vec3( 0.5f, -0.5f, 0.0f),
        glm::vec3( 0.0f,  0.5f, 0.0f)
    });

    std::shared_ptr<ShaderProgram> shaderProgram = renderer.GetShaderProgram("basic");
    std::shared_ptr<MeshObject> meshObject = std::make_shared<MeshObject>(shaderProgram, mesh, glm::mat4(1.0f));
    renderer.AddObject(meshObject);

    while (!glfwWindowShouldClose(renderer.render_window))
    {
        glfwPollEvents();
        renderer.Draw();
    }

    glfwDestroyWindow(renderer.render_window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}