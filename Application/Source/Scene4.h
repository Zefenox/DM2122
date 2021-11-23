#ifndef SCENE_4_H
#define SCENE_4_H

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "MeshBuilder.h"



class Scene4 : public Scene
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

public:

	
	Scene4();
	~Scene4();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};

#endif