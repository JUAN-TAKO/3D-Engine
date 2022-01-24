#ifndef GOBJECT_MODEL_H
#define GOBJECT_MODEL_H

#include <vector>
#include "AbstractMesh.h"
#include "GraphicContext.h"
#include "GraphicObject.h"
#include "Camera.h"
#include "Shader.h"

class AbstractMesh;
class GObjectModel{
private:
    static int gid;
    int id;
    AbstractMesh* mesh;
    GraphicContext& context;
    const Shader* shader;

    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
public:
    GObjectModel(GraphicContext& cont, const Shader* shader, AbstractMesh* m);
    ~GObjectModel();
    void initBuffers();
    void initVertexAttributes();
    void createBuffer(int size);
    void loadData(int offset, int size, const GLvoid* ptr);
    void loadIndices(int size, uint32_t* ptr);

    AbstractMesh* getMesh() const;
    const Shader* getShader() const;
    GraphicContext& getContext();
    GLuint getVAO() const;
    GLuint getVBO() const;
    GLuint getEBO() const;

    int getId() const {return id;}
};

#endif