/****************************************************************************/
/*!
\file LoadingScreen.cpp
\author Li Zhaoyuan
\par email: lizhaoyuan123@hotmail.com
\brief
class for the scene while Loading
*/
/****************************************************************************/
#include <sstream>

#include "LoadingScreen.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "Light.h"
#include "Material.h"
#include "Utility.h"
#include "ReadTextFile.h"
#include "LoadTGA.h"
/******************************************************************************/
/*!
\brief	LoadingScreen constructor
*/
/******************************************************************************/
LoadingScreen::LoadingScreen()
{
}
/******************************************************************************/
/*!
\brief	LoadingScreen destructor
*/
/******************************************************************************/
LoadingScreen::~LoadingScreen()
{
}
/******************************************************************************/
/*!
\brief	LoadingScreen main initializer function
*/
/******************************************************************************/
void LoadingScreen::Init()
{

	//// Init VBO here

	//// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Load vertex and fragment shaders
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");


	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");


	glUseProgram(m_programID);


	//Initialize camera settings
	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));


	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("reference", Color(1, 1, 1));

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(0, 0, 0));
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//Pikachu2.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//TimesNewRoman.tga");
	meshList[GEO_BODY] = MeshBuilder::GenerateOBJ("body", "OBJ//HeadBody.obj");
	meshList[GEO_BODY]->textureID = LoadTGA("Image//HumanCharacter.tga");

	meshList[GEO_ARMLEFT] = MeshBuilder::GenerateOBJ("leftarm", "OBJ//LeftArm.obj");
	meshList[GEO_ARMLEFT]->textureID = LoadTGA("Image//HumanCharacter.tga");

	meshList[GEO_ARMRIGHT] = MeshBuilder::GenerateOBJ("rightarm", "OBJ//RightArm.obj");
	meshList[GEO_ARMRIGHT]->textureID = LoadTGA("Image//HumanCharacter.tga");

	meshList[GEO_LEGLEFT] = MeshBuilder::GenerateOBJ("leftleg", "OBJ//LeftLeg.obj");
	meshList[GEO_LEGLEFT]->textureID = LoadTGA("Image//HumanCharacter.tga");

	meshList[GEO_LEGRIGHT] = MeshBuilder::GenerateOBJ("rightleg", "OBJ//RightLeg.obj");
	meshList[GEO_LEGRIGHT]->textureID = LoadTGA("Image//HumanCharacter.tga");

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 10000.f);
	projectionStack.LoadMatrix(projection);

}
/******************************************************************************/
/*!
\brief	LoadingScreen main Update function

\param	dt
	delta time
*/
/******************************************************************************/
void LoadingScreen::Update(double dt)
{
	fps = 1 / dt;


	if ((loadingbar <= 20))
	{
		loadingbar += (float)(2.5 * dt);
	}
	else if ( (loadingbar >= 20) && Gamemode::getinstance()->currentgamestate==2)
	{
		//put condition to change scene
		loadingbar = 0;
		Gamemode::getinstance()->currentgamestate = 3;
	}
	else if ((loadingbar >= 20) && Gamemode::getinstance()->currentgamestate == 4)
	{
		//put condition to change scene
		loadingbar = 0;
		Gamemode::getinstance()->currentgamestate = 5;
	}
	else if ((loadingbar >= 20) && Gamemode::getinstance()->currentgamestate == 6)
	{
		//put condition to change scene
		loadingbar = 0;
		Gamemode::getinstance()->currentgamestate = 7;
	}

	static int rotateDirLimb = 1;

	if (rotateLimbs * rotateDirLimb > 30)
	{
		rotateDirLimb = -rotateDirLimb;
	}
	rotateLimbs += (float)(rotateDirLimb * 25 * dt);
}
/******************************************************************************/
/*!
\brief	Render Mesh

\param	mesh
	The mesh that is rendering
\param	enableLight
	To determine if the Obj allows light to affect it
*/
/******************************************************************************/
void LoadingScreen::renderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
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
	mesh->Render(); //this line should only be called once 
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	}

}
/******************************************************************************/
/*!
\brief	Render Text Mesh

\param	mesh
	The mesh that is rendering
\param	text
	The text you want to render
\param	color
	Color of the text
*/
/******************************************************************************/
void LoadingScreen::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
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
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}
/******************************************************************************/
/*!
\brief	Render Text Mesh on screen

\param	mesh
The mesh that is rendering
\param	text
The text you want to render
\param	color
Color of the text
\param size
Size of the text
\param x
x coordinate of the text
\param y
y coordinate of the text
*/
/******************************************************************************/
void LoadingScreen::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	//Add these code just after glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
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
		characterSpacing.SetToTranslation(i * 0.5f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
	//Add these code just before glEnable(GL_DEPTH_TEST);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

}

/******************************************************************************/
/*!
\brief	LoadingScreen main render function to render everything
*/
/******************************************************************************/
void LoadingScreen::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Temp variables
	Mtx44 translate, rotate, scale;
	Mtx44 MVP;

	//These will be replaced by matrix stack soon
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;

	//Set all matrices to identity
	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();

	//Set view matrix using camera settings
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);

	//Set projection matrix to perspective mode
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f); //FOV, Aspect Ratio, Near plane, Far plane
	
	modelStack.PushMatrix();
	modelStack.Scale(0.01,0.01,0.01);
	RenderCharacter();
	modelStack.PopMatrix();
	RenderLoadingBarOnScreen();
	RenderTextOnScreen(meshList[GEO_TEXT], "Loading...", Color(1, 1, 1), 3, 11, 15);


}
/******************************************************************************/
/*!
\brief	LoadingScreen Exiting the program
*/
/******************************************************************************/
void LoadingScreen::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
/******************************************************************************/
/*!
\brief	Function to render the loading bar on screen
*/
/******************************************************************************/
void LoadingScreen::RenderLoadingBarOnScreen()
{
	Mtx44 ortho;
	glDisable(GL_DEPTH_TEST);
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Translate(30, 40, -1);
	modelStack.Scale(loadingbar, 3, 3);
	modelStack.Translate(0.5, 0, -1);
	//modelStack.Rotate(45, 0, 1, 0);
	//modelStack.Rotate(-45, 1, 0, 0);
	renderMesh(meshList[GEO_CUBE], false);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}
/******************************************************************************/
/*!
\brief	Function to render the moaving character
*/
/******************************************************************************/
void LoadingScreen::RenderCharacter()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, -4.62f, 0);
	renderMesh(meshList[GEO_BODY], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(rotateLimbs, 0, 0, 1);
	renderMesh(meshList[GEO_ARMLEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(-rotateLimbs, 0, 0, 1);
	renderMesh(meshList[GEO_ARMRIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -2.1f, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(-rotateLimbs, 0, 0, 1);
	renderMesh(meshList[GEO_LEGLEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(rotateLimbs, 0, 0, 1);
	renderMesh(meshList[GEO_LEGRIGHT], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}