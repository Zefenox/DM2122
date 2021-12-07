#include "SceneLight.h"
#include "GL\glew.h"

#include "shader.hpp"
#include <Mtx44.h>
#include "Application.h"
#include "../Utility.h"


SceneLight::SceneLight()
{
}

SceneLight::~SceneLight()
{
}

void SceneLight::Init()
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
	m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//Shading.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	glUseProgram(m_programID);

	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	// Make sure you pass uniform parameters after glUseProgram()
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	
	camera.Init(Vector3(20, 20, 20), Vector3(0, 0, 0), Vector3(0, 1, 0));

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Axes",Color(1,1,1),1000, 1000, 1000);

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(0, 1, 1), 1, 1,1);

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("Quad",Color(0,1,1), 1, 1);
	meshList[GEO_QUAD]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Sphere",Color(1,0,1), 30,30, 2);
	meshList[GEO_SPHERE]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_SPHERE]->material.kShininess = 1.f;

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 10, 10, 1);
}

void SceneLight::Update(double dt)
{
	static const float LSPEED = 10.0f;
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

	if (Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('K'))
		light[0].position.z += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		light[0].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('P'))
		light[0].position.y += (float)(LSPEED * dt);

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

void SceneLight::Render()
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

	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	
	/*Mtx44 MVP;*/
	
	/*glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);*/
	//Background
	RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Translate(0, 0, -20);
	modelStack.Scale(30, 30, 30);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(10, 0, 0);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-10, 0, 0);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(10,0 , 10);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(10, 0,-10);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-10, 0, 10);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-10, 0, -10);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 10);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -10);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();


	///*modelStack.PushMatrix();*/
	//modelStack.Translate(-10,0,0);
	//modelStack.Rotate(rotateAngleAnti,0,1,0);
	//modelStack.Scale(2,2,2);
	//RenderMesh(meshList[GEO_SPHERE], true);
	///*modelStack.PopMatrix();*/

	//// lat spin
	//modelStack.PushMatrix();
	//modelStack.Rotate(rotateAngleAnti, 0, 1, 0);
	//modelStack.Translate(6, 0, 0);
	//modelStack.Scale(0.4, 0.4, 0.4);
	//RenderMesh(meshList[GEO_SPHERE], true);
	//modelStack.PopMatrix();

	//// vertical
	//modelStack.PushMatrix();
	//modelStack.Rotate(rotateAngleClock, 0, 1, 0);
	//modelStack.Rotate(rotateAngleClock, 0, 0, 1);
	//modelStack.Translate(3, 3, 0);
	//modelStack.Scale(0.4, 0.4, 0.4);
	//RenderMesh(meshList[GEO_SPHERE], true);
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//modelStack.Translate(-4, 0, 0);
	//modelStack.Rotate(rotateAngleClock, 0, 0, 1);
	//modelStack.Rotate(spinlikecrazy, 0, 1, 0);
	//modelStack.Scale(0.3, 0.3, 0.3);
	//RenderMesh(meshList[GEO_SPHERE], true);
	///*modelStack.PopMatrix();*/
	//
	//modelStack.Translate(-5, 0, 0);
	//modelStack.Rotate(rotateAngleAnti, 0, 0, 1);
	//modelStack.Scale(0.7, 0.7, 0.7);
	//RenderMesh(meshList[GEO_SPHERE], true);

}

void SceneLight::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	mesh->Render();
}

void SceneLight::Exit()
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