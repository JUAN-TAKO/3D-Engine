#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>


#include <Cube.h>
#include <Object.h>
#include <GraphicContext.h>
#include <Camera.h>
#include <GraphicObject.h>
#include <GObjectModel.h>
#include <Player.hpp>
#include <ShaderManager.h>
#include <MeshManager.h>

void PrintOpenGLErrors(char const * const Function, char const * const File, int const Line)
{
	GLenum Error = glGetError();
	if (Error != GL_NO_ERROR)
	{
		char const * ErrorString = (char const *) gluErrorString(Error);
		if (ErrorString)
			std::cerr << ("OpenGL Error in %s at line %d calling function %s: '%s'", File, Line, Function, ErrorString) << std::endl;
		else
			std::cerr << ("OpenGL Error in %s at line %d calling function %s: '%d 0x%X'", File, Line, Function, Error, Error) << std::endl;
	}
}

#define CheckOpenGLErrors(x) PrintOpenGLErrors(">>BEFORE<< "#x, __FILE__, __LINE__);

GLFWwindow* initWindow(){
    GLFWwindow* window;

	if (! glfwInit())
		return nullptr;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
	if (! window)
	{
		glfwTerminate();
		return nullptr;
	}
	
    glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		glfwTerminate();
		return nullptr;
	}
    std::cout << glGetString(GL_VERSION) << std::endl;



	glClearColor(0.2f, 0.2f, 0.2f, 1);
    glEnable(GL_CULL_FACE);  
	glEnable(GL_DEPTH_TEST);
	glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);

    return window;
}


int main()
{
	GLFWwindow* window = initWindow();

	ShaderManager shaderManager = ShaderManager("shaders");
	MeshManager meshManager = MeshManager("resources");

	GraphicContext context = GraphicContext(&shaderManager);

	Cube cubeMesh = Cube();

	const Shader& cubeShader = shaderManager.getShader(std::vector<std::string>({"V_smooth", "F_smooth"}));

	GObjectModel model = GObjectModel(context, &cubeShader, meshManager.getMesh("Mars 2K.Mars_Cube.002"));

	Object scene = Object();
	GraphicObject obj = GraphicObject(&model);
	//GraphicObject light = GraphicObject(&cubeModel);

	obj.addTo(&scene);
	//light.addTo(&scene);

    glm::mat4 projection = glm::perspective(glm::radians(80.0f), 960.0f / 540.0f, 0.1f, 1000.0f);
	Camera cam(context, projection);
	cam.setTransform(glm::lookAt(
        glm::vec3(0,0,-4), // Camera is at (0,0,-2), in World Space
        glm::vec3(0,0,0), // and looks at the origin
        glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    ));

	Player p(&cam, window, 3.0f);
	scene.add(&p);
	
	glm::vec3 lightDir = glm::normalize(glm::vec3(0, 0, 1));
	glm::vec3 lightColor(1.0f,1.0f,1.0f);
	float lightAmbiant = 0.03f;
	//glUniform3fv(context.getLocLightPos(), 1, &lightPos[0]);

	//glm::mat4 lightTransform = glm::scale(glm::translate(glm::mat4(1), -lightPos), glm::vec3(0.2f, 0.2f, 0.2f));
	//light.setTransform(lightTransform);


	cubeShader.setVec3("light.direction", 1, (GLfloat*)&lightDir[0]);
    cubeShader.setVec3("light.color", 1, (GLfloat*)&lightColor[0]);
    cubeShader.setScal("light.ambiant", 1, &lightAmbiant);

	auto start = std::chrono::steady_clock::now();
	auto stop = std::chrono::steady_clock::now();
	
	while (! glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		stop = std::chrono::steady_clock::now();
		double seconds = ((double)std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count())/(1000000.0);
		scene.update(seconds);
		start = std::chrono::steady_clock::now();
		
		
		
		context.render(cam);
		glm::mat4 t = glm::rotate(obj.getTransform(), (float)glm::radians(0.5), glm::vec3(2.0f, 1.0f, 0));
		obj.setTransform(t);
		glfwSwapBuffers(window);
		

		//std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	glfwTerminate();
	return 0;
}