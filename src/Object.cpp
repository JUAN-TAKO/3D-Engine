#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>
#include "Mesh.h"
#include "Object.h"
#include "Camera.h"

Object::Object(){
    transform = glm::mat4(1);
    transformAbs = transform;
    parent = nullptr;
    children = std::vector<Object*>();
}

void Object::update(double deltaT){
    if(parent){
        transformAbs = parent->transformAbs * transform;
    }
    else{
        transformAbs = transform;
    }
    customUpdate(deltaT);

    for (Object* c : children){
        c->update(deltaT);
    }
}

void Object::customUpdate(double deltaT){}

void Object::render(GraphicContext& context, Camera& camera){
    
}

Object& Object::setTransform(glm::mat4 t){
    transform = t;
    return *this;
}
Object& Object::addTo(Object* p){
    p->addChild_(this);
    setParent_(p);
    return *this;
}
Object& Object::add(Object* c){
    addChild_(c);
    c->setParent_(this);
    return *this;
}

void Object::setParent_(Object* p){
    parent = p;
}
void Object::addChild_(Object* c){
    children.push_back(c);
}

glm::mat4& Object::getTransform(){
    return transform;
}

glm::mat4& Object::getTransformAbsolute(){
    return transformAbs;
}

Object* Object::getParent(){
    return parent;
}
std::vector<Object*>& Object::getChildren(){
    return children;
}

void Object::customRender(GraphicContext& context, Camera& camera){}
