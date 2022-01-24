#ifndef CUBE_H
#define CUBE_H

#include "AbstractMesh.h"
#include "GraphicContext.h"
#include "GObjectModel.h"

class Cube : public AbstractMesh{
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
    size_t getVertexSize() const;
    size_t getIndexSize() const;
    size_t getTriangleNumber() const;
    ~Cube(){}

    void setAttributes(const Shader* shader) const;
    void initVertexBuffer(GObjectModel* model);
    void initIndexBuffer(GObjectModel* model);


};

#endif