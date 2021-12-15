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
	// top right 
	v.pos.Set(0.5f, 0.5f, 0.5f); v.color = color; v.normal.Set(0, 0, 1);
	v.texCoord.Set(10, 10);
	vertex_buffer_data.push_back(v);
	// top left
	v.pos.Set(-0.5f, 0.5f, 0.5f); v.color = color; v.normal.Set(0, 0, 1);
	v.texCoord.Set(0, 10);
	vertex_buffer_data.push_back(v);
	//botom left
	v.pos.Set(-0.5f, -0.5f, 0.5f); v.color = color; v.normal.Set(0, 0, 1);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);
	//bottom right
	v.pos.Set(0.5f, -0.5f, 0.5f); v.color = color; v.normal.Set(0, 0, 1);
	v.texCoord.Set(10, 0);
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
			//v.texCoord.Set(x,y);
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

Mesh* MeshBuilder::GenerateCone(const std::string& meshName, Color color, int rad, int height)
{

	std::vector<Vertex> vertex;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	v.color = color;

	for (float theta = 0; theta <= 360; theta += 2) {
		v.pos.Set(rad * cos(Math::DegreeToRadian(theta)), -height / 2.0, (float)rad * sin(Math::DegreeToRadian(theta)));
		v.normal.Set(height * cos(Math::DegreeToRadian(theta)), (float)rad, height * sin(Math::DegreeToRadian(theta)));
		v.normal.Normalize();
		vertex.push_back(v);

		v.pos.Set(0, (float)height / 2.0, 0);
		v.normal.Set(height * cos(Math::DegreeToRadian(theta)), (float)rad, height * sin(Math::DegreeToRadian(theta)));
		v.normal.Normalize();
		vertex.push_back(v);
	}

	for (float theta = 0; theta <= 360; theta += 2) {

		v.pos.Set(0, -height / 2.0, 0);
		v.normal.Set(0, -1, 0);
		vertex.push_back(v);

		v.pos.Set(rad * cos(Math::DegreeToRadian(theta)), -height / 2.0, rad * sin(Math::DegreeToRadian(theta)));
		v.normal.Set(0, -1, 0);
		vertex.push_back(v);
	}

	for (int i = 0; i < vertex.size(); i++) {
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	
	return mesh;
}

Mesh* MeshBuilder::GenerateHalfCone(const std::string& meshName, Color color, int rad, int height)
{

	std::vector<Vertex> vertex;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	v.color = color;
	for (float theta = 1; theta <= 179; theta += 2) {
		if (theta > 179) theta = 179;
		float z = rad * sin(Math::DegreeToRadian(theta));
		v.pos.Set(rad * cos(Math::DegreeToRadian(theta)), (float)-height / 2.0, z);
		v.normal.Set(height * cos(Math::DegreeToRadian(theta)), (float)rad, z);
		v.normal.Normalize();
		vertex.push_back(v);

		v.pos.Set(0, (float)height / 2.0, 0);
		v.normal.Set(height * cos(Math::DegreeToRadian(theta)), (float)rad, z);
		v.normal.Normalize();
		vertex.push_back(v);
	}

	for (float theta = 1; theta <= 179; theta += 2) {
		if (theta > 179) theta = 179;

		float z = rad * sin(Math::DegreeToRadian(theta));
		v.pos.Set(rad * cos(Math::DegreeToRadian(theta)), (float)-height / 2.0, z);
		v.normal.Set(0, -1, 0);
		vertex.push_back(v);

		v.pos.Set(0, (float)-height / 2.0, 0);
		v.normal.Set(0, -1, 0);
		vertex.push_back(v);
	}
	v.normal.Set(0, 0, -1);
	v.pos.Set(0, (float)height / 2.0, 0); vertex.push_back(v);
	v.pos.Set((float)rad, (float)-height / 2.0, 0); vertex.push_back(v);
	v.pos.Set((float)-rad, (float)-height / 2.0, 0); vertex.push_back(v);

	for (unsigned int i = 0; i < vertex.size(); i++) {
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateConicalFrustum(const std::string& meshName, Color color, float innerR, float outerR, int height)
{

	std::vector<Vertex> vertex;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	v.color = color;

	for (float theta = 0; theta <= 360; theta += 2) {
		v.pos.Set(outerR * cos(Math::DegreeToRadian(theta)), (float)-height / 2.0, outerR * sin(Math::DegreeToRadian(theta)));
		v.normal.Set((float)height * cos(Math::DegreeToRadian(theta)), outerR, (float)height * sin(Math::DegreeToRadian(theta)));
		v.normal.Normalize();
		vertex.push_back(v);

		v.pos.Set(innerR * cos(Math::DegreeToRadian(theta)), (float)height / 2.0, innerR * sin(Math::DegreeToRadian(theta)));
		v.normal.Set((float)height * cos(Math::DegreeToRadian(theta)), innerR, (float)height * sin(Math::DegreeToRadian(theta)));
		v.normal.Normalize();
		vertex.push_back(v);
	}

	for (float theta = 0; theta <= 360; theta += 2) {
		v.pos.Set(outerR * cos(Math::DegreeToRadian(theta)), (float)-height / 2.0, outerR * sin(Math::DegreeToRadian(theta)));
		v.normal.Set(0, - 1, 0);
		vertex.push_back(v);

		v.pos.Set(0, (float)-height / 2.0, 0);
		v.normal.Set(0, - 1, 0);
		vertex.push_back(v);
	}

	for (float theta = 0; theta <= 360; theta += 2) {
		v.pos.Set(innerR * cos(Math::DegreeToRadian(theta)), (float)height / 2.0, innerR * sin(Math::DegreeToRadian(theta)));
		v.normal.Set(0, 1, 0);
		//debug: v.color.set(1, 0, 0);
		vertex.push_back(v);

		v.pos.Set(0, (float)height / 2.0, 0);
		v.normal.Set(0, 1, 0);
		vertex.push_back(v);
	}

	for (unsigned int i = 0; i < vertex.size(); i++) {
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	
	return mesh;
}

Mesh* MeshBuilder::GenerateHemiSphere(const std::string& meshName, Color color, unsigned numStacks, unsigned numSlices, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float degreePerStack = 90.f / numStacks;
	float degreePerSlice = 360.f / numSlices;

	unsigned startIndex;
	startIndex = vertex_buffer_data.size();
	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		float theta = slice * degreePerSlice;
		float x = radius * cosf(theta);
		float z = radius * sinf(theta);

		v.pos.Set(x, 0, z);		v.color = (0.93, 0.74, 0.89); v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
		v.pos.Set(0, 0, 0);		v.color = (0.93, 0.74, 0.89); v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	}
	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		index_buffer_data.push_back(startIndex + slice * 2 + 0);
		index_buffer_data.push_back(startIndex + slice * 2 + 1);
	}

	// circular
	startIndex = vertex_buffer_data.size();

	for (unsigned stack = 0; stack < numStacks + 1 ; ++stack)
	{
		float phi = 0.f + stack * degreePerStack;
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			float theta = slice * degreePerSlice;
			float x = cosf(Math::DegreeToRadian(phi)) * cosf(Math::DegreeToRadian(theta));
			float y = sinf(Math::DegreeToRadian(phi));
			float z = cosf(Math::DegreeToRadian(phi)) * sinf(Math::DegreeToRadian(theta));

			v.pos.Set(radius * x, radius * y, radius * z);
			v.color = color;
			v.normal.Set(x, y, z);
			vertex_buffer_data.push_back(v);
		}
	}
	for (unsigned stack = 0; stack < numStacks; ++stack)
	{
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			index_buffer_data.push_back(startIndex + stack * (numSlices + 1) + slice);
			index_buffer_data.push_back(startIndex + (stack + 1) * (numSlices + 1) + slice);
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


Mesh* MeshBuilder::GenerateTorus(const std::string& meshName, Color color, float innerR, float outerR) {
	std::vector<Vertex> vertex;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	v.color = color;


	unsigned int numStacks = 70;
	unsigned int numSlices = 200;
	float degreePerStack = 360.f / numStacks;
	float degreePerSlice = 360.f / numSlices;
	float x1, z1;
	float x2, y2, z2;
	for (unsigned int stack = 0; stack < numStacks + 1; stack++) {
		for (unsigned int slice = 0; slice < numSlices + 1; slice++) {
			z1 = outerR * cos(Math::DegreeToRadian(stack * degreePerStack));
			x1 = outerR * sin(Math::DegreeToRadian(stack * degreePerStack));
			z2 = (outerR + innerR * cos(Math::DegreeToRadian(slice * degreePerSlice))) * cos(Math::DegreeToRadian(stack * degreePerStack));
			y2 = innerR * sin(Math::DegreeToRadian(slice * degreePerSlice));
			x2 = (outerR + innerR * cos(Math::DegreeToRadian(slice * degreePerSlice))) * sin(Math::DegreeToRadian(stack * degreePerStack));
			v.pos.Set(x2, y2, z2);
			v.normal.Set(x2 - x1, y2, z2 - z1);
			v.normal.Normalize();
			vertex.push_back(v);
		}
	}

	for (unsigned int stack = 0; stack < numStacks; stack++) {
		for (unsigned int slice = 0; slice < numSlices + 1; slice++) {
			index_buffer_data.push_back((numSlices + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlices + 1) * (stack + 1) + slice + 0);
		}

	}

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	
	return mesh;
}

Mesh* MeshBuilder::GenerateCylinder(const std::string& meshName, Color color, int height)
{
	std::vector<Vertex> vertex;
	std::vector<GLuint> index_buffer_data;
	Vertex v;
	v.color = color;

	float rad = 1.0;
	int numStack = 10 * height;
	int index = 0;
	float stackHeight = ((float)height) / numStack;

	for (float theta = 0; theta <= 360; theta += 10) {
		float x = rad * cos(Math::DegreeToRadian(theta));
		float z = rad * sin(Math::DegreeToRadian(theta));

		v.pos.Set(0, -height / 2.0, 0);
		v.normal.Set(0, -1, 0);
		vertex.push_back(v);
		index_buffer_data.push_back(index++);

		v.pos.Set(x, -height / 2.0, z);
		v.normal.Set(0, -1, 0);
		vertex.push_back(v);
		index_buffer_data.push_back(index++);
	}

	for (int stack = 0; stack < numStack; ++stack) {
		for (float theta = 0; theta <= 360; theta += 10) {
			float x = rad * cos(Math::DegreeToRadian(theta));
			float z = rad * sin(Math::DegreeToRadian(theta));
			v.pos.Set(x, (float)-height / 2.0 + (float)stack * stackHeight, z);
			v.normal.Set(x, 0, z);
			vertex.push_back(v);
			index_buffer_data.push_back(index++);

			v.pos.Set(x, (float)-height / 2.0 + ((float)stack + 1) * stackHeight, z);
			v.normal.Set(x, 0, z);
			vertex.push_back(v);
			index_buffer_data.push_back(index++);
		}
	}

	for (float theta = 0; theta <= 360; theta += 10) {
		float x = rad * cos(Math::DegreeToRadian(theta));
		float z = rad * sin(Math::DegreeToRadian(theta));

		v.pos.Set(x, (float)height / 2.0, z);
		v.normal.Set(0, 1, 0);
		vertex.push_back(v);
		index_buffer_data.push_back(index++);

		v.pos.Set(0, (float)height / 2.0, 0);
		v.normal.Set(0, 1, 0);
		vertex.push_back(v);
		index_buffer_data.push_back(index++);
	}


	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}



