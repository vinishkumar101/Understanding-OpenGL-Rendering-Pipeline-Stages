#pragma once

#include<GL\glew.h>

class Mesh
{
public:
	Mesh();

	void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfvertices, unsigned int numOfIndices);
	void RenderMesh( );
	void ClearMesh();

	~Mesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;			// GLsizei is basically an integer but the GL or Glu even recognizes that as variable to represent the size of something such as of an array
};

