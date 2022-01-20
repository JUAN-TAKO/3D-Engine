#ifndef CUBE_H
#define CUBE_H

#include "Mesh.h"
#include "GraphicContext.h"
#include "GObjectModel.h"

class Cube : public Mesh{
private:
    static const GLfloat vertices[];
    static const GLuint indices[];
    static const GLfloat colors[];
    static const GLfloat normals[];
    
public:
    GLfloat* const getVertices() const;
    GLuint* const getIndices() const;
    GLfloat* const getColors() const;
    GLfloat* const getNormals() const;
    const size_t getVertexSize() const;
    const size_t getIndexSize() const;
    const size_t getTriangleNumber() const;

    void setAttributes(const Shader* shader) const;
    void initBuffers(GObjectModel* model);

};

#endif