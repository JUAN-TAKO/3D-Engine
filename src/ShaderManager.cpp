#include "ShaderManager.h"
#include <iostream>
#include <fstream>
#include <sstream>


std::string getFile(std::string filename){
    std::ifstream t(filename);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}


void PrintShaderInfoLog(GLint const Shader)
{
	int InfoLogLength = 0;
	int CharsWritten = 0;

	glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, & InfoLogLength);

	if (InfoLogLength > 0)
	{
		GLchar * InfoLog = new GLchar[InfoLogLength];
		glGetShaderInfoLog(Shader, InfoLogLength, & CharsWritten, InfoLog);
		std::cout << "Shader Info Log:" << std::endl << InfoLog << std::endl;
		delete [] InfoLog;
	}
}

GLuint initShader(std::string& source, GLenum type){
    GLint Compiled;
	GLuint shader = glCreateShader(type);
    GLchar* const glsrc = (GLchar*)source.c_str();
	glShaderSource(shader, 1, &glsrc, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &Compiled);
	if (! Compiled)
	{
		std::cerr << "Failed to compile vertex shader!" << std::endl;
		PrintShaderInfoLog(shader);
	}

    return shader;
}

void ShaderManager::addSubShader(const std::string& file){
    std::string name = fs::path(file).stem();
    std::string source = getFile(file);

    std::cout << name << std::endl;

    GLenum type;
    switch (name[0])
    {
        case 'V': type = GL_VERTEX_SHADER; break;
        case 'F': type = GL_FRAGMENT_SHADER; break;
      /*  case 'G': type = GL_GEOMETRY_SHADER; break;
        case 'C': type = GL_COMPUTE_SHADER; break;
        case 'T': type = GL_TESS_CONTROL_SHADER; break;
        case 'E': type = GL_TESS_EVALUATION_SHADER; break;  TODO: other types*/ 

    default:
        std::cout << "Shader name must start with a type indicator ('X_shadername.glsl')" << std::endl;
        std::cout << "\tV : vertex" << std::endl;
        std::cout << "\tF : fragment" << std::endl;
        /*std::cout << "\tG : geometry" << std::endl;
        std::cout << "\tC : compute" << std::endl;
        std::cout << "\tT : tesselation control" << std::endl;
        std::cout << "\tE : tesselation evaluation" << std::endl;*/

        return;
    }
    GLint sid = initShader(source, type);
    subShaders.insert(std::make_pair(name, sid));
}

void ShaderManager::addDir(const std::string& dir){
    for (const auto & entry : fs::directory_iterator(dir)){
        if(entry.is_directory())
            addDir(entry.path());
        else
            addSubShader(entry.path());
    }
}

ShaderManager::ShaderManager(const std::string& dir){
    std::cout << "Compiling..." << std::endl;
    addDir(dir);
    std::cout << "Compilation ok." << std::endl;
}

GLint ShaderManager::getSubShader(const std::string& name){
    auto s = subShaders.find(name);
    if(s == subShaders.end())
        return -1;
    else
        return s->second;
}
const Shader& ShaderManager::getShader(const std::vector<std::string>& names){
    std::vector<GLint> subs;
    for(auto n : names){
        GLint s = getSubShader(n);
        if(s == -1){
            std::cout << n << " not found" << std::endl;
            return *shaders.begin();
        }

        subs.push_back(s);
    }
    return getShader(subs);
}

const Shader& ShaderManager::getShader(const std::vector<GLint>& subs){
    std::set<Shader, ShaderManager::ShaderCmp>::iterator s = shaders.find(subs);
    if(s == shaders.end()){
        return *(shaders.insert(Shader(this, subs))).first;
    }
    else{
        return *s;
    }
}

ShaderManager::~ShaderManager(){
    for(auto s : shaders){
        glDeleteProgram(s.getId());
    }
    for(auto s : subShaders){
        glDeleteShader(s.second);
    }
}

