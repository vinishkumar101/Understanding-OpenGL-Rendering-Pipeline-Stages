#include "Mesh.h"

Mesh::Mesh()
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;

}

void Mesh::CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfvertices, unsigned int numOfIndices)
{
	indexCount = numOfIndices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO); // This almost like the array buffer down here, expect it is storing the elements or indices same thing but
			//  called two different terms we are making an a array buffer for our elements or an array buffer for indices... same concepts
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfvertices, vertices, GL_STATIC_DRAW);
	
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

			// Unbinding the IBO after the VAO because when you bind an IBO you are saying "bind this IBO to this VAO" but when we are unbinding before VAO "gets unbind IBO from this 
			// VAO" which dont want to happen we want that IBO to stay bound to the VAO, reason: VAO can have multiple VBO and as we unbind before VAO, It expectes for second or third 
			// VBO, but a VAO can have only one IBO/EBO (Index or Element buffer object, both are same concepts..)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Mesh::RenderMesh()
{
	glBindVertexArray(VAO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

			glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::ClearMesh()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;		
	}

	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}
	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	indexCount = 0;


}

Mesh::~Mesh()
{
	ClearMesh();
}