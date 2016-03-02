/****************************************************************************/
/*!
\file SP2.cpp
\author Li Zhaoyuan, Nathan Chia Shi-Lin, Terence Tan Ming Jie, Muhammad Nurhidayat Bin Suderman
\par email: lizhaoyuan123@hotmail.com
\brief
class for the Main Menu
*/
/****************************************************************************/
#include <sstream>

#include "SP2.h"
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
\brief	SP2 constructor
*/
/******************************************************************************/
SP2::SP2()
{
}

/******************************************************************************/
/*!
\brief	SP2 destructor
*/
/******************************************************************************/
SP2::~SP2()
{
}
/******************************************************************************/
/*!
\brief	SP2 main initializer function
*/
/******************************************************************************/
void SP2::Init()
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
	camera.Init(Vector3(0,0,1), Vector3(0,0,0), Vector3(0, 1, 0));

	
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("reference", Color(0,0,0));

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(0, 0, 0));
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//Pikachu2.tga");

	meshList[GEO_CUBE2] = MeshBuilder::GenerateCube("Cube", Color(0,0,0));
	
	
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//minecraft.tga");
	
	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 10000.f);
	projectionStack.LoadMatrix(projection);
	arrowpositiony = 7;
}
/******************************************************************************/
/*!
\brief	SP2 main Update function

\param	dt
	delta time
*/
/******************************************************************************/
void SP2::Update(double dt)
{
	//camera.Update(dt,100);
	fps = 1 / dt;

	if (camera.position.x >= 50 && camera.position.z >= 50 && Application::IsKeyPressed('E'))
	{
		Gamemode::getinstance()->currentgamestate = 2;
	}
	

	
	camPosX = camera.position.x;
	camPosY = camera.position.y;
	camPosz = camera.position.z;

	if (arrowpositiony > 4 && arrowpositiony < 8)
	{
		if (Application::IsKeyPressed(VK_UP) && arrowpositiony==6)
		{
			arrowpositiony += 1;
		}
		if (Application::IsKeyPressed(VK_UP) && arrowpositiony == 5)
		{
			arrowpositiony += 1;
		}
		if (Application::IsKeyPressed(VK_DOWN)&& arrowpositiony==7)
		{
			arrowpositiony -= 1;
		}
		if (Application::IsKeyPressed(VK_DOWN) && arrowpositiony == 6)
		{
			arrowpositiony -= 1;
		}
	}
	if ((arrowpositiony == 7) && (Application::IsKeyPressed(VK_RETURN)))
	{
		Gamemode::getinstance()->currentgamestate = 2;
	}
	if ((arrowpositiony == 5) && (Application::IsKeyPressed(VK_RETURN)))
	{
		application.Exit();
	}
	
	
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
void SP2::renderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	/*if (enableLight)
	{
	this->enableLight = enableLight;
	}*/
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
void SP2::RenderText(Mesh* mesh, std::string text, Color color)
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
\brief	Render black screen
*/
/******************************************************************************/
void SP2::Rendermainmenutoscreen()
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
	modelStack.Translate(40, 30, 0);
	modelStack.Scale(90, 60, 10);
	modelStack.Rotate(90, 1, 0, 0);
	renderMesh(meshList[GEO_CUBE2], false);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
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
void SP2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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
\brief	SP2 main render function to render everything
*/
/******************************************************************************/
void SP2::Render()
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
	Rendermainmenutoscreen();
	modelStack.PopMatrix();

	std::stringstream playerPos;
	//RenderTextOnScreen(meshList[GEO_TEXT], playerPos.str(), Color(1, 0, 0), 2, 0, 18);
	std::stringstream ss;
	ss << "FPS:" << fps << "         ";
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 19);

	RenderTextOnScreen(meshList[GEO_TEXT], "=>", Color(0, 1, 0), 3, 3.5, arrowpositiony);
	RenderTextOnScreen(meshList[GEO_TEXT], "Start", Color(0, 1, 0), 3, 5, 7);
	RenderTextOnScreen(meshList[GEO_TEXT], "Exit", Color(0, 1, 0), 3, 5, 5);
	
	RenderTextOnScreen(meshList[GEO_TEXT], "The Adventures Of Yalam", Color(1, 1, 1), 5, 3, 7);
}
/******************************************************************************/
/*!
\brief	SP2 Exiting the program
*/
/******************************************************************************/
void SP2::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}


