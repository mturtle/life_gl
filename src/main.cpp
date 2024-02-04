#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>
#include <string>

#include "renderer.h"
#include "scene.h"
#include "mesh.h"

int main()
{
    std::cout << std::string("It's ALIVE") << std::endl;

    Renderer renderer(1200, 600);
    renderer.LoadShaders(std::string("../res/shaders"));

    Scene scene;

    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(std::vector<glm::vec3>{
        glm::vec3(-0.5f, -0.5f, 0.0f),
        glm::vec3( 0.5f, -0.5f, 0.0f),
        glm::vec3( 0.0f,  0.5f, 0.0f)
    });

    std::shared_ptr<ShaderProgram> basicShader = renderer.GetShaderProgram("basic");

    glm::mat4 objectTransform = glm::mat4(1.0f);
    //objectTransform = glm::translate(objectTransform, glm::vec3(0.0f, -1.0f, 0.0f));
    //objectTransform = glm::rotate(objectTransform, glm::radians(20.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    
    std::shared_ptr<MeshObject> meshObject = std::make_shared<MeshObject>(basicShader, mesh, objectTransform);
    renderer.AddObject(meshObject);

    // a sample point cloud
    std::vector<glm::vec3> points(1000);
    for (int idx = 0; idx < 1000; idx++)
    {
        points[idx] = glm::vec3( 2.0 * (std::rand() / (float)RAND_MAX) - 1.0f,
                                 2.0 * (std::rand() / (float)RAND_MAX) - 1.0f,
                                 2.0 * (std::rand() / (float)RAND_MAX) - 1.0f);
    }

    std::shared_ptr<Mesh> pointCloud = std::make_shared<PointCloud>(points);
    renderer.AddObject(std::make_shared<MeshObject>(basicShader, pointCloud, glm::mat4(1.0f)));
    float lastFrameTime = glfwGetTime();

    while (!glfwWindowShouldClose(renderer.render_window))
    {
        glfwPollEvents();

        scene.Update(0.0f);
        renderer.Render();
    }

    glfwDestroyWindow(renderer.render_window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}