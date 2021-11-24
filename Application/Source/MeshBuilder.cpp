#include "MeshBuilder.h"
#include <GL\glew.h>
#include "Vertex.h"
#include <vector>
#include "MyMath.h"

/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName,Color color, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	v.pos.Set(-100, 0.f, 0.f); v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(100, 0.f, 0.f); v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.f, -100, 0.f); v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.f, 100, 0.f); v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.f, 0.f, -100); v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.f, 0.f, 100); v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	for (int i = 0; i < 6; i++)
		index_buffer_data.push_back(i);

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() *
		sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size()
		* sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_LINES;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName,Color color, float lengthX, float lengthY)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	v.pos.Set(0.5f, 0.5f, 0.5f); v.color = color; v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f); v.color = color; v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f); v.color = color; v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f); v.color = color; v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);



	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	


	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() *
		sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size()
		* sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLES;
	mesh->indexSize = index_buffer_data.size();
	return mesh;

}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName,Color color, float lengthX, float lengthY, float lengthZ)
{

	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	v.pos.Set(0.5f, 0.5f, 0.5f); v.color = color; v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f); v.color = color; v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f); v.color = color; v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f); v.color = color; v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);


	v.pos.Set(0.5f, 0.5f, -0.5f); v.color = color; v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f); v.color = color; v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f); v.color = color; v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f); v.color = color; v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);



	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);

	//top
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(0);

	//bottom
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(7);

	//right
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(7);

	//left
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(2);

	//back
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(7);



	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() *
		sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size()
		* sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLES;
	mesh->indexSize = index_buffer_data.size();
	return mesh;
	return mesh;
}

Mesh* MeshBuilder::GenerateCircle(const std::string& meshName, Color color, unsigned numSlices, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float radianPerSlice = Math::TWO_PI / numSlices;

	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		float theta = slice * radianPerSlice;
		float x = radius * cosf(theta);
		float y = 0;
		float z = radius * sinf(theta);

		v.pos.Set(x, y, z);		v.color = color;	vertex_buffer_data.push_back(v);
		v.pos.Set(0, 0, 0);		v.color = color;	vertex_buffer_data.push_back(v);
	}
	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		index_buffer_data.push_back(slice * 2 + 0);
		index_buffer_data.push_back(slice * 2 + 1);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateSphere(const std::string& meshName, Color color, unsigned numStacks, unsigned numSlices, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float degreePerStack = 180.f / numStacks;
	float degreePerSlice = 360.f / numSlices;

	for (unsigned stack = 0; stack < numStacks + 1; ++stack)
	{
		float phi = -90.f + stack * degreePerStack;
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			float theta = slice * degreePerSlice;
			float x = cosf(Math::DegreeToRadian(phi)) * cosf(Math::DegreeToRadian(theta));
			float y = sinf(Math::DegreeToRadian(phi));
			float z = cosf(Math::DegreeToRadian(phi)) * sinf(Math::DegreeToRadian(theta));

			v.pos.Set(radius * x,radius *  y,radius *  z);		
			v.color = color;	
			v.normal.Set(x, y, z);
			vertex_buffer_data.push_back(v);
		}
	}
	for (unsigned stack = 0; stack < numStacks; ++stack)
	{
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			index_buffer_data.push_back(stack * (numSlices + 1) + slice);
			index_buffer_data.push_back((stack + 1) * (numSlices + 1) + slice);
		}
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}
