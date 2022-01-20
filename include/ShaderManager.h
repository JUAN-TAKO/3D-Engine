#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <unordered_map>
#include <set>
#include <string>
#include <filesystem>
#include <iostream>

#include "Shader.h"

namespace fs = std::filesystem;

class ShaderManager{
private:
    std::unordered_map<std::string, GLint> subShaders;


    struct ShaderCmp{
        using is_transparent = void;

        bool operator()(const Shader& s1, const Shader& s2) const{
            return (*this)(s1.getSubIDs(), s2.getSubIDs());
        }
        bool operator()(const std::vector<GLint>& s1, const Shader& s2) const{
            return (*this)(s1, s2.getSubIDs());
        }
        bool operator()(const Shader& s1, const std::vector<GLint>& s2) const{
            return (*this)(s1.getSubIDs(), s2);
        }
        bool operator()(const std::vector<GLint>& s1, const std::vector<GLint>& s2) const{
            if(s1.size() == s2.size()){
                for(size_t i=0; i < s1.size(); i++){
                    if(s1[i] != s2[i])
                        return s1[i] < s2[i];
                }
                return false;
            }
            else{
                return s1.size() < s2.size();
            }
        }
    };
    std::set<Shader, ShaderCmp> shaders;

public:
    ShaderManager(const std::string& dir);
    ~ShaderManager();
    void addDir(const std::string& dir);
    void addSubShader(const std::string& file);
    GLint getSubShader(const std::string& name);

    const Shader& getShader(const std::vector<std::string>& names);
    const Shader& getShader(const std::vector<GLint>& subs); 
};

#endif