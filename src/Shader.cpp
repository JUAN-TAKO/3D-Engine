#include "Shader.h"
#include "ShaderManager.h"
#include <iostream>

Shader::Shader(ShaderManager* m, const std::vector<GLint>& subs){
    manager = m;
    shader_id = glCreateProgram();
    subShaderIDs = subs;
    for(GLint id : subs){
        if(id == -1){
            std::cout << id << " not found" << std::endl;
            glDeleteProgram(shader_id);
            shader_id = -1;
            return;
        }
	    glAttachShader(shader_id, id);
    }
	glBindFragDataLocation(shader_id, 0, "outColor");
	glLinkProgram(shader_id);
    glUseProgram(shader_id);



    GLint count;

    GLint size; // size of the variable
    GLenum type; // type of the variable (float, vec3 or mat4, etc)

    const GLsizei bufSize = 64; // maximum name length
    GLchar name[bufSize]; // variable name in GLSL
    GLsizei length; // name length


    
    glGetProgramiv(shader_id, GL_ACTIVE_ATTRIBUTES, &count);
    printf("Active Attributes: %d\n", count);

    for (GLint i = 0; i < count; i++)
    {
        glGetActiveAttrib(shader_id, (GLuint)i, bufSize, &length, &size, &type, name);

        attributes.insert(std::make_pair(std::string(name), i));
        printf("Attribute #%d Type: %u Name: %s\n", i, type, name);
    }


    glGetProgramInterfaceiv(shader_id, GL_UNIFORM, GL_ACTIVE_RESOURCES, &count);

    //glGetProgramiv(shader_id, GL_ACTIVE_UNIFORMS, &count);
    printf("Active Uniforms: %d\n", count);

    for (GLint i = 0; i < count; i++)
    {
        glGetActiveUniform(shader_id, (GLuint)i, bufSize, &length, &size, &type, name);
        uniforms.insert(std::make_pair(std::string(name), i));
        printf("Uniform #%d Type: %u Name: %s\n", i, type, name);
    }


    std::cout << "unif list: " << std::endl;
    for(auto u : uniforms){
        std::cout << '\t' <<  u.first << std::endl;
    }

    std::cout << "attr list: " << std::endl;
    for(auto a : attributes){
        std::cout << '\t' <<  a.first << std::endl;
    }
}
GLint Shader::getId() const{
    return shader_id;
}
const std::vector<GLint>& Shader::getSubIDs() const{
    return subShaderIDs;
}

GLint Shader::getUniform(const std::string& name) const{
    auto f = uniforms.find(name);
    
    if(f == uniforms.end()){

        return -1;
    }
    return f->second;
}

GLint Shader::getAttribute(const std::string& name) const{
    auto f = attributes.find(name);
    
    if(f == attributes.end()){
        
        return -1;
    }

    return f->second;
}


void Shader::setUnif(const std::string& name, int count, int size, GLfloat* ptr) const{
    GLint attr = getUniform(name);
    if(attr != -1){

        glUniform1fv(attr, count*size, ptr);
    }
}

void Shader::setScal(const std::string& name, int count, GLfloat* ptr) const{
    setUnif(name, count, 1, ptr);
}

void Shader::setMat4(const std::string& name, int count, GLfloat* ptr) const{
    GLint unif = getUniform(name);
    if(unif != -1){
        glUniformMatrix4fv(unif, count, GL_FALSE, ptr);
    }
}

void Shader::setVec3(const std::string& name, int count, GLfloat* ptr) const{
    GLint unif = getUniform(name);
    if(unif != -1){
        glUniform3fv(unif, count, ptr);

    }
}


void Shader::setAttr(const std::string& name, GLint s, GLenum t, GLboolean n, GLsizei r, const void * p) const{
    
    GLint attr = getAttribute(name);
    if(attr != -1)
        setAttr(attr, s, t, n, r, p);

}
void Shader::setAttr(GLint id, GLint s, GLenum t, GLboolean n, GLsizei r, const void * p) const{

    glVertexAttribPointer (id, s, t, n, r, p);
    glEnableVertexAttribArray(id);
}


