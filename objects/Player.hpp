#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"
#include "Camera.h"
#include <glm/gtx/string_cast.hpp>

class Player : public Object{
private:
    Camera* cam;
    GLFWwindow* window;
    float speed;

public:
    Player(Camera* c, GLFWwindow* win, float spd){
        cam = c;
        window = win;
        speed = spd;

        this->add(cam);
    }

    void customUpdate(double deltaT){
        glfwPollEvents();
		glm::vec3 dir = glm::vec3(0, 0, 0);
        
        if(glfwGetKey(window, GLFW_KEY_W))
            dir += glm::vec3(0,0,1);
        
        if(glfwGetKey(window, GLFW_KEY_S))
            dir += glm::vec3(0,0,-1);
        
        if(glfwGetKey(window, GLFW_KEY_A))
            dir += glm::vec3(1,0,0);
        
        if(glfwGetKey(window, GLFW_KEY_D))
            dir += glm::vec3(-1,0,0);

        dir *= speed*(float)deltaT;
		transform = glm::translate(transform, dir);

    }
};

#endif