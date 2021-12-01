#pragma once
#include "Source/Vertex.h"



struct Light
{
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;
	//to do: add a constructor
	Light() {};
	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};
	LIGHT_TYPE type;
	Vector3 spotDirection;
	float cosCutoff;
	float cosInner;
	float exponent;
};


