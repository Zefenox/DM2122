#include "Scene4.h"
#include "GL\glew.h"

#include "shader.hpp"
#include <Mtx44.h>
#include "Application.h"


Scene4::Scene4()
{
}

Scene4::~Scene4()
{
}

void Scene4::Init()
{
	// Init VBO here
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	left = 180;
	right = 0;

	rotateAngleAnti = 0;
	rotateAngleClock = 0;
	spinlikecrazy = 0;
	translateX = 0;
	scaleAll = 1;

	// Enable depth test

	//load vertex and fragment shaders
	m_programID = LoadShaders(
		"Shader//TransformVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	glUseProgram(m_programID);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	
	camera.Init(Vector3(5, 4, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Axes",Color(1,1,1),1000, 1000, 1000);

	//meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", 1, 1,1);

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("Quad",Color(1,0,1), 1, 1);

	

	//Get a handle for our "MVP" uniform
	

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
	//	m_indexBuffer[GEO_TRIANGLE_1]); //bind index array
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	//	sizeof(index_buffer_data), index_buffer_data, GL_STATIC_DRAW);

	//generate buffers
	/*glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_indexBuffer[0]);*/



	// AN array of 3 vectors which represents 3 vertices
	//static const GLfloat vertex_buffer_data[] = {
	//	-0.5f,0.5f,0.0f,//triangle 1
	//	-0.5f,-0.5f,0.0f,
	//	0.5f, 0.5f, 0.0f,//tri 2
	//	0.5f,-0.5f,0.0f,
	//	
	//	
	//	 // tri3
	//	 
	//};
	////colors
	//static const GLfloat color_buffer_data[] = {
	//	0.0f,1.0f,0.5f,
	//	1.0f,0.0f,0.5f,
	//	1.0f,0.5f,0.0f,
	//};

	//set the current active buffer
	/*glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);*/
	
	//transfer vertices to open GL
	/*glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);*/


}

void Scene4::Update(double dt)
{
	if (Application::IsKeyPressed('1'))
	{
		glEnable(GL_CULL_FACE);
	}

	if (Application::IsKeyPressed('2'))
	{
		glDisable(GL_CULL_FACE);
	}

	if (Application::IsKeyPressed('3'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //fill mode
	}

	if (Application::IsKeyPressed('4'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	}

	camera.Update(dt);

	rotateAngleAnti += (float)(40 * dt);
	rotateAngleClock -= (float)(50 * dt);
	spinlikecrazy += (float)(500 * dt);
	translateX += (float)(10 * dt);
	if (scaleAll >2)
	{
		scaleAll -= (float)(20 * dt);
	}
	else
	{
		scaleAll = 100;
	}
	
}

void Scene4::Render()
{
	//Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	//glEnableVertexAttribArray(1);

	Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 MVP;

	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	view.SetToIdentity();

	

	view.SetToLookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);

	projection.SetToPerspective(40.0f, 4.0 / 3.0f, 0.1f, 1000.0f); // FOV Aspect ratio Near plane Far PLANE
	
	/*glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);*/
	//Background
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_AXES]->Render();


	scale.SetToScale(3, 3, 3);
	rotate.SetToRotation(rotateAngleAnti, 0, 0, 1);
	translate.SetToTranslation(0, 0, 0);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_QUAD]->Render();
	

}

void Scene4::Exit()
{
	// Cleanup VBO here
	/*glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);*/
	delete meshList[GEO_QUAD];
	delete meshList[GEO_AXES];
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
