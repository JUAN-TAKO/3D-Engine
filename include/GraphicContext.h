#ifndef GRAPHIC_CONTEXT_H
#define GRAPHIC_CONTEXT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <ShaderManager.h>
#include <vector>
#include <string>
#include <set>
#include <type_traits>

class Camera;
class GObjectModel;
class GraphicObject;

bool operator<(const GraphicObject& l, const GraphicObject& r);

class GraphicContext{
private:
    ShaderManager* manager;
    std::vector<GObjectModel*> models;

    struct Cmp{
        bool operator()(GraphicObject* a, GraphicObject* b) const {
            return *a < *b;
        }
    };
    
    std::multiset<GraphicObject*, Cmp> instances;
    


public:
    GraphicContext(ShaderManager* m);
    //~GraphicContext();
    void uniforms();
    
    void render(Camera& camera);
    void addModel(GObjectModel* m);
    void addInstance(GraphicObject* m);
};

#endif