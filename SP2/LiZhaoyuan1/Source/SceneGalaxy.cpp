/******************************************************************************/
/*!
\file SceneGalaxy.cpp
\author Li Zhaoyuan, Nathan Chia Shi-Lin, Terence Tan Ming Jie, Muhammad Nurhidayat Bin Suderman
\par email: lizhaoyuan123@hotmail.com
\brief
	SceneGalaxy cpp file, everything needed inside the scene, found here
*/
/******************************************************************************/

#include <sstream>

#include "SceneGalaxy.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"
#include "Light.h"
#include "Material.h"
#include "Utility.h"

#include "LoadTGA.h"

Missile missile(30);

/****************************************************************************/
/*!
\brief	SceneGalaxy constructor
*/
/****************************************************************************/
SceneGalaxy::SceneGalaxy()
{
}

/****************************************************************************/
/*!
\brief	SceneGalaxy destructor
*/
/****************************************************************************/
SceneGalaxy::~SceneGalaxy()
{
}

/****************************************************************************/
/*!
\brief
	Scene Galaxy main initializer function
*/
/****************************************************************************/
void SceneGalaxy::Init()
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
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");

	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");


	glUseProgram(m_programID);

	glUniform1i(m_parameters[U_NUMLIGHTS], 2);

	light[0].type = Light::LIGHT_SPOT;
	light[0].position.Set(-5, 2, -10);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.01f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	light[1].type = Light::LIGHT_DIRECTIONAL;
	light[1].position.Set(2, 2, 0);
	light[1].color.Set(1, 1, 1);
	light[1].power = 1;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.01f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);


	//Initialize camera settings
	camera.Init(Vector3(0, 500, 0), Vector3(0, 500, -600), Vector3(0, 1, 0));


	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("reference", Color(0, 0, 0));

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1));

	meshList[GEO_GALAXYFRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1));
	meshList[GEO_GALAXYFRONT]->textureID = LoadTGA("Image//NebulaFront.tga");
	meshList[GEO_GALAXYBACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1));
	meshList[GEO_GALAXYBACK]->textureID = LoadTGA("Image//NebulaLeft.tga");
	meshList[GEO_GALAXYTOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1));
	meshList[GEO_GALAXYTOP]->textureID = LoadTGA("Image//NebulaTop_Kai.tga");
	meshList[GEO_GALAXYBOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1));
	meshList[GEO_GALAXYBOTTOM]->textureID = LoadTGA("Image//NebulaBottom_Kai.tga");
	meshList[GEO_GALAXYLEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1));
	meshList[GEO_GALAXYLEFT]->textureID = LoadTGA("Image//NebulaBack_Kai.tga");
	meshList[GEO_GALAXYRIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1));
	meshList[GEO_GALAXYRIGHT]->textureID = LoadTGA("Image//NebulaRight.tga");

	meshList[GEO_XWING] = MeshBuilder::GenerateOBJ("xwing", "OBJ//XWing.obj");
	meshList[GEO_XWING]->textureID = LoadTGA("Image//XWing_Texture.tga");
	meshList[GEO_XWING]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_XWING]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_XWING]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_XWING]->material.kShininess = 5.f;

	meshList[GEO_ASTEROID] = MeshBuilder::GenerateOBJ("asteroid", "OBJ//asteroid.obj");
	meshList[GEO_ASTEROID]->textureID = LoadTGA("Image//asteroid.tga");
	meshList[GEO_ASTEROID]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_ASTEROID]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_ASTEROID]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_ASTEROID]->material.kShininess = 5.f;

	meshList[GEO_MISSILE] = MeshBuilder::GenerateOBJ("missile", "OBJ//missile.obj");
	meshList[GEO_MISSILE]->textureID = LoadTGA("Image//missile.tga");
	meshList[GEO_MISSILE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MISSILE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MISSILE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MISSILE]->material.kShininess = 5.f;

	meshList[GEO_BLACKSCREEN] = MeshBuilder::GenerateQuad("BlackScreen", Color(0, 0, 0));
	meshList[GEO_BLACKSCREEN]->textureID = LoadTGA("Image//QuestShown.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//TimesNewRoman.tga");
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 18, 36);

	Mtx44 projection;
	projection.SetToPerspective(45.f, 16.f / 9.f, 0.1f, 10000.f);
	projectionStack.LoadMatrix(projection);

	camera.SceneGalaxy = true;
	camera.SceneMun = false;
	camera.SceneSoraJewel = false;
	missile.init(&camera);
}

//Asteroid

/****************************************************************************/
/*!
\brief	SceneGalaxy MovingAsteroid function
\param
	delta time
*/
/****************************************************************************/
void SceneGalaxy::MovingAsteroid(double dt)
{
	missileView = missilePos + missileTar;
	float speed = 0.1f;
	CheckAsteroidStartWave();
	CheckAsteroidWave1();
	CheckAsteroidWave2();
	CheckLargeAsteroid();

	if (QuestDetailShown == true)
	{
		if (CheckAsteroidStartWave() == false && CheckAsteroidWave1() == false && CheckAsteroidWave2() == false && CheckLargeAsteroid() == false)
		{
			if (getMagnitude(XWing, Asteroid) > 1)
			{
				Asteroid -= (Asteroid - XWing) * speed * dt;
				CheckCollision(missileView, Asteroid);
				if (CheckCollision(missileView, Asteroid) == true)
				{
					renderAsteroid = false;
				}
			}

			if (getMagnitude(XWing, Asteroid) < 10)
			{
				renderAsteroid = false;
			}

			if (getMagnitude(XWing, Asteroid2) > 1)
			{
				Asteroid2 -= (Asteroid2 - XWing) * speed * dt;
				CheckCollision(missileView, Asteroid2);
				if (CheckCollision(missileView, Asteroid2) == true)
				{
					renderAsteroid2 = false;
				}
			}

			if (getMagnitude(XWing, Asteroid2) < 10)
			{
				renderAsteroid2 = false;
			}

			if (getMagnitude(XWing, Asteroid3) > 1)
			{
				Asteroid3 -= (Asteroid3 - XWing) * speed * dt;
				CheckCollision(missileView, Asteroid3);
				if (CheckCollision(missileView, Asteroid3) == true)
				{
					renderAsteroid3 = false;
				}
			}

			if (getMagnitude(XWing, Asteroid3) < 10)
			{
				renderAsteroid3 = false;
			}

		}


		if (CheckAsteroidStartWave() == true && CheckAsteroidWave1() == false && CheckAsteroidWave2() == false && CheckLargeAsteroid() == false)
		{

			if (getMagnitude(XWing, Asteroid4) > 1)
			{
				Asteroid4 -= (Asteroid4 - XWing) * speed * dt;
				CheckCollision(missileView, Asteroid4);
				if (CheckCollision(missileView, Asteroid4) == true)
				{
					renderAsteroid4 = false;
				}
			}

			if (getMagnitude(XWing, Asteroid4) < 10)
			{
				renderAsteroid4 = false;
			}

			if (getMagnitude(XWing, Asteroid5) > 1)
			{
				Asteroid5 -= (Asteroid5 - XWing) * speed * dt;
				CheckCollision(missileView, Asteroid5);
				if (CheckCollision(missileView, Asteroid5) == true)
				{
					renderAsteroid5 = false;
				}
			}

			if (getMagnitude(XWing, Asteroid5) < 10)
			{
				renderAsteroid5 = false;
			}

			if (getMagnitude(XWing, Asteroid6) > 1)
			{
				Asteroid6 -= (Asteroid6 - XWing) * speed * dt;
				CheckCollision(missileView, Asteroid6);
				if (CheckCollision(missileView, Asteroid6) == true)
				{
					renderAsteroid6 = false;
				}
			}

			if (getMagnitude(XWing, Asteroid6) < 10)
			{
				renderAsteroid6 = false;
			}
		}


		if (CheckAsteroidStartWave() == true && CheckAsteroidWave1() == true && CheckAsteroidWave2() == false && CheckLargeAsteroid() == false)
		{
			if (getMagnitude(XWing, Asteroid7) > 1)
			{
				Asteroid7 -= (Asteroid7 - XWing) * speed * dt;
				CheckCollision(missileView, Asteroid7);
				if (CheckCollision(missileView, Asteroid7) == true)
				{
					renderAsteroid7 = false;
				}
			}

			if (getMagnitude(XWing, Asteroid7) < 10)
			{
				renderAsteroid7 = false;
			}

			if (getMagnitude(XWing, Asteroid8) > 1)
			{
				Asteroid8 -= (Asteroid8 - XWing) * speed * dt;
				CheckCollision(missileView, Asteroid8);
				if (CheckCollision(missileView, Asteroid8) == true)
				{
					renderAsteroid8 = false;
				}
			}

			if (getMagnitude(XWing, Asteroid8) < 10)
			{
				renderAsteroid8 = false;
			}

			if (getMagnitude(XWing, Asteroid9) > 1)
			{
				Asteroid9 -= (Asteroid9 - XWing) * speed * dt;
				CheckCollision(missileView, Asteroid9);
				if (CheckCollision(missileView, Asteroid9) == true)
				{
					renderAsteroid9 = false;
				}
			}

			if (getMagnitude(XWing, Asteroid9) < 10)
			{
				renderAsteroid9 = false;
			}

			if (getMagnitude(XWing, Asteroid10) > 1)
			{
				Asteroid10 -= (Asteroid10 - XWing) * speed * dt;
				CheckCollision(missileView, Asteroid10);
				if (CheckCollision(missileView, Asteroid10) == true)
				{
					renderAsteroid10 = false;
				}
			}

			if (getMagnitude(XWing, Asteroid10) < 10)
			{
				renderAsteroid10 = false;
			}
		}

		if (CheckAsteroidStartWave() == true && CheckAsteroidWave1() == true && CheckAsteroidWave2() == true && CheckLargeAsteroid() == false)
		{
			if (getMagnitude(XWing, LAsteroid) > 100)
			{
				LAsteroid -= (LAsteroid - XWing) * 0.3f * dt;
			}
			if (getMagnitude(XWing, LAsteroid) == 100)
			{
				renderAsteroidLarge = false;
				renderXWing = false;
				renderSkybox = false;
			}
		}
	}
}

/****************************************************************************/
/*!
\brief	SceneGalaxy CheckAsteroidStartWave function
\return
	true/false
*/
/****************************************************************************/
bool SceneGalaxy::CheckAsteroidStartWave()
{
	if (renderAsteroid == false && renderAsteroid2 == false && renderAsteroid3 == false)
		return true;
	return false;
}

/****************************************************************************/
/*!
\brief	SceneGalaxy CheckAsteroidWave1 function
\return
	true/false
*/
/****************************************************************************/
bool SceneGalaxy::CheckAsteroidWave1()
{	
	if (renderAsteroid4 == false && renderAsteroid5 == false && renderAsteroid6 == false)
		return true;
	return false;
}

/****************************************************************************/
/*!
\brief	SceneGalaxy CheckAsteoidWave2 function
\return
	true/false
*/
/****************************************************************************/
bool SceneGalaxy::CheckAsteroidWave2()
{
	if (renderAsteroid7 == false && renderAsteroid8 == false && renderAsteroid9 == false && renderAsteroid10 == false)
		return true;
	return false;
}

/****************************************************************************/
/*!
\brief	SceneGalaxy CheckLargeAsteroid function
\return
	true/false
*/
/****************************************************************************/
bool SceneGalaxy::CheckLargeAsteroid()
{
	if (renderAsteroidLarge == false)
		return true;
	return false;
}

//Asteroid

//Formula

/****************************************************************************/
/*!
\brief	SceneGalaxy CheckCollision function
\param
	Vector3 A
	Vector3 B
\return
	true/false
*/
/****************************************************************************/
bool SceneGalaxy::CheckCollision(Vector3 A, Vector3 B)
{
	float x = 15.f, y = 15.f, z = 500.f;
	if (A.x > B.x - x && A.x < B.x + x
		&& A.y > B.y && A.y < B.y + y
		&& A.z> B.z - z && A.z < B.z + z)
		return true;
	return false;
}

/****************************************************************************/
/*!
\brief	SceneGalaxy getMagnitude function
\param
	Vector3 A
	Vector3 B
\return
	Magnitude
*/
/****************************************************************************/
int SceneGalaxy::getMagnitude(Vector3 A, Vector3 B)
{
	// A camera, B target
	int totalX = (A.x - B.x) * (A.x - B.x);
	int totalY = (A.y - B.y) * (A.y - B.y);
	int totalZ = (A.z - B.z) * (A.z - B.z);
	int magnitude = totalX + totalY + totalZ;
	return sqrt(magnitude);
}

//Formula

/****************************************************************************/
/*!
\brief SceneGalaxy main update function
\param
	delta time
*/
/****************************************************************************/
void SceneGalaxy::Update(double dt)
{
	camera.XWingCamera(dt, 100);
	fps = 1.f / dt;

	if (Application::IsKeyPressed('5'))
	{
		light[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	else if (Application::IsKeyPressed('6'))
	{
		light[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	else if (Application::IsKeyPressed('7'))
	{
		light[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}

	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	if (Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('K'))
		light[0].position.z += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		light[0].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('P'))
		light[0].position.y += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('X'))
		enableLight = true;
	if (Application::IsKeyPressed('Z'))
		enableLight = false;

	//

	missile.update(dt);

	delaymissile += dt * 2;
	if (delaymissile >= 0.1f)
	{
		delaymissile = 0;
		shootMissile = true;
	}
	else
	{
		shootMissile = false;
	}

	if (Application::IsKeyPressed(VK_LBUTTON)) 
	{
		if (shootMissile == true)
		{
			missile.Firing();
		}
		
	}
	
	MovingAsteroid(dt);
	CutScene(dt);


	camPosX = camera.position.x;
	camPosY = camera.position.y;
	camPosz = camera.position.z;
	
	
} 

//Render Functions

/****************************************************************************/
/*!
\brief SceneGalaxy renderMesh function
\param
	The mesh that is rendering
	Determine if the OBJ allows light to affect it
*/
/****************************************************************************/
void SceneGalaxy::renderMesh(Mesh *mesh, bool enableLight)
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

/****************************************************************************/
/*!
\brief	SceneGalaxy RenderText function
\param
	The mesh that is rendering
	The text that is being render
	Color of the Text
*/
/****************************************************************************/
void SceneGalaxy::RenderText(Mesh* mesh, std::string text, Color color)
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

/****************************************************************************/
/*!
\brief	SceneGalaxy RenderTextOnScreen function
\param
	The mesh that is rendering
	The text that is being render
	Color of the text
	Size of the text
	x Coord of the text
	z Coord of the text
*/
/****************************************************************************/
void SceneGalaxy::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

/****************************************************************************/
/*!
\brief	SceneGalaxy Render function
*/
/****************************************************************************/
void SceneGalaxy::Render()
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
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	modelStack.Scale(0.1f, 0.1f, 0.1f);
	renderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	
	/*modelStack.PushMatrix();
	renderMesh(meshList[GEO_AXES], false);
	modelStack.PopMatrix();*/

	modelStack.PushMatrix();
	modelStack.Translate(0, 496.9f, 0);
	RenderSkybox();
	modelStack.PopMatrix();

	RenderXwing();
	RenderAsteroid();
	RenderMissile();
	QuestDetail();

	RenderTextOnScreen(meshList[GEO_TEXT], "+", Color(0, 1, 0), 3, 13.1, 9);
	std::stringstream playerPos;
	playerPos << "X = " << camPosX << " Y = " << camPosY << " Z = " << camPosz;
	//RenderTextOnScreen(meshList[GEO_TEXT], playerPos.str(), Color(1, 0, 0), 2, 0, 18);
	std::stringstream ss;
	ss << "FPS:" << fps << "         " << playerPos.str();
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 19);

}

//Render Functions

//Rendering 

/****************************************************************************/
/*!
\brief	SceneGalaxy RenderXWing function
*/
/****************************************************************************/
void SceneGalaxy::RenderXwing()
{
	if (renderXWing == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(XWing.x, XWing.y, XWing.z);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Rotate(rotateXWing, 0, 0, 1);
		modelStack.Rotate(camera.rotateChar, 0, 1, 0);
		modelStack.Scale(2.2f, 2.2f, 2.2f);
		renderMesh(meshList[GEO_XWING], true);
		modelStack.PopMatrix();
	}

}

/****************************************************************************/
/*!
\brief	SceneGalaxy RenderAsteroid function
*/
/****************************************************************************/
void SceneGalaxy::RenderAsteroid()
{
	if (renderAsteroid == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Asteroid.x, Asteroid.y, Asteroid.z);
		modelStack.Scale(2.2f, 2.2f, 2.2f);
		renderMesh(meshList[GEO_ASTEROID], true);
		modelStack.PopMatrix();
	}

	if (renderAsteroid2 == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Asteroid2.x, Asteroid2.y, Asteroid2.z);
		modelStack.Scale(2.2f, 2.2f, 2.2f);
		renderMesh(meshList[GEO_ASTEROID], true);
		modelStack.PopMatrix();
	}

	if (renderAsteroid3 == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Asteroid3.x, Asteroid3.y, Asteroid3.z);
		modelStack.Scale(2.2f, 2.2f, 2.2f);
		renderMesh(meshList[GEO_ASTEROID], true);
		modelStack.PopMatrix();
	}

	if (renderAsteroid4 == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Asteroid4.x, Asteroid4.y, Asteroid4.z);
		modelStack.Scale(2.2f, 2.2f, 2.2f);
		renderMesh(meshList[GEO_ASTEROID], true);
		modelStack.PopMatrix();
	}

	if (renderAsteroid5 == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Asteroid5.x, Asteroid5.y, Asteroid5.z);
		modelStack.Scale(2.2f, 2.2f, 2.2f);
		renderMesh(meshList[GEO_ASTEROID], true);
		modelStack.PopMatrix();
	}

	if (renderAsteroid6 == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Asteroid6.x, Asteroid6.y, Asteroid6.z);
		modelStack.Scale(2.2f, 2.2f, 2.2f);
		renderMesh(meshList[GEO_ASTEROID], true);
		modelStack.PopMatrix();
	}

	if (renderAsteroid7 == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Asteroid7.x, Asteroid7.y, Asteroid7.z);
		modelStack.Scale(2.2f, 2.2f, 2.2f);
		renderMesh(meshList[GEO_ASTEROID], true);
		modelStack.PopMatrix();
	}

	if (renderAsteroid8 == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Asteroid8.x, Asteroid8.y, Asteroid8.z);
		modelStack.Scale(2.2f, 2.2f, 2.2f);
		renderMesh(meshList[GEO_ASTEROID], true);
		modelStack.PopMatrix();
	}

	if (renderAsteroid9 == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Asteroid9.x, Asteroid9.y, Asteroid9.z);
		modelStack.Scale(2.2f, 2.2f, 2.2f);
		renderMesh(meshList[GEO_ASTEROID], true);
		modelStack.PopMatrix();
	}

	if (renderAsteroid10 == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Asteroid10.x, Asteroid10.y, Asteroid10.z);
		modelStack.Scale(2.2f, 2.2f, 2.2f);
		renderMesh(meshList[GEO_ASTEROID], true);
		modelStack.PopMatrix();
	}

	if (renderAsteroidLarge == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(LAsteroid.x, LAsteroid.y, LAsteroid.z);
		modelStack.Scale(22.2f, 22.2f, 22.2f);
		renderMesh(meshList[GEO_ASTEROID], true);
		modelStack.PopMatrix();
	}

}

/****************************************************************************/
/*!
\brief	SceneGalaxy RenderMissile function
*/
/****************************************************************************/
void SceneGalaxy::RenderMissile()
{

	if (shootMissile == true)
	{
		for (int i = 0; i < missile.Missiles; i++)
		{
			modelStack.PushMatrix();
			missilePos = missile.Capacity[i].getPositionOfMissile();
			modelStack.Translate((missilePos.x) , (missilePos.y), (missilePos.z));
			modelStack.Scale(4.f, 4.f, 4.f);
			modelStack.Rotate(camera.rotateChar, 0, 1, 0);
			renderMesh(meshList[GEO_MISSILE], true);
			modelStack.PopMatrix();
		}
	}
}

/****************************************************************************/
/*!
\brief	SceneGalaxy RenderSkybox function
*/
/****************************************************************************/
void SceneGalaxy::RenderSkybox()
{
	if (renderSkybox == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(0, 0, -498);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(1000, 1000, 1000);
		renderMesh(meshList[GEO_GALAXYBACK], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 498, 0);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Rotate(180, 1, 0, 0);
		modelStack.Scale(1000, 1000, 1000);
		renderMesh(meshList[GEO_GALAXYTOP], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-498, 0, 0);
		modelStack.Rotate(-90, 0, 0, 1);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(1000, 1000, 1000);
		renderMesh(meshList[GEO_GALAXYLEFT], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(498, 0, 0);
		modelStack.Rotate(90, 0, 0, 1);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(1000, 1000, 1000);
		renderMesh(meshList[GEO_GALAXYFRONT], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, -498, 0);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(1000, 1000, 1000);
		renderMesh(meshList[GEO_GALAXYBOTTOM], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, 498);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(1000, 1000, 1000);
		renderMesh(meshList[GEO_GALAXYRIGHT], false);
		modelStack.PopMatrix();
	}
}

//Rendering

/****************************************************************************/
/*!
\brief	SceneGalaxy CutScene function
\param
	delta time
*/
/****************************************************************************/
void SceneGalaxy::CutScene(double dt)
{
	if (CheckAsteroidStartWave() == true && CheckAsteroidWave1() == true && CheckAsteroidWave2() == true && CheckLargeAsteroid() == false)
	{
		camera.Init(Vector3(100, 570, 200), Vector3(0, 500, -50), Vector3(0, 1, 0));
		shootMissile = false;
	}

	if (CheckAsteroidStartWave() == true && CheckAsteroidWave1() == true && CheckAsteroidWave2() == true && CheckLargeAsteroid() == true)
	{
		Gamemode::getinstance()->currentgamestate = 6;
	}
}

/****************************************************************************/
/*!
\brief	SceneGalaxy QuestDetail function
*/
/****************************************************************************/
void SceneGalaxy::QuestDetail()
{
	if (QuestDetailShown == false)
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
		modelStack.Translate(37.5, 27.5, -2);
		modelStack.Scale(30, 50, 10);
		modelStack.Rotate(90, 1, 0, 0);
		renderMesh(meshList[GEO_BLACKSCREEN], false);
		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);

		if (Application::IsKeyPressed('E'))
		{
			QuestDetailShown = true;
		}
	}
}

/****************************************************************************/
/*!
\brief SceneGalaxy Exit function
*/
/****************************************************************************/
void SceneGalaxy::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
