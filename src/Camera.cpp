#include "Camera.h"
#include "Object.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

Camera::Camera(GraphicContext& c, glm::mat4 proj)
: context(c){
    projection = proj;
    vp = projection * view;
}

glm::mat4& Camera::getV(){
    return view;
}
glm::mat4& Camera::getP(){
    return projection;
}