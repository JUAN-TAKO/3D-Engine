#include "Mesh.h"
#include <cstring>
#include "GObjectModel.h"

Mesh::Mesh(size_t nb_vert, float* pdata, float* ndata, float* tdata, size_t stride_in, size_t nb_idx, uint32_t* idx){
    nb_vertices = nb_vert;
    norm_off = (ndata == nullptr) ? 0 : 3;
    tex_off = (tdata == nullptr) ? 0 : norm_off+2;

    stride = 3 + std::max(norm_off, tex_off);

    data = new float[nb_vertices*stride];

    loadData(pdata, 3, stride_in, 0);
    if(norm_off) loadData(pdata, 3, stride_in, norm_off);
    if(tex_off) loadData(pdata, 2, stride_in, tex_off);

    nb_indices = nb_idx;
    indices = new uint32_t[nb_indices];
    std::memcpy(indices, idx, nb_indices);
}

Mesh::~Mesh(){
    delete data;
    delete indices;
}

void Mesh::setAttributes(const Shader* shader) const{
    shader->setAttr("position", 3, GL_FLOAT, false, stride, 0);
    if(norm_off)
        shader->setAttr("normal", 3, GL_FLOAT, false, stride, (const GLvoid*)norm_off);
    if(tex_off)
        shader->setAttr("texco", 2, GL_FLOAT, false, stride, (const GLvoid*)tex_off);
}

void Mesh::initVertexBuffer(GObjectModel* model){
    model->createBuffer(nb_vertices*stride);
    model->loadData(0, nb_vertices*stride, data);
}

void Mesh::initIndexBuffer(GObjectModel* model){
    model->loadIndices(nb_indices, indices);
}


size_t Mesh::getVertexSize() const{
    return nb_vertices;
}
