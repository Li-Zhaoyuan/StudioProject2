/****************************************************************************/
/*!
\file LoadingScreen.h
\author Li Zhaoyuan
\par email: lizhaoyuan123@hotmail.com
\brief
class for the scene while Loading
*/
/****************************************************************************/
#ifndef LOADINGSCREEN_H_
#define LOADINGSCREEN_H_

#include "Scene.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"
#include "Camera3.h"
#include "MatrixStack.h"
/******************************************************************************/
/*!
Class LoadingScreen:
\brief	Defines the Loading screens and its methods
*/
/******************************************************************************/
class LoadingScreen : public Scene
{

	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE,
		GEO_TEXT,
		GEO_LEGLEFT,
		GEO_LEGRIGHT,
		GEO_ARMLEFT,
		GEO_ARMRIGHT,
		GEO_BODY,
		NUM_GEOMETRY,
	};

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
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

public:
	LoadingScreen();
	~LoadingScreen();

	void skybox();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	bool enableLight = false;
	float LSPEED = 10.f;
	double fps = 0;

	void renderMesh(Mesh *mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderLoadingBarOnScreen();
	void RenderCharacter();

	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];


	Camera3 camera;

	float boxX = 0;
	float boxZ = 0;
	float camPosX = 0;
	float camPosY = 0;
	float camPosz = 0;
	float loadingbar = 0;
	float rotateLimbs = 0;
	MS modelStack, viewStack, projectionStack;
};

#endif