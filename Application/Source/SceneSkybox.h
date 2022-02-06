#ifndef SCENESKYBOX_H
#define SCENESKYBOX_H

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "../Light.h"
#include "Camera2.h"
#include "Camera3.h"


class SceneSkybox : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,
		U_NUMLIGHTS, //in case you missed out practical 7
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};
	enum GEOMETRY_TYPE
	{
		GEO_TRIANGLE_1 = 0,
		GEO_TRIANGLE_2,
		GEO_TRIANGLE_3,
		GEO_TRIANGLE_4,
		GEO_TRIANGLE_5,
		GEO_QUAD,
		GEO_AXES,
		GEO_CUBE,
		GEO_CIRCLE,
		GEO_SPHERE,
		GEO_LIGHTBALL,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_BLEND,
		GEO_NYP,
		GEO_MODEL1,
		GEO_MODEL7,
		GEO_MODEL8,
		GEO_TEXT,
		GEO_TREE_TALL,
		GEO_WORKBENCH,
		GEO_CHEST,
		GEO_BED,
		GEO_HEAD,
		GEO_HEADFRONT,
		GEO_HEADHORNS,
		GEO_EYESPHERE,
		GEO_EYECONE,
		GEO_MOUTH,
		GEO_BODY,
		GEO_BODYFRONT,
		GEO_RIGHTARM,
		GEO_LEFTARM,
		GEO_RIGHTLEG,
		GEO_RIGHTLEGFOOT,
		GEO_LEFTLEG,
		GEO_LEFTLEGFOOT,
		GEO_TAIL,
		GEO_TAILBALL,
	    NUM_GEOMETRY,
	};

	enum class DIR
	{
		D_LEFT = 0,
		D_RIGHT = 1,
		D_FORWARD = 2,
		D_BACKWARD = 3,
		D_UP = 4,
		D_DOWN = 5,
	};

	
private:
	unsigned m_vertexArrayID;
	/*unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_indexBuffer[NUM_GEOMETRY];*/
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	float rotateAngleAnti;
	float rotateAngleClock;
	float spinlikecrazy;
	float translateX;
	float scaleAll;
	float tailrotate;

	float left;
	float right;

	float rightlegrotate;
	float leftlegrotate;

	float timer;
	float timer1;
	float timer3;

	int walk;
	bool jump;
	bool jumphigh;
	float jumpoffset;

	DIR taildir;
	DIR rightleg;
	DIR leftleg;

	DIR jumpdir;

	bool bEnableLight;

	Camera3 camera;

	MS modelStack, viewStack, projectionStack;

	Light light[8];

	bool CloseToInteractable;

	bool CoinsAlert;

	bool Sitting;

	int coins;

	

	virtual void RenderMesh(Mesh* mesh, bool enableLight);

	void RenderSkybox();

	void CheckColision();
	
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

public:

	
	SceneSkybox();
	~SceneSkybox();

	virtual void Init();
	virtual void Update(double dt);
	void RenderChoncc();
	virtual void Render();
	
	virtual void Exit();
};

#endif