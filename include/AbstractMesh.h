#ifndef ABSTRACT_MESH_H
#define ABSTRACT_MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

class GObjectModel;
class AbstractMesh{

public:

    virtual void setAttributes(const Shader* shader) const = 0;
    virtual void initVertexBuffer(GObjectModel* model) = 0;
    virtual void initIndexBuffer(GObjectModel* model) = 0;
    virtual size_t getVertexSize() const = 0;
    virtual ~AbstractMesh(){};
};

#endif