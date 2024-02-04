#pragma once

#include <vector>
#include <memory>

class MeshObject;

class Scene
{
public:
    Scene() = default;
    ~Scene() = default;

    void AddObject(std::shared_ptr<MeshObject> object);
    void Update(float deltaTime);
    void Render();

private:
    std::vector<std::shared_ptr<MeshObject>> objects;
};