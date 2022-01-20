#include "GraphicObject.h"

GraphicObject::GraphicObject(GObjectModel* m){
    model = m;
    model->getContext().addInstance(this);
}

GObjectModel* GraphicObject::getModel() const {
    return model;
}
