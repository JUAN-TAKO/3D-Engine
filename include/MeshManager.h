#ifndef MESH_MANAGER_H
#define MESH_MANAGER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <unordered_map>
#include <set>
#include <string>
#include <filesystem>
#include <iostream>

#include "AbstractMesh.h"

namespace objl{
    class Loader;
}

namespace fs = std::filesystem;

class MeshManager{
private:
    objl::Loader* loader;
    std::unordered_map<std::string, AbstractMesh*> meshes;
    void addMesh(const std::string& file);

public:
    void addDir(const std::string& dir);
    MeshManager(const std::string& dir);
    ~MeshManager();
    AbstractMesh* getMesh(const std::string& name);
};

#endif