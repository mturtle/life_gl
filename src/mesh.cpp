#include "mesh.h"
#include "renderer.h"

#include <iostream>

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

void Mesh::Bind()
{
    glBindVertexArray(vao_id);
}

void Mesh::Unbind()
{
    glBindVertexArray(0);
}

void MeshObject::Render()
{
    mesh->Bind();

    // set transform and material property uniforms
    shaderProgram->SetUniform("object_transform", transform);
    glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.size());

    mesh->Unbind();
}
