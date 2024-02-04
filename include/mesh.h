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

    virtual void Render();

protected:
    std::vector<glm::vec3> vertices;
    unsigned int vbo_id;
    unsigned int vao_id;
};

class PointCloud : public Mesh
{
public:
    PointCloud() = default;
    PointCloud(std::vector<glm::vec3> vertices);

    void Render() override;
};


class MeshObject {
public:
    MeshObject(std::shared_ptr<ShaderProgram> shaderProgram, std::shared_ptr<Mesh> meshObject, glm::mat4 transform)
        : shaderProgram(shaderProgram), mesh(meshObject), objectTransform(transform) {}

    void Update(float deltaTime) {}
    void Render();

private:
    std::shared_ptr<ShaderProgram> shaderProgram;
    std::shared_ptr<Mesh> mesh;
    glm::mat4 objectTransform;
};