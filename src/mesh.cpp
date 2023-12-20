#include "mesh.h"
#include "renderer.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

Mesh::Mesh(std::vector<glm::vec3> vertices)
    : vertices(vertices)
{
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);

    glGenBuffers(1, &vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    // first vertex attribute is position, which is unnormalized floats
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Mesh::Render()
{
    glBindVertexArray(vao_id);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}

void MeshObject::Render()
{
    // create and set model view projection matrix
    static const float pi2 = glm::pi<float>() * 2.0f;
    const float cameraRotation = std::fmod(glfwGetTime() * 0.9, pi2);
    const float cameraRadius = 4.0f;
    glm::vec3 cameraPosition = glm::vec3(std::cos(cameraRotation) * cameraRadius, 0.0f, std::sin(cameraRotation) * cameraRadius);

    //std::cout << "Camera position: " << cameraPosition.x << ", " << cameraPosition.y << ", " << cameraPosition.z << std::endl;

    glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 view = glm::lookAt(cameraPosition, glm::vec3(0.0f), upVector);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1200.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 mvp = projection * view * objectTransform;

    shaderProgram->Bind();
    shaderProgram->SetUniform("mvp", mvp);

    // set material property uniforms here...

    mesh->Render();
}

PointCloud::PointCloud(std::vector<glm::vec3> vertices)
: Mesh(vertices)
{

}

void PointCloud::Render()
{
    glBindVertexArray(vao_id);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glDrawArrays(GL_POINTS, 0, vertices.size());
    glBindVertexArray(0);
}
