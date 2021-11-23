#include "Scene2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include <Mtx44.h>


Scene2::Scene2()
{
}

Scene2::~Scene2()
{
}

void Scene2::Init()
{
	// Init VBO here
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	left = 180;
	right = 0;

	rotateAngleAnti = 0;
	rotateAngleClock = 0;
	spinlikecrazy = 0;
	translateX = 0;
	scaleAll = 1;

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	//load vertex and fragment shaders
	m_programID = LoadShaders(
		"Shader//TransformVertexShader.vertexshader",
		"Shader//SimpleFragmentShader.fragmentshader");
	glUseProgram(m_programID);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	

	//generate buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);


	// AN array of 3 vectors which represents 3 vertices
	static const GLfloat vertex_buffer_data[] = {
		0.0f,1.0f,0.0f,//triangle 1
		-0.5f,-1.0f,0.0f,
		0.0f, 0.0f, 0.0f,//tri 2
		 // tri3
		 
	};

	//set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	
	//transfer vertices to open GL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

	//colors
	static const GLfloat color_buffer_data[] = {
		0.0f,1.0f,0.5f,
		1.0f,0.0f,0.5f,
		1.0f,0.5f,0.0f,
	};



	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

	//tri 2
	

	// AN array of 3 vectors which represents 3 vertices
	static const GLfloat vertex_buffer_data_2[] = {
		0.0f,1.0f,-0.1f,//triangle 1
		0.0f,0.0f,-0.1f, //tri 2
		0.5f,-1.0f,-0.1f, // tri3

	};

	//set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	
	//transfer vertices to open GL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_2), vertex_buffer_data_2, GL_STATIC_DRAW);

	//colors
	static const GLfloat color_buffer_data_2[] = {
		0.5f,1.0f,0.5f,
		1.0f,0.5f,0.5f,
		1.0f,0.5f,0.5f,
	};



	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_2), color_buffer_data_2, GL_STATIC_DRAW);

	//tri 3

	// AN array of 3 vectors which represents 3 vertices
	static const GLfloat vertex_buffer_data_3[] = {
		-1.0f,1.0f,0.1f,//triangle 1
		0.0f,0.0f,0.1f, //tri 2
		-1.0f,-0.7f,0.1f, // tri3

	};

	//set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);

	//transfer vertices to open GL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_3), vertex_buffer_data_3, GL_STATIC_DRAW);

	//colors
	static const GLfloat color_buffer_data_3[] = {
		0.7f,0.3f,0.5f,
		0.2f,0.5f,0.9f,
		1.0f,0.3f,0.7f,
	};



	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_3), color_buffer_data_3, GL_STATIC_DRAW);

	// tri 4

	// AN array of 3 vectors which represents 3 vertices
	static const GLfloat vertex_buffer_data_4[] = {
		1.0f,1.0f,0.1f,//triangle 1
		0.0f,0.0f,0.1f, //tri 2
		1.0f,-0.7f,0.1f, // tri3

	};

	//set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_4]);

	//transfer vertices to open GL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_4), vertex_buffer_data_4, GL_STATIC_DRAW);

	//colors
	static const GLfloat color_buffer_data_4[] = {
		0.5f,1.0f,0.2f,
		1.0f,0.5f,0.2f,
		0.7f,1.0f,0.2f,
	};



	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_4), color_buffer_data_4, GL_STATIC_DRAW);

	//tri 5

	// AN array of 3 vectors which represents 3 vertices
	static const GLfloat vertex_buffer_data_5[] = {
		-0.3f,0.0f,0.5f,//triangle 1
		0.0f,-0.7f,0.5f, //tri 2
		0.3f,0.0f,0.5f, // tri3

	};

	//set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_5]);

	//transfer vertices to open GL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_5), vertex_buffer_data_5, GL_STATIC_DRAW);

	//colors
	static const GLfloat color_buffer_data_5[] = {
		0.5f,0.1f,0.5f,
		0.6f,0.5f,0.5f,
		1.0f,1.0f,0.5f,
	};



	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_5), color_buffer_data_5, GL_STATIC_DRAW);
}

void Scene2::Update(double dt)
{

	rotateAngleAnti += (float)(50 * dt);
	rotateAngleClock -= (float)(50 * dt);
	spinlikecrazy += (float)(500 * dt);
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

void Scene2::Render()
{
	//Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnableVertexAttribArray(0); // 1st attribute buffer : vertices
	glEnableVertexAttribArray(1);

	Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 MVP;

	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	view.SetToIdentity();

	projection.SetToOrtho(-40, +40, -30, +30, -10, +10);

	scale.SetToScale(scaleAll, scaleAll, scaleAll);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(1, 1, 1);
	model = translate * rotate * scale;
	MVP = projection * view * model;
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	


	scale.SetToScale(scaleAll, scaleAll, scaleAll);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(1, 1, 1);
	model = translate * rotate * scale;

	MVP = projection * view * model;

	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);


	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	scale.SetToScale(20, 20, 1);
	rotate.SetToRotation(rotateAngleClock, 0, 0, 1);
	translate.SetToTranslation(1, 1, 1);
	model = translate * rotate * scale;

	MVP = projection * view * model;

	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	scale.SetToScale(20, 20, 1);
	rotate.SetToRotation(rotateAngleAnti, 0, 0, 1);
	translate.SetToTranslation(1, 1, 1);
	model = translate * rotate * scale;

	MVP = projection * view * model;

	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_4]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_4]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	scale.SetToScale(20, 20, 1);
	rotate.SetToRotation(spinlikecrazy, 0, 0, 1);
	translate.SetToTranslation(1, 1, 1);
	model = translate * rotate * scale;

	MVP = projection * view * model;

	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[GEO_TRIANGLE_5]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[GEO_TRIANGLE_5]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	


	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

void Scene2::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
