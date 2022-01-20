#ifndef GRAPHIC_OBJECT_H
#define GRAPHIC_OBJECT_H

#include "Object.h"
#include "GObjectModel.h"
#include "GraphicContext.h"
#include "Camera.h"

class GraphicObject : public Object{
private:
    GObjectModel* model;
public:
    GraphicObject(GObjectModel* m);
    GObjectModel* getModel() const;
};

#endif