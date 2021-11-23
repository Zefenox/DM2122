#ifndef SCENE_5_H
#define SCENE_5_H

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"


class Scene5 : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
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
	    NUM_GEOMETRY,
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

	float left;
	float right;

	Camera camera;

	MS modelStack, viewStack, projectionStack;
	

public:

	
	Scene5();
	~Scene5();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};

#endif