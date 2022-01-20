#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <unordered_map>
#include <vector>
#include <string>
class ShaderManager;
class Shader{
private:
    GLint shader_id;
    std::vector<GLint> subShaderIDs;
    ShaderManager* manager;
    std::unordered_map<std::string, GLint> uniforms;
    std::unordered_map<std::string, GLint> attributes;


public:
    Shader(ShaderManager* m, const std::vector<GLint>& subs);
    GLint getId() const;
    const std::vector<GLint>& getSubIDs() const;

    GLint getUniform(const std::string& name) const;
    GLint getAttribute(const std::string& name) const;
    
    void setUnif(const std::string& name, int count, int size, GLfloat* ptr) const;
    void setScal(const std::string& name, int count, GLfloat* ptr) const;
    void setMat4(const std::string& name, int count, GLfloat* ptr) const;
    void setVec3(const std::string& name, int count, GLfloat* ptr) const;

    void setAttr(GLint id, GLint s, GLenum t, GLboolean n, GLsizei r, const void * p) const;
    void setAttr(const std::string& name, GLint s, GLenum t, GLboolean n, GLsizei r, const void * p) const;

};

#endif