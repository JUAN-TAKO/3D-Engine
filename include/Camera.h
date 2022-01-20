#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <Object.h>
#include <GraphicContext.h>

class Camera : public Object{
private:
    GraphicContext context;
    glm::mat4 projection;
    glm::mat4& view = this->getTransformAbsolute();
    glm::mat4 vp;

    GLint projection_id;
    GLint view_id;
    GLint vp_id;

public:
    Camera(GraphicContext& c, glm::mat4 proj);
    glm::mat4& getV();
    glm::mat4& getP();
};

#endif