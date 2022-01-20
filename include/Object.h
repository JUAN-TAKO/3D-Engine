#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "GraphicContext.h"

class Camera;
class Mesh;

class Object{
protected:
    glm::mat4 transform;
    glm::mat4 transformAbs;
    Object* parent;
    std::vector<Object*> children;

    bool fresh; //fresh is true if preRender has been called since last render

    void setParent_(Object* p);
    void addChild_(Object* c);
public:
    Object();
    void render(GraphicContext& context, Camera& camera);
    virtual void update(double deltaT);
    virtual void customUpdate(double deltaT);
    virtual void customRender(GraphicContext& context, Camera& camera);
    Object& setTransform(glm::mat4 t);
    glm::mat4& getTransform();
    glm::mat4& getTransformAbsolute();
    Object* getParent();
    std::vector<Object*>& getChildren();


    Object& addTo(Object* p);
    Object& add(Object* c);


};

#endif