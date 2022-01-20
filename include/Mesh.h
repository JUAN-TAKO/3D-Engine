#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

class GObjectModel;
class Mesh{

public:


    virtual GLfloat* const getVertices() const = 0;
    virtual GLuint* const getIndices() const = 0;
    virtual GLfloat* const getColors() const = 0;
    virtual GLfloat* const getNormals() const = 0;
    virtual size_t const getVertexSize() const = 0;
    virtual size_t const getIndexSize() const = 0;
    virtual size_t const getTriangleNumber() const = 0;
    virtual void setAttributes(const Shader* shader) const = 0;
    virtual void initBuffers(GObjectModel* model) = 0;
};

#endif