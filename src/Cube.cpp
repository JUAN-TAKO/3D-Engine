#include "Cube.h"
#include <iostream>

GLfloat const Cube::vertices[] = {
    -0.5f,0.5f,-0.5f, //A0 left
    -0.5f,0.5f,0.5f,  //B1 up
    0.5f,0.5f,-0.5f,  //C2 right
    0.5f,0.5f,0.5f,   //D3 
        
    -0.5f,-0.5f,-0.5f,//E4 
    -0.5f,-0.5f,0.5f, //F5 bottom
    0.5f,-0.5f,-0.5f, //G6 front
    0.5f,-0.5f,0.5f   //H7 back
};

GLfloat const Cube::normals[] = {
    1.0f,0.0f,0.0f, //A0 left
    0.0f,-1.0f,0.0f,  //B1 up
    -1.0f,0.0f,0.0f,  //C2 right
    0.0f,0.0f,0.0f,   //D3 
        
    0.0f,0.0f,0.0f,//E4 
    0.0f,1.0f,0.0f, //F5 bottom
    0.0f,0.0f,1.0f, //G6 front
    0.0f,0.0f,-1.0f   //H7 back
};

GLuint const Cube::indices[] = {
        /*Above ABC,BCD*/
        1,2,0,
        1,3,2,
 
        /*Following EFG,FGH*/
        5,4,6,
        5,6,7,

        /*Left ABF,AEF*/
        0,5,1,
        0,4,5,
        
        /*Right side CDH,CGH*/
        2,3,7,
        2,7,6,
        
        /*ACG,AEG*/
        6,0,2,
        6,4,0,
        
        /*Behind BFH,BDH*/
        7,1,5,
        7,3,1
};

GLfloat const Cube::colors[] = {

    0.0f,1.0f,0.0f, //A0
    0.0f,1.0f,1.0f,  //B1
    1.0f,1.0f,0.0f,  //C2
    1.0f,1.0f,1.0f,   //D3
        
    0.0f,0.0f,0.0f,//E4
    0.0f,0.0f,1.0f, //F5
    1.0f,0.0f,0.0f, //G6
    1.0f,0.0f,1.0f   //H7
};

GLfloat* const Cube::getVertices() const{
    return (GLfloat*)vertices;
}

GLuint* const Cube::getIndices() const{
    return (GLuint*)indices;
}

GLfloat* const Cube::getColors() const{
    return (GLfloat*)colors;
}

GLfloat* const Cube::getNormals() const{
    return (GLfloat*)normals;
}

size_t Cube::getVertexSize() const{
    return sizeof(vertices);
}

size_t Cube::getIndexSize() const{
    return sizeof(indices);
}

size_t Cube::getTriangleNumber() const{
    return sizeof(indices)/(3*sizeof(GLuint));
}

void Cube::initVertexBuffer(GObjectModel* model){
    model->createBuffer(getVertexSize()*3);
    model->loadData(0, getVertexSize(), getVertices());
    model->loadData(getVertexSize(), getVertexSize(), getColors());
    model->loadData(getVertexSize()*2, getVertexSize(), getNormals());
}

void Cube::initIndexBuffer(GObjectModel* model){
    model->loadIndices(getIndexSize(), getIndices());
}

void Cube::setAttributes(const Shader* shader) const{
    shader->setAttr("position", 3, GL_FLOAT, false, 0, 0);
    shader->setAttr("color", 3, GL_FLOAT, false, 0, (const GLvoid*)getVertexSize());
    shader->setAttr("normal", 3, GL_FLOAT, false, 0, (const GLvoid*)(getVertexSize()*2));

}
