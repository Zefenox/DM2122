#include "Assignment.h"
#include "GL\glew.h"

#include "shader.hpp"
#include <Mtx44.h>
#include "Application.h"
#include "../Utility.h"


Assignment::Assignment()
{
}

Assignment::~Assignment()
{
}

void Assignment::Init()
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

	taildir = Assignment::TAIL::D_LEFT;

	tailrotate = 0;

	timer = 1.0;

	// Enable depth test

	//load vertex and fragment shaders
	m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//LightSource.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");
	
	glUseProgram(m_programID);

	light[0].type = Light::LIGHT_POINT;
	light[0].position.Set(0, 5, 9);
	light[0].color.Set(1, 1, 1);
	light[0].power = 0.9f;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 1.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	light[1].type = Light::LIGHT_DIRECTIONAL;
	light[1].position.Set(0, 20, 0);
	light[1].color.Set(1, 1, 1);
	light[1].power = 1;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);
	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_NUMLIGHTS], 8);


	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);


	// carmera
	camera.Init(Vector3(20, 20, 20), Vector3(0, 0, 0), Vector3(0, 1, 0));

	// axes
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Axes",Color(1,1,1),1000, 1000, 1000);

	// scene
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(0, 1, 1), 1, 1,1);

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("Quad",Color(0.29,0.77,0.26), 1, 1);
	meshList[GEO_QUAD]->material.kAmbient.Set(0.0f, 0.0f, 0.0f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Sphere",Color(1,0,1), 30,30, 2);
	meshList[GEO_SPHERE]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_SPHERE]->material.kShininess = 1.f;

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("HafizBall", Color(1, 1, 1), 10, 10, 1);


	//head
	meshList[GEO_HEAD] = MeshBuilder::GenerateSphere("Head", Color(1, 0.54, 0.9), 30, 30, 2);
	meshList[GEO_HEAD]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HEAD]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_HEAD]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_HEAD]->material.kShininess = 1.f;

	//head front
	meshList[GEO_HEADFRONT] = MeshBuilder::GenerateHemiSphere("Headfront", Color(0.93, 0.74, 0.89), 30, 30, 2);
	meshList[GEO_HEADFRONT]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HEADFRONT]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_HEADFRONT]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_HEADFRONT]->material.kShininess = 1.f;

	//body
	meshList[GEO_BODY] = MeshBuilder::GenerateSphere("Body", Color(1, 0.54, 0.9), 30, 30, 2);
	meshList[GEO_BODY]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BODY]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BODY]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BODY]->material.kShininess = 1.f;

	//body front
	meshList[GEO_BODYFRONT] = MeshBuilder::GenerateSphere("Bodyfront", Color(0.93, 0.74, 0.89), 30, 30, 2);
	meshList[GEO_BODYFRONT]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BODYFRONT]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BODYFRONT]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BODYFRONT]->material.kShininess = 1.f;

	//eyes
	meshList[GEO_EYESPHERE] = MeshBuilder::GenerateSphere("eyesphere", Color(0, 0, 0), 30, 30, 2);
	meshList[GEO_EYESPHERE]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_EYESPHERE]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_EYESPHERE]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_EYESPHERE]->material.kShininess = 1.f;

	// mouth
	meshList[GEO_MOUTH] = MeshBuilder::GenerateHemiSphere("mouthhemisphere", Color(0, 0, 0), 30, 30, 2);
	meshList[GEO_MOUTH]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_MOUTH]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_MOUTH]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_MOUTH]->material.kShininess = 1.f;

	//HEAD HORNS
	meshList[GEO_HEADHORNS] = MeshBuilder::GenerateHemiSphere("Head horns", Color(1, 0.54, 0.9), 30, 30, 2);
	meshList[GEO_HEADHORNS]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HEADHORNS]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_HEADHORNS]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_HEADHORNS]->material.kShininess = 1.f;


	//right arm
	meshList[GEO_RIGHTARM] = MeshBuilder::GenerateHemiSphere("Right Arm", Color(1, 0.54, 0.9), 30, 30, 2);
	meshList[GEO_RIGHTARM]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_RIGHTARM]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_RIGHTARM]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_RIGHTARM]->material.kShininess = 1.f;

	//left arm
	meshList[GEO_LEFTARM] = MeshBuilder::GenerateHemiSphere("Left Arm", Color(1, 0.54, 0.9), 30, 30, 2);
	meshList[GEO_LEFTARM]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_LEFTARM]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_LEFTARM]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_LEFTARM]->material.kShininess = 1.f;

	//tail
	meshList[GEO_TAIL] = MeshBuilder::GenerateConicalFrustum("tail", Color(1, 0.54, 0.9), 0.8, 1.0, 1.5);
	meshList[GEO_TAIL]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_TAIL]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_TAIL]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_TAIL]->material.kShininess = 1.f;

	//tail ball
	meshList[GEO_TAILBALL] = MeshBuilder::GenerateSphere("tailball", Color(1, 0.54, 0.9), 30, 30, 2);
	meshList[GEO_TAILBALL]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_TAILBALL]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_TAILBALL]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_TAILBALL]->material.kShininess = 1.f;

	//right leg
	meshList[GEO_RIGHTLEG] = MeshBuilder::GenerateCylinder("right leg", Color(1.0, 0.54, 0.9), 2.6);
	meshList[GEO_RIGHTLEG]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_RIGHTLEG]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_RIGHTLEG]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_RIGHTLEG]->material.kShininess = 1.f;

	meshList[GEO_RIGHTLEGFOOT] = MeshBuilder::GenerateHemiSphere("right leg foot", Color(1, 0.54, 0.9), 20, 20 ,1);
	meshList[GEO_RIGHTLEGFOOT]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_RIGHTLEGFOOT]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_RIGHTLEGFOOT]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_RIGHTLEGFOOT]->material.kShininess = 1.f;

	//Left leg

	meshList[GEO_LEFTLEG] = MeshBuilder::GenerateCylinder("left leg", Color(1.0, 0.54, 0.9), 2.6);
	meshList[GEO_LEFTLEG]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_LEFTLEG]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_LEFTLEG]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_LEFTLEG]->material.kShininess = 1.f;

	meshList[GEO_LEFTLEGFOOT] = MeshBuilder::GenerateHemiSphere("left leg foot", Color(1, 0.54, 0.9), 20, 20, 1);
	meshList[GEO_LEFTLEGFOOT]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_LEFTLEGFOOT]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_LEFTLEGFOOT]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_LEFTLEGFOOT]->material.kShininess = 1.f;


}

void Assignment::Update(double dt)
{
	static const float LSPEED = 20.0f;
	timer += dt;

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



	if (Application::IsKeyPressed('5'))
	{
		//to do: switch light type to POINT and pass the information to shader
		m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
		glUseProgram(m_programID);
		light[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
		
	}
	else if (Application::IsKeyPressed('6'))
	{
		//to do: switch light type to DIRECTIONAL and pass the information to shader
		m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
		glUseProgram(m_programID);
		light[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	else if (Application::IsKeyPressed('7'))
	{
		//to do: switch light type to SPOT and pass the information to shader
		m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
		glUseProgram(m_programID);
		light[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}

	if (Application::IsKeyPressed('G'))
	{
		//to do: switch light type to POINT and pass the information to shader
		tailrotate -= 1;
	}
	else if (Application::IsKeyPressed('H'))
	{
		//to do: switch light type to POINT and pass the information to shader
		tailrotate += 1;
	}


	camera.Update(dt);

	rotateAngleAnti += (float)(40 * dt);
	rotateAngleClock -= (float)(50 * dt);
	spinlikecrazy += (float)(200 * dt);
	translateX += (float)(10 * dt);

	if (timer > 2.0)
	{
		switch (taildir)
		{
		case Assignment::TAIL::D_LEFT:
			taildir = Assignment::TAIL::D_RIGHT;
			timer = 0;
			break;
		case Assignment::TAIL::D_RIGHT:
			taildir = Assignment::TAIL::D_LEFT;
			timer = 0;
			break;
		default:
			break;
		}
		
	}

	if (taildir == Assignment::TAIL::D_LEFT)
	{
		tailrotate -= (float)(30 * dt);
	}
	else if (taildir == Assignment::TAIL::D_RIGHT)
	{
		tailrotate += (float)(30 * dt);
	}
	

	if (scaleAll >2)
	{
		scaleAll -= (float)(20 * dt);
	}
	else
	{
		scaleAll = 100;
	}


}

void Assignment::Render()
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


	Vector3 lightDir(light[1].position.x, light[1].position.y, light[1].position.z);
	Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
	glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);

	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}
	//Background
	RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	/*modelStack.PushMatrix();
	modelStack.Translate(light[1].position.x, light[1].position.y, light[1].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();*/

	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Translate(0, 0, -23);
	modelStack.Scale(30, 30, 30);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();

	//head
	modelStack.PushMatrix();
	modelStack.Translate(0, 3.3,-0.2);
	modelStack.Rotate(-20, 1, 0, 0);
	modelStack.Scale(1.3, 1, 1);
	RenderMesh(meshList[GEO_HEAD], true);
	/*modelStack.PopMatrix();*/

	//head front
	modelStack.PushMatrix();
	modelStack.Translate(0,-0.1, 0.3);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Scale(0.95, 0.9, 0.9);
	RenderMesh(meshList[GEO_HEADFRONT], true);
	modelStack.PopMatrix();
	

	// right eye
	modelStack.PushMatrix();
	modelStack.Translate(-0.6, 0.3, 1.76);
	modelStack.Rotate(-10, 0, 0, 1);
	modelStack.Rotate(-10, 0, 1, 0);
	modelStack.Scale(0.2, 0.1, 0.1);
	RenderMesh(meshList[GEO_EYESPHERE], true);
	modelStack.PopMatrix();

	// left eye
	modelStack.PushMatrix();
	modelStack.Translate(0.6, 0.3, 1.76);
	modelStack.Rotate(10, 0, 0, 1);
	modelStack.Rotate(10, 0, 1, 0);
	modelStack.Scale(0.2, 0.1, 0.1);
	RenderMesh(meshList[GEO_EYESPHERE], true);
	modelStack.PopMatrix();

	// mouth
	modelStack.PushMatrix();
	modelStack.Translate(0,-0.3, 1.7);
	modelStack.Rotate(180, 1, 0, 0);
	/*modelStack.Rotate(10, 0, 1, 0);*/
	modelStack.Scale(0.5f, 0.45f, 0.2f);
	RenderMesh(meshList[GEO_MOUTH], true);
	modelStack.PopMatrix();

	//horns
	// right horn
	modelStack.PushMatrix();
	modelStack.Translate(-0.8f, 1.4f, 0.3f);
	modelStack.Rotate(5, 0, 0, 1);
	modelStack.Rotate(-10, 1, 0, 0);
	/*modelStack.Rotate(10, 0, 1, 0);*/
	modelStack.Scale(0.25f, 0.9f, 0.3f);
	RenderMesh(meshList[GEO_HEADHORNS], true);
	modelStack.PopMatrix();

	//left horn
	modelStack.PushMatrix();
	modelStack.Translate(0.8, 1.4, 0.3);
	modelStack.Rotate(-5, 0, 0, 1);
	modelStack.Rotate(-10, 1, 0, 0);
	/*modelStack.Rotate(10, 0, 1, 0);*/
	modelStack.Scale(0.25f, 0.9f, 0.3f);
	RenderMesh(meshList[GEO_HEADHORNS], true);
	modelStack.PopMatrix();

	//right face scales
	modelStack.PushMatrix();
	modelStack.Translate(-1.6, 0, 0.3);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Rotate(-40, 1, 0, 0);
	/*modelStack.Rotate(-10, 1, 0, 0);*/
	/*modelStack.Rotate(10, 0, 1, 0);*/
	modelStack.Scale(0.3f, 0.6f, 0.2f);
	RenderMesh(meshList[GEO_HEADHORNS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1.6, -0.7, 0);
	modelStack.Rotate(130, 0, 0, 1);
	modelStack.Rotate(-20, 1, 0, 0);
	/*modelStack.Rotate(-10, 1, 0, 0);*/
	/*modelStack.Rotate(10, 0, 1, 0);*/
	modelStack.Scale(0.2, 0.4, 0.15);
	RenderMesh(meshList[GEO_HEADHORNS], true);
	modelStack.PopMatrix();

	//left face scales
	modelStack.PushMatrix();
	modelStack.Translate(1.6, 0, 0.3);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Rotate(-40, 1, 0, 0);
	/*modelStack.Rotate(-10, 1, 0, 0);*/
	/*modelStack.Rotate(10, 0, 1, 0);*/
	modelStack.Scale(0.3, 0.6, 0.2);
	RenderMesh(meshList[GEO_HEADHORNS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(1.6, -0.7, 0);
	modelStack.Rotate(-130, 0, 0, 1);
	modelStack.Rotate(-20, 1, 0, 0);
	/*modelStack.Rotate(-10, 1, 0, 0);*/
	/*modelStack.Rotate(10, 0, 1, 0);*/
	modelStack.Scale(0.2, 0.4, 0.15);
	RenderMesh(meshList[GEO_HEADHORNS], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	//body
	modelStack.PushMatrix();
	modelStack.Translate(0, -1, 0);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(2, 1.7, 1.8);
	RenderMesh(meshList[GEO_BODY], true);
	modelStack.PopMatrix();
	//body front
	modelStack.PushMatrix();
	modelStack.Translate(0, -1, 0.7);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(1.85, 1.6, 1.6);
	RenderMesh(meshList[GEO_BODYFRONT], true);
	modelStack.PopMatrix();

	//tail
	modelStack.PushMatrix();
	modelStack.Translate(0, -3, -3);
	modelStack.Rotate(-110, 1, 0, 0);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[GEO_TAIL], true);
	/*modelStack.PopMatrix();*/

	for (int i = 0; i < 9; i++)
	{
		modelStack.PushMatrix();
		modelStack.Rotate(6, 1, 0, 0);
		modelStack.Rotate(tailrotate, 0, 1, 0);
		modelStack.Translate(0, 0.7, 0);
		modelStack.Scale(0.9, 0.9, 0.9);
		RenderMesh(meshList[GEO_TAIL], true);

	}

	//tail ball
	modelStack.PushMatrix();
	modelStack.Translate(0, 3, 0);
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.Scale(1.3, 1.3, 1.3);
	RenderMesh(meshList[GEO_TAILBALL], true);

	modelStack.PopMatrix();


	for (int i = 0; i < 9; i++)
	{
		modelStack.PopMatrix();
	}

	modelStack.PopMatrix();

	//right arm
	modelStack.PushMatrix();
	modelStack.Translate(-2.9, 0.7, 0.5);
	modelStack.Rotate(50, 0, 0, 1);
	modelStack.Rotate(60, 0, 1, 0);
	modelStack.Rotate(20, 1, 0, 0);
	modelStack.Scale(0.8,0.5 , 0.5);
	RenderMesh(meshList[GEO_RIGHTARM], true);
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
	modelStack.Translate(-2.7,0.2, 2.5);
	modelStack.Rotate(70, 0, 0, 1);
	modelStack.Rotate(40, 0, 1, 0);
	modelStack.Rotate(40, 1, 0, 0);
	modelStack.Scale(0.6, 0.6, 0.7);
	RenderMesh(meshList[GEO_RIGHTARM], true);
	modelStack.PopMatrix();

	// left arm
	modelStack.PushMatrix();
	modelStack.Translate(2.9, 0.7, 0.5);
	modelStack.Rotate(-50, 0, 0, 1);
	modelStack.Rotate(-60, 0, 1, 0);
	modelStack.Rotate(20, 1, 0, 0);
	modelStack.Scale(0.8, 0.5, 0.5);
	RenderMesh(meshList[GEO_LEFTARM], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(2.7, 0.2, 2.5);
	modelStack.Rotate(-70, 0, 0, 1);
	modelStack.Rotate(-40, 0, 1, 0);
	modelStack.Rotate(40, 1, 0, 0);
	modelStack.Scale(0.6, 0.6, 0.7);
	RenderMesh(meshList[GEO_LEFTARM], true);
	modelStack.PopMatrix();

	//right leg
	modelStack.PushMatrix();
	modelStack.Translate(-2.5, -3, 0.2);
	/*modelStack.Rotate(50, 0, 0, 1);
	modelStack.Rotate(60, 0, 1, 0);
	modelStack.Rotate(20, 1, 0, 0);*/
	modelStack.Scale(1.2, 1.4, 1.2);
	RenderMesh(meshList[GEO_RIGHTLEG], true);
	

	//right foot
	modelStack.PushMatrix();
	modelStack.Translate(0, -1.2, 0.2);
	/*modelStack.Rotate(50, 0, 0, 1);
	modelStack.Rotate(60, 0, 1, 0);
	modelStack.Rotate(20, 1, 0, 0);*/
	modelStack.Scale(1.2, 0.8, 1.3);
	RenderMesh(meshList[GEO_RIGHTLEGFOOT], true);
	modelStack.PopMatrix();
	
	modelStack.PopMatrix();

	//left leg
	modelStack.PushMatrix();
	modelStack.Translate(2.5, -3, 0.1);
	/*modelStack.Rotate(50, 0, 0, 1);
	modelStack.Rotate(60, 0, 1, 0);
	modelStack.Rotate(20, 1, 0, 0);*/
	modelStack.Scale(1.1, 1.4, 1.2);
	RenderMesh(meshList[GEO_LEFTLEG], true);
	

	modelStack.PushMatrix();
	modelStack.Translate(0, -1.2, 0.2);
	/*modelStack.Rotate(50, 0, 0, 1);
	modelStack.Rotate(60, 0, 1, 0);
	modelStack.Rotate(20, 1, 0, 0);*/
	modelStack.Scale(1.2, 0.8, 1.3);
	RenderMesh(meshList[GEO_LEFTLEGFOOT], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	

}

void Assignment::RenderMesh(Mesh* mesh, bool enableLight)
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

void Assignment::Exit()
{
	// Cleanup VBO here
	/*glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);*/
	delete meshList[GEO_QUAD];
	delete meshList[GEO_AXES];
	delete meshList[GEO_SPHERE];
	delete meshList[GEO_CUBE];
	delete meshList[GEO_CIRCLE];
	delete meshList[GEO_LIGHTBALL];
	delete meshList[GEO_HEAD];
	delete meshList[GEO_HEADFRONT];
	delete meshList[GEO_HEADHORNS];
	delete meshList[GEO_MOUTH];
	delete meshList[GEO_BODY];
	delete meshList[GEO_RIGHTARM];
	delete meshList[GEO_LEFTARM];
	delete meshList[GEO_RIGHTLEG];
	delete meshList[GEO_LEFTLEG];
	delete meshList[GEO_TAIL];
	delete meshList[GEO_TAILBALL];
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
