#include "Scene5.h"
#include "GL\glew.h"

#include "shader.hpp"
#include <Mtx44.h>
#include "Application.h"


Scene5::Scene5()
{
}

Scene5::~Scene5()
{
}

void Scene5::Init()
{
	// Init VBO here
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

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

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", 1, 1,1);

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("Quad",Color(1,0,1), 1, 1);

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Sphere",Color(1,0,1), 30,30, 2);

}

void Scene5::Update(double dt)
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
	spinlikecrazy += (float)(200 * dt);
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

void Scene5::Render()
{
	//Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	//glEnableVertexAttribArray(1);

	
	

	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();
	
	Mtx44 MVP;
	
	/*glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);*/
	//Background
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_AXES]->Render();


	/*modelStack.PushMatrix();*/
	modelStack.Translate(-10,0,0);
	modelStack.Rotate(rotateAngleAnti,0,1,0);
	modelStack.Scale(2,2,2);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_SPHERE]->Render();
	/*modelStack.PopMatrix();*/

	// lat spin
	modelStack.PushMatrix();
	modelStack.Rotate(rotateAngleAnti, 0, 1, 0);
	modelStack.Translate(6, 0, 0);
	modelStack.Scale(0.4, 0.4, 0.4);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_SPHERE]->Render();
	modelStack.PopMatrix();

	// vertical
	modelStack.PushMatrix();
	modelStack.Rotate(rotateAngleClock, 0, 1, 0);
	modelStack.Rotate(rotateAngleClock, 0, 0, 1);
	modelStack.Translate(3, 3, 0);
	modelStack.Scale(0.4, 0.4, 0.4);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_SPHERE]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-4, 0, 0);
	modelStack.Rotate(rotateAngleClock, 0, 0, 1);
	modelStack.Rotate(spinlikecrazy, 0, 1, 0);
	modelStack.Scale(0.3, 0.3, 0.3);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_SPHERE]->Render();
	/*modelStack.PopMatrix();*/
	
	modelStack.Translate(-5, 0, 0);
	modelStack.Rotate(rotateAngleAnti, 0, 0, 1);
	modelStack.Scale(0.7, 0.7, 0.7);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	meshList[GEO_SPHERE]->Render();

}

void Scene5::Exit()
{
	// Cleanup VBO here
	/*glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);*/
	delete meshList[GEO_QUAD];
	delete meshList[GEO_AXES];
	delete meshList[GEO_SPHERE];
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
