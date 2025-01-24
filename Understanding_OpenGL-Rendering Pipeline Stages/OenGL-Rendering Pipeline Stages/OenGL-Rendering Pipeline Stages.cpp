#include<GL\glew.h>
#include<GLFW\glfw3.h>

#include<string.h>
#include<stdio.h>
#include<vector>
#include<cmath>


#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include<glm\gtc\type_ptr.hpp>  //We will be using the type pointer to pass the value to the shader because as the value are being stored by GLM, they arent fit to be
//passed as raw values to the shader. We need to actually have a pointer to the actual locaion there and thats what the type pointer will be handling there. 

//Custom Class that we've created
#include"Mesh.h"
#include"Shader.h"
#include"MainWindow.h"

//Preprocessors
#ifndef M_PI
#define M_PI 3.14159265f
#endif

//Initialization for to acess from the class we have created.
MainWindow MainScreen;
std::vector<Mesh*> meshList;
std::vector<Shader> ShaderList;


bool Direction = true;

// Translate.....Currently not using this so commented it out.
//float triOffset = 0.0f;
//float triMaxOffset = 0.7f;
//float triIncrement = 0.00005f;

// Rotation
float currentAngle = 0.0f;
const float toRadians = M_PI / 180.0f;

//Scale.....Currently not using this so commented it out.
//bool sizeDirection = true;
//float currentSize = 0.4f;
//float maxSize = 0.4f;
//float minSize = 0.1f;


// Vertex Shader
static const char* vertex_shader = "Shaders/Shader.vert";

// Fragment Shader	
static const char* fragment_shader = "Shaders/Shader.frag";



void CreateObjects()
{
	//Instead of repeating specifying the points to draw a 3D triangle we are using IBO - (Index buffer object) so that we can reuse the specified vertex points as we can
	unsigned int triangle3D_indices[] = {

		// Defining the order to draw the 3D triangle
		// these 0,3,1 are nothing but the index from the triangle_vertices array, u can think like: we are accessing and arranging them as per our need
		0, 3, 1,	// the other side 😅
		1, 3, 2,	// backward maybe
		2, 3, 0,	// Front face
		0, 1, 2		// Base
	};

	GLfloat triangle_vertices[] = {
		-1.0f,-1.0f,0.0f, //  Bottom Left.............0
		0.0f, -1.0f, 1.0f, // background for indepth so that the object could be created as pyramid shape.............1
		1.0f,-1.0f,0.0f,  //  Bottom Right..............2
		0.0f,1.0f,0.0f    //  Top...............3
	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(triangle_vertices, triangle3D_indices, 12, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(triangle_vertices, triangle3D_indices, 12, 12);
	meshList.push_back(obj2);
}

void createShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vertex_shader, fragment_shader);
	ShaderList.push_back(*shader1);
}

int main() {

	MainScreen = MainWindow(1000, 600);
	MainScreen.Initialize();

	CreateObjects();
	createShaders();

	GLuint uniformProjection = 0, uniformModel = 0;

	glm::mat4 projection(1.0f);
	projection = glm::perspective(45.0f, MainScreen.getBufferWidth() / MainScreen.getBufferHeight(), 0.1f, 100.0f); // the first argument is fovy: means field of view Y.

	while (!MainScreen.getShouldClose())
	{
		// get Handle User Input
		glfwPollEvents();

		//Translating Moving the triangle vertically and horizontly 
		/*if (Direction).....Currently not using this so commented it out.
		{
			triOffset += triIncrement;
		}
		else
		{
			triOffset -= triIncrement;
		}

		if (abs(triOffset) >= triMaxOffset)
		{
			Direction = !Direction;
		}*/

		// Rotation
		currentAngle += 0.01f;
		if (currentAngle >= 360)
		{
			currentAngle -= 360;
		}

		//Scaling.....Currently not using this so commented it out.
		/*if (sizeDirection)
		{
			currentSize += 0.0001f;
		}
		else
		{
			currentSize -= 0.0001f;
		}

		if (currentSize > maxSize || currentSize <= minSize)
		{
			sizeDirection = !sizeDirection;
		}*/

		// Clear Window
		glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ShaderList[0].useShader();
		uniformModel = ShaderList[0].GetModelLocation();
		uniformProjection = ShaderList[0].GetProjectionLocation();

		// Model 1
		glm::mat4 model(1.0f);

		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -2.7f));
		model = glm::rotate(model, currentAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

		// All done now the tringle might be rotating but the front face seems to not be rotating as expected thats because of lack of depth buffer
		// as we know that depth buffer stores the depth information of each pixel in a scene

		/*Basically in order to tell which triangle should be drawn over the top of others to make sure that things are drawn in the right order, we need to have
		a depth buffer to determine which triangles are behind others*/

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		meshList[0]->RenderMesh();

		//Model2
		glm::mat4 model2(1.0f);
		model2 = glm::translate(model2, glm::vec3(1.0f, 0.0f, -2.7f));
		model2 = glm::rotate(model2, currentAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model2 = glm::scale(model2, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model2));
		meshList[1]->RenderMesh();

		glUseProgram(0);

		//Swap front and back buffers
		MainScreen.swapBuffers();
	}

	return 0;
}