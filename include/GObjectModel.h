#ifndef GOBJECT_MODEL_H
#define GOBJECT_MODEL_H

#include <vector>
#include "Mesh.h"
#include "GraphicContext.h"
#include "GraphicObject.h"
#include "Camera.h"
#include "Shader.h"

class Mesh;
class GObjectModel{
private:
    static int gid;
    int id;
    Mesh* mesh;
    GraphicContext& context;
    const Shader* shader;

    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
public:
    GObjectModel(GraphicContext& cont, const Shader* shader, Mesh* m);
    ~GObjectModel();
    void initBuffers();
    void initVertexAttributes();

    void createBuffer(int size);
    void loadData(int offset, int size, const GLvoid* ptr);

    Mesh* getMesh() const;
    const Shader* getShader() const;
    GraphicContext& getContext();
    GLuint getVAO() const;
    GLuint getVBO() const;
    GLuint getEBO() const;

    int getId() const {return id;}
};

#endif