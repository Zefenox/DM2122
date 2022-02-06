#include "SceneSkybox.h"
#include "GL\glew.h"

#include "shader.hpp"
#include <Mtx44.h>
#include "Application.h"
#include "../Utility.h"
#include "LoadTGA.h"


SceneSkybox::SceneSkybox()
{
}

SceneSkybox::~SceneSkybox()
{
}

void SceneSkybox::Init()
{
	// Init VBO here
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDisable(GL_CULL_FACE);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);


	left = 180;
	right = 0;

	rotateAngleAnti = 0;
	rotateAngleClock = 0;
	spinlikecrazy = 0;
	translateX = 0;
	scaleAll = 1;

	taildir = SceneSkybox::DIR::D_LEFT;

	rightleg = SceneSkybox::DIR::D_FORWARD;
	leftleg = SceneSkybox::DIR::D_BACKWARD;

	jumpdir = SceneSkybox::DIR::D_UP;

	tailrotate = 0;
	rightlegrotate = 0;
	leftlegrotate = 0;

	jumpoffset = 0;

	timer = 1.0;
	timer1 = 0.2;
	timer3 = 0;

	walk = 0;

	jump = false;
	jumphigh = false;

	CloseToInteractable = false;

	CoinsAlert = false;

	Sitting = false;

	

	coins = 0;

	// Enable depth test

	//load vertex and fragment shaders
	m_programID = LoadShaders("Shader//Texture.vertexshader","Shader//Text.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] =
		glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] =
		glGetUniformLocation(m_programID, "colorTexture");

	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID,"textColor");

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

	light[0].type = Light::LIGHT_SPOT;
	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
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
	
	camera.Init(Vector3(20, 20, 20), Vector3(0, 0, 0), Vector3(0, 1, 0));

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Axes",Color(1,1,1),1000, 1000, 1000);

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(0, 1, 1), 1, 1,1);

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("Quad",Color(0,1,1), 1, 1);
	meshList[GEO_QUAD]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//dirt.tga");

	//sky box
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f,1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//front.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("BACK", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//back.tga");

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("TOP", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//top.tga");

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottm", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom.tga");

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//left.tga");

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right.tga");

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

	meshList[GEO_RIGHTLEGFOOT] = MeshBuilder::GenerateHemiSphere("right leg foot", Color(1, 0.54, 0.9), 20, 20, 1);
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

	/*meshList[GEO_NYP] = MeshBuilder::GenerateQuad("nyp", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_NYP]->textureID = LoadTGA("Image//NYP.tga");*/


	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Sphere",Color(1,0,1), 30,30, 2);
	meshList[GEO_SPHERE]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SPHERE]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_SPHERE]->material.kShininess = 1.f;
	//meshList[GEO_SPHERE]->textureID = LoadTGA("Image//color.tga");

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 10, 10, 1);

	meshList[GEO_MODEL1] = MeshBuilder::GenerateOBJ("model1","OBJ//chair.obj");
	meshList[GEO_MODEL1]->textureID = LoadTGA("Image//chair.tga");

	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT],
		m_parameters[U_MATERIAL_DIFFUSE],
		m_parameters[U_MATERIAL_SPECULAR],
		m_parameters[U_MATERIAL_SHININESS]);

	meshList[GEO_MODEL7] = MeshBuilder::GenerateOBJMTL("model7",
		"OBJ//house_type01.obj", "OBJ//house_type01.mtl");

	meshList[GEO_MODEL8] = MeshBuilder::GenerateOBJMTL("model7",
		"OBJ//cottage_obj.obj", "OBJ//cottage_obj.mtl"); //cottage_diffuse
	meshList[GEO_MODEL8]->textureID = LoadTGA("Image//cottage_diffuse.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_TREE_TALL] = MeshBuilder::GenerateOBJMTL("modeltreetall",
		"OBJ//TreeTall.obj", "OBJ//TreeTall.mtl"); //cottage_diffuse
	//meshList[GEO_TREE_TALL]->textureID = LoadTGA("Image//TreeTall.tga");

	meshList[GEO_WORKBENCH] = MeshBuilder::GenerateOBJMTL("modelworkbench",
		"OBJ//workbench.obj", "OBJ//workbench.mtl");

	meshList[GEO_CHEST] = MeshBuilder::GenerateOBJMTL("modelchest",
		"OBJ//chest.obj", "OBJ//chest.mtl");

	meshList[GEO_BED] = MeshBuilder::GenerateOBJMTL("modelbed",
		"OBJ//bedroll.obj", "OBJ//bedroll.mtl");

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

}

void SceneSkybox::Update(double dt)
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

	/*else if (Application::IsKeyPressed('0'))
	{
		bEnableLight = false;
	}*/

	static bool bstate = false;
	if (!bstate && Application::IsKeyPressed('9'))
	{
		bstate = true;
		bEnableLight = !bEnableLight;
	}
	else if (bstate && !Application::IsKeyPressed('9'))
	{
		bstate = false;
	}

	

	camera.Update(dt);

	CheckColision();



	

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

	// tail animation
	if (timer > 2.0)
	{
		switch (taildir)
		{
		case SceneSkybox::DIR::D_LEFT:
			taildir = SceneSkybox::DIR::D_RIGHT;
			timer = 0;
			break;
		case SceneSkybox::DIR::D_RIGHT:
			taildir = SceneSkybox::DIR::D_LEFT;
			timer = 0;
			break;
		default:
			break;
		}

	}

	if (taildir == SceneSkybox::DIR::D_LEFT)
	{
		tailrotate -= (float)(30 * dt);
	}
	else if (taildir == SceneSkybox::DIR::D_RIGHT)
	{
		tailrotate += (float)(30 * dt);
	}


	//walk animation 
	if (walk == 1)
	{
		timer1 += dt;

		if (timer1 > 0.4)
		{
			if (rightleg == SceneSkybox::DIR::D_FORWARD)
			{
				rightleg = SceneSkybox::DIR::D_BACKWARD;
				timer1 = 0;
			}
			else if (rightleg == SceneSkybox::DIR::D_BACKWARD)
			{
				rightleg = SceneSkybox::DIR::D_FORWARD;
				timer1 = 0;
			}

			if (leftleg == SceneSkybox::DIR::D_FORWARD)
			{
				leftleg = SceneSkybox::DIR::D_BACKWARD;
				timer1 = 0;
			}
			else if (leftleg == SceneSkybox::DIR::D_BACKWARD)
			{
				leftleg = SceneSkybox::DIR::D_FORWARD;
				timer1 = 0;
			}

		}


		if (leftleg == SceneSkybox::DIR::D_FORWARD)
		{
			leftlegrotate -= (float)(150 * dt);
		}
		else if (leftleg == SceneSkybox::DIR::D_BACKWARD)
		{
			leftlegrotate += (float)(150 * dt);
		}

		if (rightleg == SceneSkybox::DIR::D_FORWARD)
		{
			rightlegrotate -= (float)(150 * dt);
		}
		else if (rightleg == SceneSkybox::DIR::D_BACKWARD)
		{
			rightlegrotate += (float)(150 * dt);
		}
	}

	//jump animation 

	if (jump == true)
	{
		timer3 += dt;

		if (timer3 > 0.2)
		{
			switch (jumpdir)
			{
			case SceneSkybox::DIR::D_UP:
				jumpdir = SceneSkybox::DIR::D_DOWN;
				break;
			case SceneSkybox::DIR::D_DOWN:
				jumpdir = SceneSkybox::DIR::D_UP;
				break;
			default:
				break;
			}

			timer3 = 0;
		}

		if (jumpdir == SceneSkybox::DIR::D_UP)
		{
			jumpoffset += (7 * dt);
		}
		else if (jumpdir == SceneSkybox::DIR::D_DOWN)
		{
			jumpoffset -= (7 * dt);
		}

	}

	if (jumphigh == true)
	{
		timer3 += dt;

		if (timer3 > 0.4)
		{
			switch (jumpdir)
			{
			case SceneSkybox::DIR::D_UP:
				jumpdir = SceneSkybox::DIR::D_DOWN;
				break;
			case SceneSkybox::DIR::D_DOWN:
				jumpdir = SceneSkybox::DIR::D_UP;
				break;
			default:
				break;
			}

			timer3 = 0;
		}

		if (jumpdir == SceneSkybox::DIR::D_UP)
		{
			jumpoffset += (7 * dt);
			rightlegrotate += (60 * dt);
			leftlegrotate += (60 * dt);
		}
		else if (jumpdir == SceneSkybox::DIR::D_DOWN)
		{
			jumpoffset -= (7 * dt);
			rightlegrotate -= (60 * dt);
			leftlegrotate -= (60 * dt);
		}

	}

	if (Application::IsKeyPressed('G'))
	{
		//to do: switch light type to POINT and pass the information to shader
		walk = 1;
		jump = true;
	}
	if (Application::IsKeyPressed('B'))
	{
		//to do: switch light type to POINT and pass the information to shader
		jumphigh = true;
	}
	else if (Application::IsKeyPressed('H'))
	{
		//to do: switch light type to POINT and pass the information to shader
		rightleg = SceneSkybox::DIR::D_FORWARD;
		leftleg = SceneSkybox::DIR::D_BACKWARD;
		jumpdir = SceneSkybox::DIR::D_UP;

		rightlegrotate = 0;
		leftlegrotate = 0;

		walk = 0;
		timer1 = 0.2;
		timer3 = 0;
		jumpoffset = 0;
		jump = false;
		jumphigh = false;

	}
	
	
	
}
void SceneSkybox::RenderChoncc()
{
	//body
	modelStack.PushMatrix();
	modelStack.Translate(-5, jumpoffset +4, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(2, 1.7, 1.8);
	RenderMesh(meshList[GEO_BODY], true);

	//body front
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0.5);
	/*modelStack.Rotate(0, 0, 1, 0);*/
	modelStack.Scale(0.92, 0.94, 0.88);
	RenderMesh(meshList[GEO_BODYFRONT], true);
	modelStack.PopMatrix();
	

	//head
	modelStack.PushMatrix();
	modelStack.Translate(0, 2.75, -0.2);
	modelStack.Rotate(-20, 1, 0, 0);
	modelStack.Scale(0.8, 0.7, 0.7);
	RenderMesh(meshList[GEO_HEAD], true);
	/*modelStack.PopMatrix();*/

	//head front
	modelStack.PushMatrix();

	modelStack.Translate(0, -0.1, 0.3);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Scale(0.96, 0.9, 0.85);
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
	modelStack.Translate(0, -0.3, 1.6);
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

	modelStack.PopMatrix(); //back to head

	//right arm
	modelStack.PushMatrix();
	modelStack.Translate(-1.4, 1, 0.3);
	modelStack.Rotate(50, 0, 0, 1);
	modelStack.Rotate(60, 0, 1, 0);
	modelStack.Rotate(20, 1, 0, 0);
	modelStack.Scale(0.45, 0.25, 0.25);
	RenderMesh(meshList[GEO_RIGHTARM], true);

	modelStack.PushMatrix();
	modelStack.Translate(-2, 0, 2);
	modelStack.Rotate(90, 0, 1, 0);
	/*modelStack.Rotate(40, 1, 0, 0);*/
	modelStack.Scale(1.4, 1, 0.7);
	RenderMesh(meshList[GEO_RIGHTARM], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	// left arm
	modelStack.PushMatrix();
	modelStack.Translate(1.4, 1, 0.3);
	modelStack.Rotate(-50, 0, 0, 1);
	modelStack.Rotate(-60, 0, 1, 0);
	modelStack.Rotate(20, 1, 0, 0);
	modelStack.Scale(0.45, 0.25, 0.25);
	RenderMesh(meshList[GEO_LEFTARM], true);


	modelStack.PushMatrix();
	modelStack.Translate(2, 0, 2);
	modelStack.Rotate(-90, 0, 1, 0);
	/*modelStack.Rotate(40, 1, 0, 0);*/
	modelStack.Scale(1.4, 1, 0.7);
	RenderMesh(meshList[GEO_RIGHTARM], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	//tail
	modelStack.PushMatrix();
	modelStack.Translate(0, -1, -1.9);
	modelStack.Rotate(-110, 1, 0, 0);
	modelStack.Scale(0.5, 0.5, 0.5);
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


	//right leg
	modelStack.PushMatrix();
	modelStack.Translate(-1, -1.2, 0.2);
	modelStack.Rotate(rightlegrotate, 1, 0, 0);

	modelStack.Scale(0.6, 1, 0.7);
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
	modelStack.Translate(1, -1.2, 0.2);
	modelStack.Rotate(leftlegrotate, 1, 0, 0);
	modelStack.Scale(0.6, 1, 0.7);
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

	modelStack.PopMatrix(); //back to body
}
void SceneSkybox::Render()
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

	RenderSkybox();

	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Translate(0, 0, -50);
	modelStack.Scale(100, 100, 100);
	
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();

	RenderChoncc();

	//modelStack.PushMatrix();
	////scale, translate, rotate
	//modelStack.Translate(-20, 10, 1);
	//RenderMesh(meshList[GEO_MODEL1], true);
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	////scale, translate, rotate
	//modelStack.Translate(0, 0, 10);
	//modelStack.Scale(2, 2, 2);
	//RenderMesh(meshList[GEO_MODEL7], true);
	//modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(30,0,0);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[GEO_MODEL8], true);
	modelStack.PopMatrix();

	//workbench
	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(-20, 0, 0);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_WORKBENCH], true);
	modelStack.PopMatrix();

	// chest
	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(-20, 0, -20);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_CHEST], true);
	modelStack.PopMatrix();

	//bed
	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(-20, 0, 20);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_BED], true);
	modelStack.PopMatrix();

	//bounding trees

	for (int i = 0; i < 20; i++)
	{
		modelStack.PushMatrix();
		//scale, translate, rotate
		modelStack.Translate(-50+(i*5), 0, -50);
		modelStack.Scale(10, 10, 10);
		RenderMesh(meshList[GEO_TREE_TALL], true);
		modelStack.PopMatrix();
	}

	for (int i = 0; i < 20; i++)
	{
		modelStack.PushMatrix();
		//scale, translate, rotate
		modelStack.Translate(-50 + (i * 5), 0, +50);
		modelStack.Scale(10, 10, 10);
		RenderMesh(meshList[GEO_TREE_TALL], true);
		modelStack.PopMatrix();
	}

	for (int i = 0; i < 20; i++)
	{
		modelStack.PushMatrix();
		//scale, translate, rotate
		modelStack.Translate(-50, 0, -50 + (i * 5));
		modelStack.Scale(10, 10, 10);
		RenderMesh(meshList[GEO_TREE_TALL], true);
		modelStack.PopMatrix();
	}

	for (int i = 0; i < 20; i++)
	{
		modelStack.PushMatrix();
		//scale, translate, rotate
		modelStack.Translate(50, 0, -50 + (i * 5));
		modelStack.Scale(10, 10, 10);
		RenderMesh(meshList[GEO_TREE_TALL], true);
		modelStack.PopMatrix();
	}


	

	/*modelStack.PushMatrix();
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.Translate(0, 0, 0);
	modelStack.Scale(30, 30, 30);
	RenderMesh(meshList[GEO_NYP], true);
	modelStack.PopMatrix();*/

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[1].position.x, light[1].position.y, light[1].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();



	//modelStack.PushMatrix();
	////scale, translate, rotate
	//modelStack.Scale(30, 30, 30);
	//RenderText(meshList[GEO_TEXT], "Hello World", Color(0, 1, 0));
	//modelStack.PopMatrix();

	float debugcordx = camera.position.x;
	float debugcordz = camera.position.z;


	RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(debugcordx), Color(0, 1, 0), 4, 0, 0);
	RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(debugcordz), Color(0, 1, 0), 4, 0, 4);

	//coins
	RenderTextOnScreen(meshList[GEO_TEXT], "Coins:", Color(0, 1, 0), 4, 0, 50);
	RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(coins), Color(0, 1, 0), 4, 13, 50);

	//not enough coins alert
	if (CoinsAlert)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "10 Coins Required", Color(0, 1, 0), 4, 15, 30);
	}
	
	//interactable alert
	if (CloseToInteractable)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to Interact", Color(0, 1, 0), 4, 15, 20);
	}


}

void SceneSkybox::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight && bEnableLight)
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

	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();

	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void SceneSkybox::RenderSkybox()
{
	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.Translate(0, 0, -100);
	modelStack.Scale(200, 200, 0);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Translate(0, 0, -100);
	modelStack.Scale(200, 200, 0);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Translate(0, 0, -100);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(200, 200, 0);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Translate(0, 0, -100);
	modelStack.Scale(200, 200, 0);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Translate(0, 0, -100);
	modelStack.Scale(200, 200, 0);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Translate(0, 0, -100);
	modelStack.Scale(200, 200, 0);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();
}

void SceneSkybox::CheckColision()
{
	static bool bstateinter = false;
	// workbench interactable
	if (camera.position.x > -24 && camera.position.x < -16 && camera.position.z > -4 && camera.position.z < 4)
	{
		CloseToInteractable = true;
		if (!bstateinter && Application::IsKeyPressed('E'))
		{
			bstateinter = true;
			if (coins >= 10)
			{
				coins -= 10;
			}
			else
			{
				CoinsAlert = true;
			}
		}
		else if (bstateinter && !Application::IsKeyPressed('E'))
		{
			bstateinter = false;
		}
	}
	//chest
	else if (camera.position.x > -24 && camera.position.x < -16 && camera.position.z > -24 && camera.position.z < -16)
	{
		CloseToInteractable = true;
		if (!bstateinter && Application::IsKeyPressed('E'))
		{
			bstateinter = true;
			coins += 5;
		}
		else if (bstateinter && !Application::IsKeyPressed('E'))
		{
			bstateinter = false;
		}
		
	}
	//bed
	else if (camera.position.x > -24 && camera.position.x < -16 && camera.position.z > 16 && camera.position.z < 24)
	{
		CloseToInteractable = true;
		if (!bstateinter && Application::IsKeyPressed('E'))
		{
			bstateinter = true;
			camera.position.y = 1.5;
			camera.Resetview();
		}
		else if (bstateinter && !Application::IsKeyPressed('E'))
		{
			bstateinter = false;
		}
	}
	else
	{
		bstateinter = false;
		CloseToInteractable = false;
		CoinsAlert = false;
	}

}

void SceneSkybox::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;
	//glDisable(GL_DEPTH_TEST); //uncomment for RenderTextOnScreen
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
			Mtx44 MVP = projectionStack.Top() * viewStack.Top() *
			modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
			&MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	//glEnable(GL_DEPTH_TEST); //uncomment for RenderTextOnScreen
}

void SceneSkybox::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;
	glDisable(GL_DEPTH_TEST); //uncomment for RenderTextOnScreen
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(0.5f + i * 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() *
			modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
			&MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST); //uncomment for RenderTextOnScreen
	
}

void SceneSkybox::Exit()
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
