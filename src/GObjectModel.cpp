#include "GObjectModel.h"
#include <iostream>

int GObjectModel::gid = 0;

GObjectModel::GObjectModel(GraphicContext& cont, const Shader* sh, Mesh* m)
: context(cont), shader(sh){
    mesh = m;
    id = gid++;
    initBuffers();
    initVertexAttributes(); 
}
void GObjectModel::initBuffers(){
    glGenVertexArrays(1, &VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    mesh->initBuffers(this);

    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndexSize(), mesh->getIndices(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void GObjectModel::initVertexAttributes(){
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    mesh->setAttributes(shader);

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GObjectModel::createBuffer(int size){
    glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);
}
void GObjectModel::loadData(int offset, int size, const GLvoid* ptr){
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, ptr);
}

GObjectModel::~GObjectModel(){
    glDeleteBuffers(1, & EBO);
	glDeleteBuffers(1, & VBO);
	glDeleteVertexArrays(1, & VAO);
}



GLuint GObjectModel::getVAO() const{
    return VAO;
}
GLuint GObjectModel::getVBO() const{
    return VBO;
}
GLuint GObjectModel::getEBO() const{
    return EBO;
}

Mesh* GObjectModel::getMesh() const{
    return mesh;
}
GraphicContext& GObjectModel::getContext(){
    return context;
}

const Shader* GObjectModel::getShader() const{
    return shader;
}