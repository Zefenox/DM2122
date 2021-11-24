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
};