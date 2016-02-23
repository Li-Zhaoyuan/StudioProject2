#include <sstream>

#include "SceneMun.h"
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
//#include "RenderMun.h"
//#include "LoadOBJ.h"
SceneMun::SceneMun()
{
}
SceneMun::~SceneMun()
{
}
void SceneMun::Init()
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

	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(0, 100, -100);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	light[1].type = Light::LIGHT_DIRECTIONAL;
	light[1].position.Set(0, 100, 100);
	light[1].color.Set(1, 1, 1);
	light[1].power = 1;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
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
	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));
	camera.minimapcoords.y = 55;
	camera.minimapcoords.x = 75;
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("reference", Color(0, 1, 0));

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1));

	//Skybox
	meshList[GEO_MUNFRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1));
	meshList[GEO_MUNFRONT]->textureID = LoadTGA("Image//MunFront.tga");
	meshList[GEO_MUNBACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1));
	meshList[GEO_MUNBACK]->textureID = LoadTGA("Image//MunLeft.tga");
	meshList[GEO_MUNTOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1));
	meshList[GEO_MUNTOP]->textureID = LoadTGA("Image//MunTop.tga");
	meshList[GEO_MUNBOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1));
	meshList[GEO_MUNBOTTOM]->textureID = LoadTGA("Image//MunBottom.tga");
	meshList[GEO_MUNLEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1));
	meshList[GEO_MUNLEFT]->textureID = LoadTGA("Image//MunBack.tga");
	meshList[GEO_MUNRIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1));
	meshList[GEO_MUNRIGHT]->textureID = LoadTGA("Image//MunRight.tga");
	meshList[GEO_MUNGROUND] = MeshBuilder::GenerateQuad("ground", Color(0.2f, 0.2f, 0.2f));

	//Objs -Xwing
	meshList[GEO_CRASHEDPLANE] = MeshBuilder::GenerateOBJ("crashedplane", "OBJ//XWingCrash.obj");
	meshList[GEO_CRASHEDPLANE]->textureID = LoadTGA("Image//XWingCrash_Texture.tga");
	meshList[GEO_CRASHEDPLANE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CRASHEDPLANE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CRASHEDPLANE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CRASHEDPLANE]->material.kShininess = 5.f;
	meshList[GEO_PLANE] = MeshBuilder::GenerateOBJ("plane", "OBJ//XwingLand.obj");
	meshList[GEO_PLANE]->textureID = LoadTGA("Image//XWing_Texture.tga");
	meshList[GEO_PLANE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_PLANE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_PLANE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_PLANE]->material.kShininess = 5.f;
	//Houses
	meshList[GEO_HOUSE] = MeshBuilder::GenerateOBJ("house", "OBJ//house.obj");
	meshList[GEO_HOUSE]->textureID = LoadTGA("Image//house.tga");
	meshList[GEO_HOUSE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HOUSE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HOUSE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HOUSE]->material.kShininess = 5.f;
	//NPCS
	meshList[GEO_ALIEN] = MeshBuilder::GenerateOBJ("Guy", "OBJ//CharacterModel.obj");
	meshList[GEO_ALIEN]->textureID = LoadTGA("Image//CatAlien.tga");
	meshList[GEO_ALIEN]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_ALIEN]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_ALIEN]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_ALIEN]->material.kShininess = 5.f;

	meshList[GEO_FEMALEA] = MeshBuilder::GenerateOBJ("femaleA", "OBJ//CharacterModel.obj");
	meshList[GEO_FEMALEA]->textureID = LoadTGA("Image//FemaleCharacter2.tga");
	meshList[GEO_FEMALEA]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_FEMALEA]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_FEMALEA]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_FEMALEA]->material.kShininess = 5.f;

	//Cave
	meshList[GEO_CAVE] = MeshBuilder::GenerateOBJ("cave", "OBJ//Cave.obj");
	meshList[GEO_CAVE]->textureID = LoadTGA("Image//StoneTile.tga");
	meshList[GEO_CAVE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CAVE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CAVE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CAVE]->material.kShininess = 5.f;
	//Pickaxe Pick-up item
	meshList[GEO_PICKAXE] = MeshBuilder::GenerateOBJ("pickaxe", "OBJ//Pickaxe.obj");
	meshList[GEO_PICKAXE]->textureID = LoadTGA("Image//Pickaxe.tga");
	meshList[GEO_PICKAXE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_PICKAXE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_PICKAXE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_PICKAXE]->material.kShininess = 5.f;

	meshList[GEO_ORE] = MeshBuilder::GenerateOBJ("ore", "OBJ//oreCube.obj");
	meshList[GEO_ORE]->textureID = LoadTGA("Image//diamondOre.tga");
	meshList[GEO_ORE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_ORE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_ORE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_ORE]->material.kShininess = 5.f;
	//Minimaps
	//meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("target", Color(1, 0, 0), 18, 36);

	meshList[GEO_MINIMAP] = MeshBuilder::GenerateQuad("Minimap", Color(1.f, 1.f, 1.f));
	meshList[GEO_MINIMAP]->textureID = LoadTGA("Image//Munmap.tga");
	
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//TimesNewRoman.tga");
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 18, 36);

	meshList[GEO_MAINICON] = MeshBuilder::GenerateCube("mainicon for map", Color(1, 0, 0));

	Mtx44 projection;
	projection.SetToPerspective(45.f, 16.f / 9.f, 0.1f, 10000.f);
	projectionStack.LoadMatrix(projection);

	camera.SceneGalaxy = false;
	camera.SceneMun = true;
	camera.SceneSoraJewel = false;

	/*boxX = 0;
	boxZ = 0;
	camPosX = 0;
	camPosY = 0;
	camPosz = 0;

	crashedplaneCoord = Vector3(-36.f, 4.9f, -34.f);
	planecoord = Vector3(-36.f, -2.9f, -45.f);
	questdudehouseCoord = Vector3(33, -5, 20);
	worriedladyhouseCoord = Vector3(20, -5, -38);
	worriedladyCoord = Vector3(2, -4, -38);
	questdudeCoord = Vector3(33, -4, 3);
	minerandplusCoord = Vector3(-19, 0, 25);
	caveCoord = Vector3(-35, -5, 35);
	oreCoord = Vector3(-42, -2.75, 35);

	worriedladytempx = 0;
	worriedladytempz = 0;

	minerandplusx = 0;
	minerandplusz = 0;

	questdudex = 0;
	questdudez = 0;

	rotateworriedlady = 0;
	rotateminer = 0;
	rotatequestdude = 0;

	loadingbar = 0.01f;

	mining = false;
	isMined = false;*/
}


void SceneMun::Update(double dt)
{
	camera.Update(dt, 100);
	fps = 1 / dt;

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

	camPosX = camera.position.x;
	camPosY = camera.position.y;
	camPosz = camera.position.z;
	
	if ((mining || isRepairing) && loadingbar <= 20)
	{
		loadingbar += (float)(5 * dt);
	}
	else if (mining && loadingbar >= 20)
	{
		isMined = true;
	}
	else if (isRepairing && loadingbar >= 20)
	{
		isRepaired = true;
	}
	else
	{
		loadingbar = 0.01f;
	}

	/*if (isRepairing && loadingbar <= 20)
	{
		loadingbar += (float)(5 * dt);
	}
	else if (isRepairing && loadingbar >= 20)
	{
		isRepaired = true;
	}
	else
	{
		loadingbar = 0.01f;
	}*/

	npcRotate();
	interactions();
	camera.target;
}
void SceneMun::lighting()
{
	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top()* light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() *light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_POINT)
	{

		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}
}
void SceneMun::lighting2()
{
	if (light[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[1].position.x, light[1].position.y, light[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top()* light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() *light[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else if (light[1].type == Light::LIGHT_POINT)
	{

		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}

}
void SceneMun::renderMesh(Mesh *mesh, bool enableLight)
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

void SceneMun::RenderText(Mesh* mesh, std::string text, Color color)
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

void SceneMun::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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
		characterSpacing.SetToTranslation(i * 0.5f + 0.7f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
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

void SceneMun::Renderpicturetoscreen()
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
	modelStack.Translate(75, 55, -2);
	modelStack.Scale(10, 10, 10);
	modelStack.Rotate(90, 1, 0, 0);
	renderMesh(meshList[GEO_MINIMAP], false);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);

	glDisable(GL_DEPTH_TEST);
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Translate(camera.minimapcoords.x,camera.minimapcoords.y, -1);
	modelStack.Scale(0.5, 0.5, 0.5);
	modelStack.Rotate(90, 1, 0, 0);
	renderMesh(meshList[GEO_MAINICON], false);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);

}

void SceneMun::Render()
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
	lighting();
	lighting2();
	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	modelStack.Scale(0.1f, 0.1f, 0.1f);
	renderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	renderMesh(meshList[GEO_AXES], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//modelStack.Translate(0, 496.9, 0);
	modelStack.Rotate(180, 1, 0, 0);
	RenderSkybox();
	modelStack.PopMatrix();
	

	modelStack.PushMatrix();
	modelStack.Translate(0, -5, 0);
	modelStack.Scale(100, 100, 100);
	renderMesh(meshList[GEO_MUNGROUND], false);
	modelStack.PopMatrix();

	if (!isRepaired)
	{
		modelStack.PushMatrix();
		modelStack.Translate(crashedplaneCoord.x, crashedplaneCoord.y, crashedplaneCoord.z);
		modelStack.Scale(2.2f, 2.2f, 2.2f);
		renderMesh(meshList[GEO_CRASHEDPLANE], true);
		modelStack.PopMatrix();
	}
	if (isRepaired)
	{
		modelStack.PushMatrix();
		modelStack.Translate(planecoord.x, planecoord.y, planecoord.z);
		modelStack.Scale(2.2f, 2.2f, 2.2f);
		renderMesh(meshList[GEO_PLANE], true);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Translate(questdudehouseCoord.x, questdudehouseCoord.y, questdudehouseCoord.z);
	renderMesh(meshList[GEO_HOUSE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(worriedladyhouseCoord.x, worriedladyhouseCoord.y, worriedladyhouseCoord.z);
	modelStack.Rotate(90, 0, 1, 0);
	renderMesh(meshList[GEO_HOUSE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(worriedladyCoord.x, worriedladyCoord.y, worriedladyCoord.z);
	modelStack.Rotate(-rotateworriedlady, 0, 1, 0);
	modelStack.Rotate(180, 0, 1, 0);
	renderMesh(meshList[GEO_FEMALEA], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(questdudeCoord.x, questdudeCoord.y, questdudeCoord.z);
	modelStack.Rotate(rotatequestdude, 0, 1, 0);
	modelStack.Rotate(90, 0, 1, 0);
	renderMesh(meshList[GEO_ALIEN], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(caveCoord.x, caveCoord.y, caveCoord.z);
	modelStack.Scale(5, 5, 5);
	//modelStack.Rotate(90, 0, 1, 0);
	renderMesh(meshList[GEO_CAVE], true);
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
	modelStack.Translate(minerandplusCoord.x, minerandplusCoord.y, minerandplusCoord.z);
	modelStack.Rotate(rotateminer, 0, 1, 0);
	modelStack.PushMatrix();
	modelStack.Translate(0, -5.5, 0);
	renderMesh(meshList[GEO_ALIEN], true);
	modelStack.PopMatrix();
	if (!playergetpickaxe)
	{
		modelStack.PushMatrix();
		//modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Translate(0.5, -2.75, 1.25);
		modelStack.Rotate(-90, 0, 0, 1);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(0.5, 0.5, 0.5);
		renderMesh(meshList[GEO_PICKAXE], true);
		modelStack.PopMatrix();
	}
		
	modelStack.PopMatrix();
	if (!isMined)
	{
		modelStack.PushMatrix();
		modelStack.Translate(oreCoord.x, oreCoord.y, oreCoord.z);
		modelStack.Scale(2, 2, 2);
		renderMesh(meshList[GEO_ORE], true);
		modelStack.PopMatrix();
	}
	if (isMined)
	{
		RenderOreOnScreen();
	}

	modelStack.PushMatrix();
	modelStack.Translate(camera.target.x, camera.target.y, camera.target.z);
	modelStack.Scale(0.01f, 0.01f, 0.01f);
	renderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	if (!isMined && playergetpickaxe == true)
	{
		RenderPickaxeOnScreen();
	}
	RenderLetterOnScreen();
	Renderpicturetoscreen();
	if (mining)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "M ining", Color(0, 1, 0), 3, 11, 15);
		RenderLoadingBarOnScreen();
	}
	if (isRepairing && isMined)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Repairing", Color(0, 1, 0), 3, 11, 15);
		RenderLoadingBarOnScreen();
	}
	RenderTextBoxOnScreen();
	
	std::stringstream playerPos;
	playerPos << "X = " << camPosX << " Y = " << camPosY << " Z = " << camPosz;
	//RenderTextOnScreen(meshList[GEO_TEXT], playerPos.str(), Color(1, 0, 0), 2, 0, 18);
	std::stringstream ss;
	ss << "FPS:" << fps << "         " << playerPos.str();
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 19);
}

void SceneMun::RenderSkybox()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -498);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	renderMesh(meshList[GEO_MUNBACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 498, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	renderMesh(meshList[GEO_MUNTOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-498, 0, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	renderMesh(meshList[GEO_MUNLEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(498, 0, 0);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	renderMesh(meshList[GEO_MUNFRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -498, 0);
	modelStack.Scale(1000, 1000, 1000);
	renderMesh(meshList[GEO_MUNBOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 498);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	renderMesh(meshList[GEO_MUNRIGHT], false);
	modelStack.PopMatrix();

}

void SceneMun::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void SceneMun::npcRotate()
{
	if (camera.position.x < worriedladyCoord.x)
	{
		worriedladytempx = worriedladyCoord.x - camera.position.x;
		worriedladytempz = worriedladyCoord.z - camera.position.z;
		rotateworriedlady = atan(worriedladytempz / worriedladytempx)*(180 / Math::PI);
	}

	if (camera.position.x > minerandplusCoord.x)
	{
		minerandplusx = minerandplusCoord.x - camera.position.x;
		minerandplusz = camera.position.z - minerandplusCoord.z;
		rotateminer = atan(minerandplusz / minerandplusx)*(180 / Math::PI);
	}

	if (camera.position.z < questdudeCoord.z)
	{
		questdudex = questdudeCoord.x - camera.position.x;
		questdudez = questdudeCoord.z - camera.position.z;
		rotatequestdude = atan(questdudex / questdudez)*(180 / Math::PI);
	}
}

void SceneMun::interactions()
{
	Vector3 tempview = (camera.target - camera.position);
	Vector3 viewAtOre = (oreCoord - camera.position);
	Vector3 viewAtLady = (worriedladyCoord - camera.position);
	Vector3 viewAtDude = (questdudeCoord - camera.position);
	Vector3 viewAtMiner = (minerandplusCoord - camera.position);
	Vector3 viewAtCrashedPlane = (crashedplaneCoord - camera.position);
	float RadiusFromOre = (viewAtOre - tempview).Length();
	float RadiusFromLady = (viewAtLady - tempview).Length();
	float RadiusFromDude = (viewAtDude - tempview).Length();
	float RadiusFromMiner = (viewAtMiner - tempview).Length();
	float RadiusFromCrashedPlane = (viewAtCrashedPlane - tempview).Length();
	
	
	if (RadiusFromOre < 2.5f
		&& playergetpickaxe == true
		&& Application::IsKeyPressed(VK_LBUTTON)
		&& !isMined)
	{
		mining = true;
	}
	else
	{
		mining = false;
	}

	if (RadiusFromCrashedPlane < 7.5f
		&& Application::IsKeyPressed(VK_LBUTTON)
		&& !isRepaired)
	{
		isRepairing = true;
	}
	else
	{
		isRepairing = false;
	}

	if (RadiusFromLady < 6.0f
		&& Application::IsKeyPressed(VK_RBUTTON))
	{
		isTalkingToLady = true;
	}
	else if (RadiusFromLady > 6.0f)
	{
		isTalkingToLady = false;
	}

	if (RadiusFromDude < 6.0f
		&& Application::IsKeyPressed(VK_RBUTTON))
	{
		TalkedToQuestDude = true;
		isTalkingToQuestDude = true;
	}
	else if (RadiusFromDude > 6.0f)
	{
		isTalkingToQuestDude = false;
	}
	if (RadiusFromMiner < 6.0f
		&& TalkedToQuestDude == true
		&& Application::IsKeyPressed(VK_RBUTTON))
	{
		minergotLetter = true;
		playergetpickaxe = true;
		isTalkingToMinerType2 = true;
	}
	else if (RadiusFromMiner > 6.0f)
	{
		isTalkingToMinerType2 = false;
	}
	if (RadiusFromMiner < 6.0f
		&& TalkedToQuestDude == false
		&& Application::IsKeyPressed(VK_RBUTTON))
	{
		isTalkingToMinerType1 = true;
	}
	else if (RadiusFromMiner > 6.0f)
	{
		isTalkingToMinerType1 = false;
	}
}

void SceneMun::RenderPickaxeOnScreen()
{

	if (Application::IsKeyPressed(VK_LBUTTON) )
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
		modelStack.Translate(40, 15, -5);
		modelStack.Scale(6.5, 7.5, 6.5);
		//modelStack.Rotate(45, 0, 1, 0);
		//modelStack.Rotate(-45, 1, 0, 0);
		renderMesh(meshList[GEO_PICKAXE], true);
		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
	}
	else
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
		modelStack.Translate(60, 10, -5);
		modelStack.Scale(6.5, 6.5, 6.5);
		modelStack.Rotate(45, 0, 1, 0);
		//modelStack.Rotate(-45, 1, 0, 0);
		renderMesh(meshList[GEO_PICKAXE], true);
		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
	}
	
}

void SceneMun::RenderLoadingBarOnScreen()
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

void SceneMun::RenderOreOnScreen()
{
	if (!isRepairing && !isRepaired)
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
		modelStack.Translate(60, 10, -7);
		modelStack.Rotate(45, 0, 1, 0);
		modelStack.Rotate(45, 0, 0, 1);
		modelStack.Scale(15, 15, 15);
		renderMesh(meshList[GEO_ORE], true);
		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
	}
	else if (isRepairing)
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
		modelStack.Translate(40, 15, -7);
		modelStack.Rotate(45, 0, 1, 0);
		modelStack.Rotate(45, 0, 0, 1);
		modelStack.Scale(15, 15, 15);
		renderMesh(meshList[GEO_ORE], true);
		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
	}
}

void SceneMun::RenderTextBoxOnScreen()
{
	if (isTalkingToLady)
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
		modelStack.Translate(40, 10, -1);
		/*modelStack.Rotate(45, 0, 1, 0);
		modelStack.Rotate(45, 0, 0, 1);*/
		modelStack.Scale(45, 15, 1);
		modelStack.Rotate(90, 1, 0, 0);
		renderMesh(meshList[GEO_QUAD], true);
		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
		RenderTextOnScreen(meshList[GEO_TEXT], "Oh Lord! Are you okayyyyy?", Color(0, 0, 0), 3, 7, 4);
	}

	if (isTalkingToQuestDude)
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
		modelStack.Translate(40, 10, -1);
		/*modelStack.Rotate(45, 0, 1, 0);
		modelStack.Rotate(45, 0, 0, 1);*/
		modelStack.Scale(45, 15, 1);
		modelStack.Rotate(90, 1, 0, 0);
		renderMesh(meshList[GEO_QUAD], true);
		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
		RenderTextOnScreen(meshList[GEO_TEXT], "I see you need some materials", Color(0, 0, 0), 3, 6, 4);
		RenderTextOnScreen(meshList[GEO_TEXT], "to fix your ship. G ive this", Color(0, 0, 0), 3, 6, 3);
		RenderTextOnScreen(meshList[GEO_TEXT], "letter to the M iner near the", Color(0, 0, 0), 3, 6, 2);
		RenderTextOnScreen(meshList[GEO_TEXT], "Cave.", Color(0, 0, 0), 3, 6, 1);
	}
	if (isTalkingToMinerType1)
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
		modelStack.Translate(40, 10, -1);
		/*modelStack.Rotate(45, 0, 1, 0);
		modelStack.Rotate(45, 0, 0, 1);*/
		modelStack.Scale(45, 15, 1);
		modelStack.Rotate(90, 1, 0, 0);
		renderMesh(meshList[GEO_QUAD], true);
		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
		RenderTextOnScreen(meshList[GEO_TEXT], "Go Away, Im busy", Color(0, 0, 0), 3, 7, 4);
	}
	if (isTalkingToMinerType2)
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
		modelStack.Translate(40, 10, -1);
		/*modelStack.Rotate(45, 0, 1, 0);
		modelStack.Rotate(45, 0, 0, 1);*/
		modelStack.Scale(45, 15, 1);
		modelStack.Rotate(90, 1, 0, 0);
		renderMesh(meshList[GEO_QUAD], true);
		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
		RenderTextOnScreen(meshList[GEO_TEXT], "I see the chief wants me to", Color(0, 0, 0), 3, 6, 4);
		RenderTextOnScreen(meshList[GEO_TEXT], "help you, use my pickaxe to ", Color(0, 0, 0), 3, 6, 3);
		RenderTextOnScreen(meshList[GEO_TEXT], "mine your materials.", Color(0, 0, 0), 3, 6, 2);
	}
}

void SceneMun::RenderLetterOnScreen()
{
	if (TalkedToQuestDude && !minergotLetter)
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
		modelStack.Translate(60, 10, -5);
		modelStack.Scale(6.5, 6.5, 6.5);
		modelStack.Rotate(90, 1, 0, 0);
		//modelStack.Rotate(-45, 1, 0, 0);
		renderMesh(meshList[GEO_QUAD], true);
		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
	}
	
}

void SceneMun::RenderInfomationOnScreen()
{

}