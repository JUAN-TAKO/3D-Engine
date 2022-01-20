#include "GraphicContext.h"
#include "Camera.h"
#include <iostream>
#include "GObjectModel.h"
#include <glm/gtx/string_cast.hpp>



bool operator<(const GraphicObject& l, const GraphicObject& r)
{
    return l.getModel()->getId() < r.getModel()->getId();
}

GraphicContext::GraphicContext(ShaderManager* m){
	manager = m;
}


void GraphicContext::render(Camera& camera){
    GLint last_id = -1;
	for(GraphicObject* i : instances){
        glm::mat4& m = i->getTransformAbsolute();
        glm::mat4& v = camera.getV();
        glm::mat4& p = camera.getP();
        glm::mat4 vp = p * v;
        glm::mat4 mv = v * m;
        glm::mat4 mvp = vp * m;
        glm::mat4 Rm2w = glm::transpose(glm::inverse(m));

        const Shader* shader = i->getModel()->getShader();
        if(shader->getId() != last_id){
            last_id = shader->getId();
            glUseProgram(last_id);
        }
        shader->setMat4("mM", 1, &m[0][0]);
        shader->setMat4("mV", 1, &v[0][0]);
        shader->setMat4("mP", 1, &p[0][0]);

        shader->setMat4("mMV", 1, &mv[0][0]);
        shader->setMat4("mVP" , 1, &vp[0][0]);
        shader->setMat4("mMVP", 1, &mvp[0][0]);
        shader->setMat4("mRm2w", 1, &Rm2w[0][0]);

        glBindVertexArray(i->getModel()->getVAO());
        glDrawElements(GL_TRIANGLES, i->getModel()->getMesh()->getVertexSize(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

}


void GraphicContext::addModel(GObjectModel* m){
	models.push_back(m);
}

void GraphicContext::addInstance(GraphicObject* m){
	instances.insert(m);

}