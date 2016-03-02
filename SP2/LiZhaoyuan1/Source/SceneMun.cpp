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
#include "ReadTextFile.h"
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
	camera.Init(Vector3(-49, 0, -39), Vector3(-48, 0, -39), Vector3(0, 1, 0));
	camera.minimapcoords.y = 59.9f;
	camera.minimapcoords.x = 78.9f;
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("reference", Color(0, 1, 0));

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 0, 1));
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//Textbox.tga");
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
	meshList[GEO_MUNGROUND]->textureID = LoadTGA("Image//munFloorTexture.tga");

	//Objs -Xwing
	meshList[GEO_CRASHEDPLANE] = MeshBuilder::GenerateOBJ("crashedplane", "OBJ//XWingCrash.obj");
	meshList[GEO_CRASHEDPLANE]->textureID = LoadTGA("Image//XWingCrash_Texture.tga");
	meshList[GEO_CRASHEDPLANE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CRASHEDPLANE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CRASHEDPLANE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CRASHEDPLANE]->material.kShininess = 5.f;
	
	meshList[GEO_PLANE] = MeshBuilder::GenerateOBJ("plane", "OBJ//XWingLand.obj");
	meshList[GEO_PLANE]->textureID = LoadTGA("Image//XWing_Texture.tga");
	meshList[GEO_PLANE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_PLANE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_PLANE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_PLANE]->material.kShininess = 5.f;

	meshList[GEO_PLANE_TAKEOFF] = MeshBuilder::GenerateOBJ("planefortakeoff", "OBJ//XWing.obj");
	meshList[GEO_PLANE_TAKEOFF]->textureID = LoadTGA("Image//XWing_Texture.tga");
	meshList[GEO_PLANE_TAKEOFF]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_PLANE_TAKEOFF]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_PLANE_TAKEOFF]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_PLANE_TAKEOFF]->material.kShininess = 5.f;
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

	meshList[GEO_VILLAGER_BODY] = MeshBuilder::GenerateOBJ("body", "OBJ//HeadBody.obj");
	meshList[GEO_VILLAGER_BODY]->textureID = LoadTGA("Image//HumanCharacter.tga");
	meshList[GEO_VILLAGER_BODY]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_VILLAGER_BODY]->material.kDiffuse.Set(0, 0, 0);
	meshList[GEO_VILLAGER_BODY]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_VILLAGER_BODY]->material.kShininess = 1.f;
				
	meshList[GEO_VILLAGER_ARMLEFT] = MeshBuilder::GenerateOBJ("leftarm", "OBJ//LeftArm.obj");
	meshList[GEO_VILLAGER_ARMLEFT]->textureID = LoadTGA("Image//HumanCharacter.tga");
	meshList[GEO_VILLAGER_ARMLEFT]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_VILLAGER_ARMLEFT]->material.kDiffuse.Set(0, 0, 0);
	meshList[GEO_VILLAGER_ARMLEFT]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_VILLAGER_ARMLEFT]->material.kShininess = 1.f;
				 
	meshList[GEO_VILLAGER_ARMRIGHT] = MeshBuilder::GenerateOBJ("rightarm", "OBJ//RightArm.obj");
	meshList[GEO_VILLAGER_ARMRIGHT]->textureID = LoadTGA("Image//HumanCharacter.tga");
	meshList[GEO_VILLAGER_ARMRIGHT]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_VILLAGER_ARMRIGHT]->material.kDiffuse.Set(0, 0, 0);
	meshList[GEO_VILLAGER_ARMRIGHT]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_VILLAGER_ARMRIGHT]->material.kShininess = 1.f;
				 
	meshList[GEO_VILLAGER_LEGLEFT] = MeshBuilder::GenerateOBJ("leftleg", "OBJ//LeftLeg.obj");
	meshList[GEO_VILLAGER_LEGLEFT]->textureID = LoadTGA("Image//HumanCharacter.tga");
	meshList[GEO_VILLAGER_LEGLEFT]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_VILLAGER_LEGLEFT]->material.kDiffuse.Set(0, 0, 0);
	meshList[GEO_VILLAGER_LEGLEFT]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_VILLAGER_LEGLEFT]->material.kShininess = 1.f;
				 
	meshList[GEO_VILLAGER_LEGRIGHT] = MeshBuilder::GenerateOBJ("rightleg", "OBJ//RightLeg.obj");
	meshList[GEO_VILLAGER_LEGRIGHT]->textureID = LoadTGA("Image//HumanCharacter.tga");
	meshList[GEO_VILLAGER_LEGRIGHT]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_VILLAGER_LEGRIGHT]->material.kDiffuse.Set(0, 0, 0);
	meshList[GEO_VILLAGER_LEGRIGHT]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_VILLAGER_LEGRIGHT]->material.kShininess = 1.f;

	meshList[GEO_CRATE] = MeshBuilder::GenerateOBJ("crate", "OBJ//oreCube.obj");
	meshList[GEO_CRATE]->textureID = LoadTGA("Image//crate.tga");
	meshList[GEO_CRATE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CRATE]->material.kDiffuse.Set(0, 0, 0);
	meshList[GEO_CRATE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CRATE]->material.kShininess = 1.f;

	meshList[GEO_SNAKE] = MeshBuilder::GenerateOBJ("SolidSnake", "OBJ//CharacterModel.obj");
	meshList[GEO_SNAKE]->textureID = LoadTGA("Image//snake.tga");

	//Minimaps
	//meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("target", Color(1, 0, 0), 18, 36);

	meshList[GEO_MINIMAP] = MeshBuilder::GenerateQuad("Minimap", Color(1.f, 1.f, 1.f));
	meshList[GEO_MINIMAP]->textureID = LoadTGA("Image//Munmap.tga");
	
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//minecraft.tga");
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 18, 36);

	meshList[GEO_MAINICON] = MeshBuilder::GenerateCube("mainicon for map", Color(1, 0, 0));

	Mtx44 projection;
	projection.SetToPerspective(45.f, 16.f / 9.f, 0.1f, 10000.f);
	projectionStack.LoadMatrix(projection);

	camera.SceneGalaxy = false;
	camera.SceneMun = true;
	camera.SceneSoraJewel = false;

	ReadFromTxt("TextFiles//Worried_Lady.txt", TextLady);
	Ladypos = TextLady.begin();
	sWLady = *Ladypos;
	ssWLady << sWLady[0];

	ReadFromTxt("TextFiles//Quest_Dude.txt", TextQuestDude);
	QuestDudepos = TextQuestDude.begin();
	sQuestDude = *QuestDudepos;
	ssQuestDude << sQuestDude[0];

	ReadFromTxt("TextFiles//Miner1.txt", TextMiner);
	Minerpos = TextMiner.begin();
	sMiner = *Minerpos;
	ssMiner << sMiner[0];

	ReadFromTxt("TextFiles//Miner2.txt", TextMiner2);
	Minerpos2 = TextMiner2.begin();
	sMiner2 = *Minerpos2;
	ssMiner2 << sMiner2[0];

	a = 1;
	b = 1;
	c = 1;
	d = 1;

	textWL = false;
	textQD = false;
	textminer1 = false;
	textminer2 = false;

	interact = 0;


	crashedplaneCoord = Vector3(-36.f, 4.9f, -49.f);
	planecoord = Vector3(-36.f, -2.9f, -35.f);
	questdudehouseCoord = Vector3(33, -5, 20);
	worriedladyhouseCoord = Vector3(20, -5, -38);
	worriedladyCoord = Vector3(2, -4, -38);
	questdudeCoord = Vector3(33, -4, 3);
	minerandplusCoord = Vector3(-19, 0, 25);
	caveCoord = Vector3(-35, -5, 35);
	oreCoord = Vector3(-42, -2.75f, 35);
	CalefareACoord = Vector3(26, -0.9f, -21);
	CalefareBCoord = Vector3(26, -0.9f, -10);
	CalefareCCoord = Vector3(15, -0.9f, 25);
	
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

	rotateAngle = 0;
	Allcaptured = false;
	translatingChar = 0;
	hoverheight = 0;
	rotateplane = 0;
	translateplane = 0;
	thisisastring << "fulton left: ";
	fultonleft = 6;
	thisisastring << fultonleft;
}

void SceneMun::Update(double dt)
{
	if ((((interact >> REPAIRED) & 1) < 1))
	{
		camera.Update(dt, 50);
	}
	if ((((interact >> REPAIRED) & 1) > 0))
	{
		camera.Init(Vector3(15, 10, 45), Vector3(-35, 0, -40), Vector3(0, 1, 0));
	}
	if (Allcaptured == true)
	{
		camera.Init(Vector3(15, 10, 45), Vector3(-35, 0, -40), Vector3(0, 1, 0));
	}

	if (((((interact >> TALKING_TO_LADY) & 1) > 0)) && textWL)
	{
		timing += (float)(10 * dt);
		if (timing >= 0.5f)
		{
			if (a < sWLady.size())
			{
				ssWLady << sWLady[a];
				a++;
				timing = 0;
			}
			else if (a == sWLady.size() && Application::IsKeyPressed(VK_LBUTTON))
			{
				if (Ladypos != TextLady.end())
				{
					ssWLady.str("");
					sWLady = "";

					sWLady = *Ladypos;
					ssWLady << sWLady[0];

					timing = 0;
					a = 1;
					Ladypos++;
				}
				else
				{
					if (Application::IsKeyPressed(VK_LBUTTON))
					{
						ssWLady.str("");
						textWL = false;
						Ladypos = TextLady.begin();
						sWLady = *Ladypos;
						ssWLady << sWLady[0];
						a = 1;
					}
				}
			}
		}
	}
	else
	{
		ssWLady.str("");
		Ladypos = TextLady.begin();
		sWLady = *Ladypos;
		ssWLady << sWLady[0];
		a = 1;
	}

	if (((((interact >> TALKING_TO_QUEST_DUDE) & 1) > 0)) && textQD)
	{
		timing += (float)(10 * dt);
		if (timing >= 0.5f)
		{
			if (b < sQuestDude.size())
			{
				ssQuestDude << sQuestDude[b];
				b++;
				timing = 0;
			}
			else if (b == sQuestDude.size() && Application::IsKeyPressed(VK_LBUTTON))
			{
				if (QuestDudepos != TextQuestDude.end())
				{
					ssQuestDude.str("");
					sQuestDude = "";

					sQuestDude = *QuestDudepos;
					ssQuestDude << sQuestDude[0];

					timing = 0;
					b = 1;
					QuestDudepos++;
				}
				else
				{
					if (Application::IsKeyPressed(VK_LBUTTON))
					{
						ssQuestDude.str("");
						textQD = false;
						QuestDudepos = TextQuestDude.begin();
						sQuestDude = *QuestDudepos;
						ssQuestDude << sQuestDude[0];
						b = 1;
					}
				}
			}
		}
	}
	else
	{
		ssQuestDude.str("");
		QuestDudepos = TextQuestDude.begin();
		sQuestDude = *QuestDudepos;
		ssQuestDude << sQuestDude[0];
		b = 1;
	}

	if (((((interact >> TALKING_TO_MINER_CASE_1) & 1) > 0)) && textminer1)
	{
		timing += (float)(10 * dt);
		if (timing >= 0.5f)
		{
			if (c < sMiner.size())
			{
				ssMiner << sMiner[c];
				c++;
				timing = 0;
			}
			else if (c == sMiner.size() && Application::IsKeyPressed(VK_LBUTTON))
			{
				if (Minerpos != TextMiner.end())
				{
					ssMiner.str("");
					sMiner = "";

					sMiner = *Minerpos;
					ssMiner << sMiner[0];

					timing = 0;
					c = 1;
					Minerpos++;
				}
				else
				{
					if (Application::IsKeyPressed(VK_LBUTTON))
					{
						ssMiner.str("");
						textminer1 = false;
						Minerpos = TextMiner.begin();
						sMiner = *Minerpos;
						ssMiner << sMiner[0];
						c = 1;
					}
				}
			}
		}
	}
	else
	{
		ssMiner.str("");
		Minerpos = TextMiner.begin();
		sMiner = *Minerpos;
		ssMiner << sMiner[0];
		c = 1;
	}

	if (((((interact >> TALKING_TO_MINER_CASE_2) & 1) > 0)) && textminer2)
	{
		timing += (float)(10 * dt);
		if (timing >= 0.5f)
		{
			if (d < sMiner2.size())
			{
				ssMiner2 << sMiner2[d];
				d++;
				timing = 0;
			}
			else if (d == sMiner2.size() && Application::IsKeyPressed(VK_LBUTTON))
			{
				if (Minerpos2 != TextMiner2.end())
				{
					ssMiner2.str("");
					sMiner2 = "";

					sMiner2 = *Minerpos2;
					ssMiner2 << sMiner2[0];

					timing = 0;
					d = 1;
					Minerpos2++;
				}
				else
				{
					if (Application::IsKeyPressed(VK_LBUTTON))
					{
						ssMiner2.str("");
						textminer2 = false;
						Minerpos2 = TextMiner2.begin();
						sMiner2 = *Minerpos2;
						ssMiner2 << sMiner2[0];
						d = 1;
					}
				}
			}
		}
	}
	else
	{
		ssMiner2.str("");
		Minerpos2 = TextMiner2.begin();
		sMiner2 = *Minerpos2;
		ssMiner2 << sMiner2[0];
		d = 1;
	}

	fps = (int)(1 / dt);


	camPosX = (int)camera.position.x;
	camPosY = (int)camera.position.y;
	camPosz = (int)camera.position.z;
	
	if (((((interact >> MINING) & 1) > 0) || (((interact >> REPAIRING) & 1) > 0)) && (loadingbar <= 20))
	{
		loadingbar += (float)(5 * dt);
	}
	else if ((((interact >> MINING) & 1) > 0) && (loadingbar >= 20))
	{
		interact |= 1 << MINED;
	}
	else if ((((interact >> REPAIRING) & 1) > 0) && (loadingbar >= 20))
	{
		interact |= 1 << REPAIRED;
	}
	else
	{
		loadingbar = 0.01f;
	}

	static int rotateDir = 1;
	static int rotateDirLimb = 1;
	static int translateDir = 1;
	if (rotateAngle * rotateDir > 30)
	{
		rotateDir = -rotateDir;
	}
	rotateAngle += (float)(rotateDir * 100 * dt);

	if (rotateLimbs * rotateDirLimb > 30)
	{
		rotateDirLimb = -rotateDirLimb;
	}
	rotateLimbs += (float)(rotateDirLimb * 25 * dt);

	if (translatingChar * translateDir > 10)
	{
		translateDir = -translateDir;
		if (rotateWhole == 0)
		{
			rotateWhole = 180;
		}
		else if (rotateWhole == 180)
		{
			rotateWhole = 0;
		}
	}
	translatingChar += (float)(translateDir * 2.5 * dt);

	if (hoverheight < 5 && (((interact >> REPAIRED) & 1) > 0))
	{
		hoverheight += (float)(2.f * dt);
	}
	else if (hoverheight >= 5 && (((interact >> REPAIRED) & 1) > 0) && rotateplane < 180)
	{
		rotateplane += (float)(50.f * dt);
	}
	else if (rotateplane >= 180)
	{
		translateplane += (float)(100.f * dt);
	}
	if (translateplane >= 50)
	{
		Gamemode::getinstance()->currentgamestate = 1;
	}

	TranslateCalefareA = (translatingChar, 0.f, 0.f);
	TranslateCalefareB = (translatingChar, 0.f, 0.f);;
	TranslateCalefareC = (0.f , 0.f, translatingChar);
	npcRotate();
	interactions();
	camera.target;
	if ((LadyCaptured == true)&& (CaptureLadyCap==0))
	{
		
		fultonleft -= 1;
		CaptureLadyCap += 1;
		thisisastring.seekp(-1, thisisastring.cur);
		thisisastring << fultonleft;

	}
	if ((VillageChiefCaptured == true) && (CaptureVChiefCap == 0))
	{

		fultonleft -= 1;
		CaptureVChiefCap += 1;
		thisisastring.seekp(-1, thisisastring.cur);
		thisisastring << fultonleft;

	}
	if ((MinerCaptured == true) && (CaptureMinerCap == 0))
	{

		fultonleft -= 1;
		CaptureMinerCap += 1;
		thisisastring.seekp(-1, thisisastring.cur);
		thisisastring << fultonleft;

	}
	if ((CalefareACaptured == true) && (CalefareACap == 0))
	{

		fultonleft -= 1;
		CalefareACap += 1;
		thisisastring.seekp(-1, thisisastring.cur);
		thisisastring << fultonleft;

	}
	if ((CalefareCCaptured == true) && (CalefareCCap == 0))
	{

		fultonleft -= 1;
		CalefareCCap += 1;
		thisisastring.seekp(-1, thisisastring.cur);
		thisisastring << fultonleft;

	}
	if ((CalefareBCaptured == true) && (CalefareBCap == 0))
	{

		fultonleft -= 1;
		CalefareBCap += 1;
		thisisastring.seekp(-1, thisisastring.cur);
		thisisastring << fultonleft;

	}
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
	//modelStack.Translate(0, 496.9, 0);
	modelStack.Rotate(180, 1, 0, 0);
	RenderSkybox();
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
	modelStack.Translate(worriedladyCoord.x, worriedladyCoord.y + 9, worriedladyCoord.z);
	modelStack.Scale(0.5f, 0.5f, 0.5f);
	renderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(questdudeCoord.x, questdudeCoord.y + 9, questdudeCoord.z);
	modelStack.Scale(0.5f, 0.5f, 0.5f);
	renderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(minerandplusCoord.x, minerandplusCoord.y + 7, minerandplusCoord.z);
	modelStack.Scale(0.5f, 0.5f, 0.5f);
	renderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -5, 0);
	modelStack.Scale(100, 100, 100);
	renderMesh(meshList[GEO_MUNGROUND], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(SNAKEcoords.x, SNAKEcoords.y, SNAKEcoords.z);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1.f, 1.f, 1.f);
	renderMesh(meshList[GEO_SNAKE], false);
	modelStack.PopMatrix();

	if ((((interact >> REPAIRED) & 1) < 1))
	{
		modelStack.PushMatrix();
		modelStack.Translate(crashedplaneCoord.x, crashedplaneCoord.y, crashedplaneCoord.z);
		modelStack.Scale(2.2f, 2.2f, 2.2f);
		renderMesh(meshList[GEO_CRASHEDPLANE], true);
		modelStack.PopMatrix();
	}
	if ((Allcaptured == true))
	{
		interact |= 1 << REPAIRED;
	}
	if ((((interact >> REPAIRED) & 1) > 0))
	{
		modelStack.PushMatrix();
		modelStack.Translate(planecoord.x, planecoord.y + hoverheight, planecoord.z - translateplane);
		modelStack.Scale(2.2f, 2.2f, 2.2f);
		modelStack.Rotate(rotateplane, 0, 1, 0);
		renderMesh(meshList[GEO_PLANE_TAKEOFF], true);
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
	renderMesh(meshList[GEO_CAVE], true);
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
	modelStack.Translate(CalefareACoord.x, CalefareACoord.y, CalefareACoord.z);
	modelStack.Translate(translatingChar, 0, 0);
	modelStack.Rotate(rotateWhole, 0, 1, 0);
	RenderCalefare();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(CalefareBCoord.x, CalefareBCoord.y, CalefareBCoord.z);
	modelStack.Translate(-translatingChar, 0, 0);
	modelStack.Rotate(rotateWhole-180, 0, 1, 0);
	RenderCalefare();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(CalefareCCoord.x, CalefareCCoord.y, CalefareCCoord.z);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Translate(translatingChar, 0, 0);
	modelStack.Rotate(rotateWhole, 0, 1, 0);
	RenderCalefare();
	modelStack.PopMatrix();
	

	modelStack.PushMatrix();
	modelStack.Translate(minerandplusCoord.x, minerandplusCoord.y, minerandplusCoord.z);
	modelStack.Rotate(rotateminer, 0, 1, 0);
	modelStack.PushMatrix();
	modelStack.Translate(0, -5.5, 0);
	renderMesh(meshList[GEO_ALIEN], true);
	modelStack.PopMatrix();
	if ((((interact >> PLAYER_GET_PICKAXE) & 1) < 1))
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
	if ((((interact >> MINED) & 1) < 1))
	{
		modelStack.PushMatrix();
		modelStack.Translate(oreCoord.x, oreCoord.y, oreCoord.z);
		modelStack.Scale(2, 2, 2);
		renderMesh(meshList[GEO_ORE], true);
		modelStack.PopMatrix();
	}
	if ((((interact >> MINED) & 1) > 0))
	{
		RenderOreOnScreen();
	}

	modelStack.PushMatrix();
	modelStack.Translate(camera.target.x, camera.target.y, camera.target.z);
	modelStack.Scale(0.01f, 0.01f, 0.01f);
	renderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	if ((((interact >> MINED) & 1) < 1) && (((interact >> PLAYER_GET_PICKAXE) & 1) > 0))
	{
		RenderPickaxeOnScreen();
	}
	RenderLetterOnScreen();
	Renderpicturetoscreen();
	if ((((interact >> MINING) & 1) > 0))
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "M ining", Color(0, 1, 0), 3, 11, 15);
		RenderLoadingBarOnScreen();

	}
	if ((((interact >> REPAIRING) & 1) > 0) && (((interact >> MINED) & 1) > 0))
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Repairing", Color(0, 1, 0), 3, 11, 15);
		RenderLoadingBarOnScreen();
	}
	RenderTextBoxOnScreen();
	RenderInfomationOnScreen();
	fultoninteraction();
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
	tempview = (camera.target - camera.position);
	viewAtOre = (oreCoord - camera.position);
	viewAtLady = (worriedladyCoord - camera.position);
	viewAtDude = (questdudeCoord - camera.position);
	viewAtMiner = (minerandplusCoord - camera.position);
	viewAtCrashedPlane = (crashedplaneCoord - camera.position);
	viewatSNAKE = (SNAKEcoords - camera.position);
	viewatCalefareA = (CalefareACoord + TranslateCalefareA - camera.position);
	viewatCalefareB = (CalefareBCoord + TranslateCalefareB - camera.position);
	viewatCalefareC = (CalefareCCoord + TranslateCalefareC - camera.position);
	RadiusFromOre = (viewAtOre - tempview).Length();
	RadiusFromLady = (viewAtLady - tempview).Length();
	RadiusFromDude = (viewAtDude - tempview).Length();
	RadiusFromMiner = (viewAtMiner - tempview).Length();
	RadiusFromCrashedPlane = (viewAtCrashedPlane - tempview).Length();
	RadiusFromSnake = (viewatSNAKE-tempview).Length();
	// Add Calafare Radius Here  translatingChar-> this is the movement
	RadiusFromCalafareA = (viewatCalefareA - tempview).Length();
	RadiusFromCalafareB = (viewatCalefareB - tempview).Length();
	RadiusFromCalafareC = (viewatCalefareC - tempview).Length();
	if ((RadiusFromOre < 2.5f && (((interact >> MINED) & 1) < 1) && (((interact >> PLAYER_GET_PICKAXE) & 1) > 0))
		|| (RadiusFromCrashedPlane < 7.5f && (((interact >> REPAIRED) & 1) < 1))
		|| RadiusFromLady < 6.0f
		|| RadiusFromDude < 6.0f
		|| (RadiusFromMiner < 6.0f && (((interact >> TALKED_QUEST_DUDE) & 1) > 0))
		|| (RadiusFromMiner < 6.0f && (((interact >> TALKED_QUEST_DUDE) & 1) < 1)))
	{
		interact |= 1 << CAN_INTERACT;
	}
	else
	{
		interact &= ~(1 << CAN_INTERACT);
	}
	if (RadiusFromOre < 2.5f
		&& (((interact >> PLAYER_GET_PICKAXE) & 1) > 0)
		&& Application::IsKeyPressed(('E'))
		&& (((interact >> MINED) & 1) < 1))
	{
		interact |= 1 << MINING;
	}
	else
	{
		interact &= ~(1 << MINING);
	}

	if (RadiusFromCrashedPlane < 7.5f
		&& Application::IsKeyPressed('E')
		&& (((interact >> REPAIRED) & 1) < 1))
	{
		interact |= 1 << REPAIRING;
	}
	else
	{
		interact &= ~(1 << REPAIRING);
	}

	if (RadiusFromLady < 6.0f
		&& Application::IsKeyPressed('E'))
	{
		interact |= 1 << TALKING_TO_LADY;
		textWL = true;
		fultonleft - 1;
	}
	else if (RadiusFromLady > 6.0f)
	{
		interact &= ~(1 << TALKING_TO_LADY);
		textWL = false;
	}
	else if ((RadiusFromLady < 6.0f) && (fultonreceived == true) && (fultonleft>0) &&(LadyCaptured==false)&&(Application::IsKeyPressed('Q')))
	{
		LadyCaptured =true;

	}

	if (RadiusFromDude < 6.0f
		&& Application::IsKeyPressed('E'))
	{
		interact |= 1 << TALKED_QUEST_DUDE;
		interact |= 1 << TALKING_TO_QUEST_DUDE;
		textQD = true;
	}
	else if (RadiusFromDude > 6.0f)
	{
		interact &= ~(1 << TALKING_TO_QUEST_DUDE);
		textQD = false;
	}
	else if ((RadiusFromDude < 6.0f) && (fultonreceived == true) && (fultonleft>0) && (VillageChiefCaptured == false) && (Application::IsKeyPressed('Q')))
	{
		VillageChiefCaptured = true;
	}
	if (RadiusFromMiner < 6.0f
		&& (((interact >> TALKED_QUEST_DUDE) & 1) > 0)
		&& Application::IsKeyPressed('E'))
	{
		interact |= 1 << MINER_GET_LETTER;
		interact |= 1 << PLAYER_GET_PICKAXE;
		interact |= 1 << TALKING_TO_MINER_CASE_2;
		textminer2 = true;
	}
	else if (RadiusFromMiner > 6.0f)
	{
		interact &= ~(1 << TALKING_TO_MINER_CASE_2);
		textminer2 = false;
	}
	if (RadiusFromMiner < 6.0f
		&& (((interact >> TALKED_QUEST_DUDE) & 1)< 1)
		&& Application::IsKeyPressed('E'))
	{
		interact |= 1 << TALKING_TO_MINER_CASE_1;
		textminer1 = true;
	}
	else if (RadiusFromMiner > 6.0f)
	{
		interact &= ~(1 << TALKING_TO_MINER_CASE_1);
		textminer1 = false;
	}
	else if ((RadiusFromMiner < 6.0f) && (fultonreceived == true) && (fultonleft>0) && (MinerCaptured == false) && (Application::IsKeyPressed('Q')))
	{
		MinerCaptured = true;
	}
	if ((RadiusFromCalafareA < 10.0f) && (fultonreceived == true) && (fultonleft>0) && (CalefareACaptured == false) && (Application::IsKeyPressed('Q')))
	{
		CalefareACaptured = true;
	}
	if ((RadiusFromCalafareB < 10.0f) && (fultonreceived == true) && (fultonleft>0) && (CalefareBCaptured == false) && (Application::IsKeyPressed('Q')))
	{
		CalefareBCaptured = true;
	}
	if ((RadiusFromCalafareC < 10.0f) && (fultonreceived == true) && (fultonleft>0) && (CalefareCCaptured == false) && (Application::IsKeyPressed('Q')))
	{
		CalefareCCaptured = true;
	}

	if (RadiusFromSnake < 6.0f
		&& Application::IsKeyPressed('E'))
	{
		interact |= 1 << TALKING_TO_SNAKE;
		fultonreceived = true;
	}
	else if (RadiusFromSnake > 6.0f)
	{
		interact &= ~(1 << TALKING_TO_SNAKE);
	}
}
void SceneMun::fultoninteraction()
{
	if (fultonreceived == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], thisisastring.str() , Color(0, 0, 0), 2, 1, 18);
		RenderTextOnScreen(meshList[GEO_TEXT], "Captured", Color(0, 0, 0), 2, 1, 16);
		if (LadyCaptured == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Lady", Color(0, 0, 0), 2, 1, 15);
		}
		if (VillageChiefCaptured == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Village Chief", Color(0, 0, 0), 2, 1, 14);
		}
		if (MinerCaptured == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Miner", Color(0, 0, 0), 2, 1, 13);
		}
		if (CalefareACaptured == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Worker No.1", Color(0, 0, 0), 2, 1, 12);
		}
		if (CalefareBCaptured == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Worker No.2", Color(0, 0, 0), 2, 1, 11);
		}
		if (CalefareCCaptured == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Worker No.3", Color(0, 0, 0), 2, 1, 10);
		}
		if ((LadyCaptured == true) && (VillageChiefCaptured == true) && (MinerCaptured == true) && (CalefareACaptured == true) && (CalefareBCaptured == true) && (CalefareCCaptured == true))
		{
			Allcaptured = true;
			if (Allcaptured == true)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], "All Captured", Color(0, 0, 0), 2, 1, 9);
			}
		}
	}

}
void SceneMun::RenderPickaxeOnScreen()
{

	if (Application::IsKeyPressed('E') )
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
		modelStack.Rotate(rotateAngle, 0, 0, 1);
		modelStack.Scale(6.5, 6.5, 6.5);
		modelStack.Rotate(-90, 0, 1, 0);
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
		//modelStack.Rotate(rotateAngle, 0, 0.5, 0.5);
		modelStack.Translate(60, 10, -5);
		modelStack.Scale(6.5, 6.5, 6.5);
		modelStack.Rotate(90, 0, 1, 0);
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
	if ((((interact >> REPAIRING) & 1) < 1) && (((interact >> REPAIRED) & 1) < 1))
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
	else if (((((interact >> REPAIRING) & 1) > 0)))
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
		modelStack.Rotate(rotateAngle, 1, 0, 0);
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
	if (((((interact >> TALKING_TO_LADY) & 1) > 0)))
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
		modelStack.Scale(60, 60, 1);
		modelStack.Rotate(90, 1, 0, 0);
		renderMesh(meshList[GEO_QUAD], false);
		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
		RenderTextOnScreen(meshList[GEO_TEXT], ssWLady.str(), Color(0, 0, 0), 3, 7, 4);
	}

	if (((((interact >> TALKING_TO_QUEST_DUDE) & 1) > 0)))
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
		modelStack.Scale(60, 60, 1);
		modelStack.Rotate(90, 1, 0, 0);
		renderMesh(meshList[GEO_QUAD], false);
		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
		RenderTextOnScreen(meshList[GEO_TEXT], ssQuestDude.str(), Color(0, 0, 0), 3, 6, 4);
	}
	if (((((interact >> TALKING_TO_MINER_CASE_1) & 1) > 0)))
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
		modelStack.Scale(60, 60, 1);
		modelStack.Rotate(90, 1, 0, 0);
		renderMesh(meshList[GEO_QUAD], false);
		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
		RenderTextOnScreen(meshList[GEO_TEXT], ssMiner.str(), Color(0, 0, 0), 3, 7, 4);
	}
	if (((((interact >> TALKING_TO_MINER_CASE_2) & 1) > 0)))
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
		modelStack.Scale(60, 60, 1);
		modelStack.Rotate(90, 1, 0, 0);
		renderMesh(meshList[GEO_QUAD], false);
		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
		RenderTextOnScreen(meshList[GEO_TEXT], ssMiner2.str(), Color(0, 0, 0), 3, 6, 4);
	}

	if (((((interact >> TALKING_TO_SNAKE) & 1) > 0)))
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
		modelStack.Scale(60, 60, 1);
		modelStack.Rotate(90, 1, 0, 0);
		renderMesh(meshList[GEO_QUAD], false);
		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
		RenderTextOnScreen(meshList[GEO_TEXT], "Here is some Fulton Extraction Ballons", Color(0, 0, 0), 2, 6, 4);
		RenderTextOnScreen(meshList[GEO_TEXT], "Extract All the villagers for better rewards", Color(0, 0, 0), 2, 6, 2);
	}
}

void SceneMun::RenderLetterOnScreen()
{
	if ((((interact >> TALKED_QUEST_DUDE) & 1) > 0) && (((interact >> MINER_GET_LETTER) & 1) < 1))
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
		modelStack.Translate(70, 10, -5);
		modelStack.Scale(6.5, 6.5, 6.5);
		modelStack.Rotate(90, 1, 0, 0);
		//modelStack.Rotate(-45, 1, 0, 0);
		renderMesh(meshList[GEO_QUAD], true);
		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
		RenderTextOnScreen(meshList[GEO_TEXT], "Letter", Color(1, 0, 0), 2, 33.5, 5);
	}
	
}

void SceneMun::RenderInfomationOnScreen()
{
	if ((((interact >> REPAIRED) & 1) > 0))
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
		modelStack.Scale(60, 60, 1);
		modelStack.Rotate(90, 1, 0, 0);
		renderMesh(meshList[GEO_QUAD], false);
		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
		RenderTextOnScreen(meshList[GEO_TEXT], "Your plane is Fixed! You can", Color(0, 0, 0), 3, 6, 5);
		RenderTextOnScreen(meshList[GEO_TEXT], "continue with your journey.", Color(0, 0, 0), 3, 6, 4);
		RenderTextOnScreen(meshList[GEO_TEXT], "THE END", Color(0, 0, 0), 3, 6, 3);
	}

	if (Allcaptured==true)
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
		modelStack.Scale(60, 60, 1);
		modelStack.Rotate(90, 1, 0, 0);
		renderMesh(meshList[GEO_QUAD], false);
		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);              //                            //
		RenderTextOnScreen(meshList[GEO_TEXT], "You Captured All the Villagers!", Color(0, 0, 0), 3, 6, 5);
		RenderTextOnScreen(meshList[GEO_TEXT], "You Forced them to repair your ship.", Color(0, 0, 0), 3, 6, 4);
		RenderTextOnScreen(meshList[GEO_TEXT], "THE END", Color(0, 0, 0), 3, 6, 3);
	}

	if ((((interact >> CAN_INTERACT) & 1) > 0))
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to interact", Color(0, 1, 0), 3, 8, 17);
	}
	RenderTextOnScreen(meshList[GEO_TEXT], "WASD to move", Color(0, 1, 0), 1, 65, 49);
	RenderTextOnScreen(meshList[GEO_TEXT], "Mouse to move Camera", Color(0, 1, 0), 1, 65, 48);
	RenderTextOnScreen(meshList[GEO_TEXT], "E to interact when available", Color(0, 1, 0), 1, 65, 47);
	RenderTextOnScreen(meshList[GEO_TEXT], "Left click when textbox appear", Color(0, 1, 0), 1, 65, 46);
	std::stringstream playerPos;
	playerPos << "X = " << camPosX << " Y = " << camPosY << " Z = " << camPosz;
	//RenderTextOnScreen(meshList[GEO_TEXT], playerPos.str(), Color(1, 0, 0), 2, 0, 18);
	std::stringstream ss;
	ss << "FPS:" << fps << "         " << playerPos.str();
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 19);
}

void SceneMun::RenderCalefare()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, -4.62f, 0);
	renderMesh(meshList[GEO_VILLAGER_BODY], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 0, 1);
	renderMesh(meshList[GEO_VILLAGER_ARMLEFT], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 0, 1);
	renderMesh(meshList[GEO_VILLAGER_ARMRIGHT], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -2.1f, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(-rotateLimbs, 0, 0, 1);
	renderMesh(meshList[GEO_VILLAGER_LEGLEFT], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(rotateLimbs, 0, 0, 1);
	renderMesh(meshList[GEO_VILLAGER_LEGRIGHT], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(2, 0, 0);
	modelStack.Scale(2, 2, 2);
	renderMesh(meshList[GEO_CRATE], true);
	modelStack.PopMatrix();
}

void SceneMun::RenderSceneOBJ()
{

}