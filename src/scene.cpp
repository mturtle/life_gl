#include "scene.h"
#include "mesh.h"

void Scene::AddObject(std::shared_ptr<MeshObject> object)
{
    objects.push_back(object);
}

void Scene::Update(float deltaTime)
{
    for (std::shared_ptr<MeshObject> object : objects)
    {
        object->Update(deltaTime);
    }
}

void Scene::Render()
{
    // transform hierarchy stuff could be done here
    for (std::shared_ptr<MeshObject> object : objects)
    {
        object->Render();
    }
}
