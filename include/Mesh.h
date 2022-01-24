#ifndef MESH_H
#define MESH_H

#include "AbstractMesh.h"

class Mesh : public AbstractMesh{
private:
    size_t nb_vertices;
    GLfloat* data;
    int stride;
    int norm_off;
    int tex_off;
    size_t nb_indices;
    GLuint* indices;

    void loadData(float* src, int components, int str, int offset){
        for(size_t i=0; i < nb_vertices*components; i+=stride){
            for(int j=0; j < components; j++){
                data[offset+i+j] = src[i*str+j];
            }
        }
    }
public:
    Mesh(size_t nb_vert, float* pdata, float* ndata, float* tdata, size_t in_stride, size_t nb_idx, uint32_t* idx);
    ~Mesh();
    void setAttributes(const Shader* shader) const;
    void initVertexBuffer(GObjectModel* model);
    void initIndexBuffer(GObjectModel* model);
    size_t getVertexSize() const;

};

#endif