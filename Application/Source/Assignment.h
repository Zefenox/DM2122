#ifndef SCENE_Assignment_H
#define SCENE_Assignment_H

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "../Light.h"
#include "Camera2.h"


class Assignment : public Scene
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
		U_NUMLIGHTS,
		U_TOTAL,
	};
	enum GEOMETRY_TYPE
	{
		GEO_QUAD = 0,
		GEO_AXES,
		GEO_CUBE,
		GEO_CIRCLE,
		GEO_SPHERE,
		GEO_LIGHTBALL,
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

	/*enum TAIL
	{
		D_LEFT = 0,
		D_RIGHT,
	};*/
	
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

	/*TAIL taildir;*/

	Camera2 camera;

	MS modelStack, viewStack, projectionStack;

	Light light[8];

	virtual void RenderMesh(Mesh* mesh, bool enableLight);
	

public:

	
	Assignment();
	~Assignment();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	
	virtual void Exit();
};

#endif