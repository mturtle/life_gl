#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>

class ShaderProgram;

/// A base minimal mesh class, built from a vector of 3D vertex positions
class Mesh
{
public:
    Mesh() = default;
    Mesh(std::vector<glm::vec3> vertices);

    void Bind();
    void Unbind();

    std::vector<glm::vec3> vertices;

private:

    unsigned int vbo_id;
    unsigned int vao_id;
};

class MeshObject {
public:
    MeshObject(std::shared_ptr<ShaderProgram> shaderProgram, std::shared_ptr<Mesh> meshObject, glm::mat4 transform)
        : shaderProgram(shaderProgram), mesh(meshObject), transform(transform) {}

    void Update() {}
    void Render();

    // TODO: Add methods to update the transform, shader program, and VBO

private:
    std::shared_ptr<ShaderProgram> shaderProgram;
    std::shared_ptr<Mesh> mesh;
    glm::mat4 transform;
};