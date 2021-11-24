#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName,Color color, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName,Color color, float lengthX, float lengthY);
	static Mesh* GenerateCube(const std::string &meshName,Color color, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateCircle(const std::string& meshName, Color color, unsigned numSlices, float radius);
	static Mesh* GenerateSphere(const std::string& meshName, Color color, unsigned numStacks, unsigned numSlices, float radius);
};

#endif