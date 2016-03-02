#include <sstream>
#include <iostream>
#include "SceneSoraJewel.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"
#include "Light.h"
#include "Material.h"
#include "Utility.h"
#include "Physics.h"

#include "LoadTGA.h"
#include "ReadTextFile.h"

SceneSoraJewel::SceneSoraJewel()
{
}
SceneSoraJewel::~SceneSoraJewel()
{
}
void SceneSoraJewel::Init()
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

	m_parameters[U_LIGHT2_POSITION] = glGetUniformLocation(m_programID, "lights[2].position_cameraspace");
	m_parameters[U_LIGHT2_COLOR] = glGetUniformLocation(m_programID, "lights[2].color");
	m_parameters[U_LIGHT2_POWER] = glGetUniformLocation(m_programID, "lights[2].power");
	m_parameters[U_LIGHT2_KC] = glGetUniformLocation(m_programID, "lights[2].kC");
	m_parameters[U_LIGHT2_KL] = glGetUniformLocation(m_programID, "lights[2].kL");
	m_parameters[U_LIGHT2_KQ] = glGetUniformLocation(m_programID, "lights[2].kQ");
	m_parameters[U_LIGHT2_TYPE] = glGetUniformLocation(m_programID, "lights[2].type");
	m_parameters[U_LIGHT2_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[2].spotDirection");
	m_parameters[U_LIGHT2_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[2].cosCutoff");
	m_parameters[U_LIGHT2_COSINNER] = glGetUniformLocation(m_programID, "lights[2].cosInner");
	m_parameters[U_LIGHT2_EXPONENT] = glGetUniformLocation(m_programID, "lights[2].exponent");

	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");


	glUseProgram(m_programID);

	glUniform1i(m_parameters[U_NUMLIGHTS], 3);

	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(0, 80, 5);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1.5f;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	light[1].type = Light::LIGHT_POINT;
	light[1].position.Set(25, 45, -53);
	light[1].color.Set(1, 1, 1);
	light[1].power = 1.f;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);

	light[2].type = Light::LIGHT_POINT;
	light[2].position.Set(-25, -10, 53);
	light[2].color.Set(1, 1, 1);
	light[2].power = 1.f;
	light[2].kC = 1.f;
	light[2].kL = 0.01f;
	light[2].kQ = 0.001f;
	light[2].cosCutoff = cos(Math::DegreeToRadian(45));
	light[2].cosInner = cos(Math::DegreeToRadian(30));
	light[2].exponent = 3.f;
	light[2].spotDirection.Set(0.f, 1.f, 0.f);

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

	glUniform1i(m_parameters[U_LIGHT2_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT2_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT2_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT2_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT2_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT2_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT2_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT2_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT2_EXPONENT], light[1].exponent);
	
	//Initialize camera settings

	camera.Init(Vector3(0, 5, 50), Vector3(0, 5, 0), Vector3(0, 1, 0));

	//camera.Init(Vector3(0, 350, 1), Vector3(0, 7, 0), Vector3(0, 1, 0));

	camera.minimapsoracoords.x = 78.f; //
	camera.minimapsoracoords.y = 55.f; //

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_MINIMAPSJ] = MeshBuilder::GenerateQuad("Minimap for Sora Jewel", Color(1, 1, 1));
	meshList[GEO_MINIMAPSJ]->textureID = LoadTGA("Image//SoraJewelMapNew.tga");

	meshList[GEO_MAINICONSJ] = MeshBuilder::GenerateQuad("front", Color(0.f, 1.f, 0.f));

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 0, 1));
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//Textbox.tga");

	meshList[GEO_SORAJEWELFRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1));
	meshList[GEO_SORAJEWELFRONT]->textureID = LoadTGA("Image//SoraJewelFront.tga");
	meshList[GEO_SORAJEWELBACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1));
	meshList[GEO_SORAJEWELBACK]->textureID = LoadTGA("Image//SoraJewelBack.tga");
	meshList[GEO_SORAJEWELTOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1));
	meshList[GEO_SORAJEWELTOP]->textureID = LoadTGA("Image//SoraJewelUp.tga");
	meshList[GEO_SORAJEWELBOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1));
	meshList[GEO_SORAJEWELBOTTOM]->textureID = LoadTGA("Image//SoraJewelDown.tga");
	meshList[GEO_SORAJEWELLEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1));
	meshList[GEO_SORAJEWELLEFT]->textureID = LoadTGA("Image//SoraJewelLeft.tga");
	meshList[GEO_SORAJEWELRIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1));
	meshList[GEO_SORAJEWELRIGHT]->textureID = LoadTGA("Image//SoraJewelRight.tga");

	meshList[GEO_SORAJEWEL] = MeshBuilder::GenerateOBJ("BASE", "OBJ//SoraJewelBase_Kaiii.obj");
	meshList[GEO_SORAJEWEL]->textureID = LoadTGA("Image//SoraJewelBase_Texture.tga");
	meshList[GEO_SORAJEWEL]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SORAJEWEL]->material.kDiffuse.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SORAJEWEL]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SORAJEWEL]->material.kShininess = 1.f;

	meshList[GEO_XWING] = MeshBuilder::GenerateOBJ("BASE", "OBJ//XWingLand.obj");
	meshList[GEO_XWING]->textureID = LoadTGA("Image//XWing_Texture.tga");
	meshList[GEO_XWING]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_XWING]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_XWING]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_XWING]->material.kShininess = 1.f;

	meshList[GEO_GLASS] = MeshBuilder::GenerateOBJ("Glass", "OBJ//glass.obj");
	meshList[GEO_GLASS]->textureID = LoadTGA("Image//Glass.tga");
	meshList[GEO_GLASS]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_GLASS]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_GLASS]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_GLASS]->material.kShininess = 1.f;

	meshList[GEO_KEG] = MeshBuilder::GenerateOBJ("Glass", "OBJ//Keg.obj");
	meshList[GEO_KEG]->textureID = LoadTGA("Image//Keg_Texture.tga");
	meshList[GEO_KEG]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_KEG]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_KEG]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_KEG]->material.kShininess = 1.f;

	meshList[GEO_BEEREMPTY] = MeshBuilder::GenerateOBJ("Glass", "OBJ//Beer_Empty.obj");
	meshList[GEO_BEEREMPTY]->textureID = LoadTGA("Image//Beer_Empty_Texture.tga");
	meshList[GEO_BEEREMPTY]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BEEREMPTY]->material.kDiffuse.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BEEREMPTY]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BEEREMPTY]->material.kShininess = 0.5f;

	meshList[GEO_BEERFULL] = MeshBuilder::GenerateOBJ("Glass", "OBJ//Beer.obj");
	meshList[GEO_BEERFULL]->textureID = LoadTGA("Image//Beer_Full_Texture.tga");
	meshList[GEO_BEERFULL]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BEERFULL]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BEERFULL]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BEERFULL]->material.kShininess = 0.5f;

	meshList[GEO_GLOBE] = MeshBuilder::GenerateOBJ("Globe", "OBJ//earth.obj");
	meshList[GEO_GLOBE]->textureID = LoadTGA("Image//hologram_earth.tga");
	meshList[GEO_GLOBE]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_GLOBE]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_GLOBE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_GLOBE]->material.kShininess = 1.f;

	meshList[GEO_SOFA] = MeshBuilder::GenerateOBJ("Sofa", "OBJ//sofa_kaii.obj");
	meshList[GEO_SOFA]->textureID = LoadTGA("Image//Sofa_Texture.tga");
	meshList[GEO_SOFA]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_SOFA]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SOFA]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SOFA]->material.kShininess = 0.5f;

	meshList[GEO_PROJECTOR] = MeshBuilder::GenerateOBJ("projector", "OBJ//earth_base.obj");
	meshList[GEO_PROJECTOR]->textureID = LoadTGA("Image//hologram_base.tga");
	meshList[GEO_PROJECTOR]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_PROJECTOR]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_PROJECTOR]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_PROJECTOR]->material.kShininess = 1.f;

	meshList[GEO_COUNTER] = MeshBuilder::GenerateOBJ("Counter", "OBJ//Counter.obj");
	meshList[GEO_COUNTER]->textureID = LoadTGA("Image//hologram_base.tga");
	meshList[GEO_COUNTER]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_COUNTER]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_COUNTER]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_COUNTER]->material.kShininess = 1.f;

	//Characters
	meshList[GEO_QUESTLADY] = MeshBuilder::GenerateOBJ("quest lady", "OBJ//CharacterModel.obj");
	meshList[GEO_QUESTLADY]->textureID = LoadTGA("Image//FemaleCharacter.tga");
	meshList[GEO_QUESTLADY]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUESTLADY]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_QUESTLADY]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_QUESTLADY]->material.kShininess = 1.f;

	meshList[GEO_ENGINEER] = MeshBuilder::GenerateOBJ("Counter", "OBJ//CharacterModel.obj");
	meshList[GEO_ENGINEER]->textureID = LoadTGA("Image//mainCharacterY.tga");
	meshList[GEO_ENGINEER]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_ENGINEER]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_ENGINEER]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_ENGINEER]->material.kShininess = 1.f;

	meshList[GEO_ENGINEER_BODY] = MeshBuilder::GenerateOBJ("Engineer's Body", "OBJ//HeadBody.obj");
	meshList[GEO_ENGINEER_BODY]->textureID = LoadTGA("Image//mainCharacterY.tga");
	meshList[GEO_ENGINEER_BODY]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_ENGINEER_BODY]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_ENGINEER_BODY]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_ENGINEER_BODY]->material.kShininess = 1.f;

	meshList[GEO_ENGINEER_ARMLEFT] = MeshBuilder::GenerateOBJ("Engineer left arm", "OBJ//LeftArm.obj");
	meshList[GEO_ENGINEER_ARMLEFT]->textureID = LoadTGA("Image//mainCharacterY.tga");
	meshList[GEO_ENGINEER_ARMLEFT]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_ENGINEER_ARMLEFT]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_ENGINEER_ARMLEFT]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_ENGINEER_ARMLEFT]->material.kShininess = 1.f;

	meshList[GEO_ENGINEER_ARMRIGHT] = MeshBuilder::GenerateOBJ("Engineer right arm", "OBJ//RightArm.obj");
	meshList[GEO_ENGINEER_ARMRIGHT]->textureID = LoadTGA("Image//mainCharacterY.tga");
	meshList[GEO_ENGINEER_ARMRIGHT]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_ENGINEER_ARMRIGHT]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_ENGINEER_ARMRIGHT]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_ENGINEER_ARMRIGHT]->material.kShininess = 1.f;

	meshList[GEO_ENGINEER_LEGLEFT] = MeshBuilder::GenerateOBJ("Engineer left leg", "OBJ//LeftLeg.obj");
	meshList[GEO_ENGINEER_LEGLEFT]->textureID = LoadTGA("Image//mainCharacterY.tga");
	meshList[GEO_ENGINEER_LEGLEFT]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_ENGINEER_LEGLEFT]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_ENGINEER_LEGLEFT]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_ENGINEER_LEGLEFT]->material.kShininess = 1.f;

	meshList[GEO_ENGINEER_LEGRIGHT] = MeshBuilder::GenerateOBJ("Engineer right leg", "OBJ//RightLeg.obj");
	meshList[GEO_ENGINEER_LEGRIGHT]->textureID = LoadTGA("Image//mainCharacterY.tga");
	meshList[GEO_ENGINEER_LEGRIGHT]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_ENGINEER_LEGRIGHT]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_ENGINEER_LEGRIGHT]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_ENGINEER_LEGRIGHT]->material.kShininess = 1.f;

	meshList[GEO_NORMALDUDE] = MeshBuilder::GenerateOBJ("Counter", "OBJ//CharacterModel.obj");
	meshList[GEO_NORMALDUDE]->textureID = LoadTGA("Image//mainCharacter.tga");
	meshList[GEO_NORMALDUDE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_NORMALDUDE]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_NORMALDUDE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_NORMALDUDE]->material.kShininess = 1.f;

	meshList[GEO_COMMANDER] = MeshBuilder::GenerateOBJ("Counter", "OBJ//CharacterModel.obj");
	meshList[GEO_COMMANDER]->textureID = LoadTGA("Image//mainCharacterR.tga");
	meshList[GEO_COMMANDER]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_COMMANDER]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_COMMANDER]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_COMMANDER]->material.kShininess = 1.f;

	meshList[GEO_XWINGBODY] = MeshBuilder::GenerateOBJ("XwingBody", "OBJ//XwingBody.obj");
	meshList[GEO_XWINGBODY]->textureID = LoadTGA("Image//XWing_Texture.tga");
	meshList[GEO_XWINGBODY]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_XWINGBODY]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_XWINGBODY]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_XWINGBODY]->material.kShininess = 1.f;

	meshList[GEO_XWING1] = MeshBuilder::GenerateOBJ("XwingRight", "OBJ//XwingRightWing.obj");
	meshList[GEO_XWING1]->textureID = LoadTGA("Image//XWing_Texture.tga");
	meshList[GEO_XWING1]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_XWING1]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_XWING1]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_XWING1]->material.kShininess = 1.f;

	meshList[GEO_XWING2] = MeshBuilder::GenerateOBJ("XwingLeft", "OBJ//XwingLeftWing.obj");
	meshList[GEO_XWING2]->textureID = LoadTGA("Image//XWing_Texture.tga");
	meshList[GEO_XWING2]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_XWING2]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_XWING2]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_XWING2]->material.kShininess = 1.f;

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//minecraft.tga");
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 18, 36);

	Mtx44 projection;
	projection.SetToPerspective(45.f, 16.f / 9.f, 0.1f, 10000.f);
	projectionStack.LoadMatrix(projection);

	Quest1 = false;
	Quest2 = false;
	Quest1Done = false;
	Quest2Done = false;
	QuestsDone = false;

	talkwithQL = false;
	talkwithEngi1 = false;
	talkwithEngi2 = false;
	talkwithCommando = false;

	EmptyinHand = false;
	BeerinHand = false;
	givenBeer = false;

	ReadFromTxt("TextFiles//Quest_Lady.txt", Textstuffs);
	position = Textstuffs.begin();
	sDialogue = *position;
	ssDialogue << sDialogue[0];

	ReadFromTxt("TextFiles//Engineer1.txt", TextEngi);
	Engipos = TextEngi.begin();
	sEngiDialogue = *Engipos;
	ssEngiDialogue << sEngiDialogue[0];

	ReadFromTxt("TextFiles//Engineer2.txt", TextEngi2);
	Engi2pos = TextEngi2.begin();
	sEngiDialogue2 = *Engi2pos;
	ssEngiDialogue2 << sEngiDialogue2[0];

	ReadFromTxt("TextFiles//Commando.txt", TextCommando);
	Commandopos = TextCommando.begin();
	sCommandoDialogue = *Commandopos;
	ssCommandoDialogue << sCommandoDialogue[0];

	cutscene = false;

	camera.SceneGalaxy = false;
	camera.SceneMun = false;
	camera.SceneSoraJewel = true;

	RotationWings1 = 5;
	RotationWings2 = -5;
	Engineerpositionx = -78.f, Engineerpositiony = -2.f , Engineerpositionz = -45.5f; Engineerrotationarmleft = 45; Engineerrotationarmright = -45; Engineerrotationlegleft = -45; Engineerrotationlegright = 45;
	Engineerrotationy = 280;
	Engineerpositionx2 = -65, Engineerpositiony2 = 100, Engineerpositionz2 = 56,Engineerrotationy2=180.f;
}
void SceneSoraJewel::Update(double dt)
{
	if (!cutscene)
		camera.SJUpdate(dt, 60, -140, -110, 110);
	fps = 1 / dt;

	if (camera.position.x >= 50 && camera.position.z >= 50 && Application::IsKeyPressed('E') && QuestsDone)
	{
		Gamemode::getinstance()->currentgamestate = 4;
	}

	if (((((interact >> INTERACT_XWING) & 1) > 0)) && QuestsDone)
	{
		cutscene = true;
	}

	if (cutscene)
	{
		camera.Init(Vector3(-20, 9, -109), Vector3(-20, 12, 1), Vector3(0, 1, 0));
		if (RotationWings1 > 0 && Xwing.y >= 35)
			RotationWings1 -= (float)(1 * dt);
		if (RotationWings2 < 0 && Xwing.y >= 35)
			RotationWings2 += (float)(1 * dt);
		if (Xwing.y < 35)
			Xwing.y += (float)(3 * dt);
		if (Xwing.x < 61)
			Xwing.x += (float)(15 * dt);
		if (Xwing.x > 60)
		{
			Gamemode::getinstance()->currentgamestate = 4;
		}
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

	//interactions();

	if (camera.position.x >= -28 && camera.position.z >= 49 && camera.position.x <= -18 && camera.position.z <= 60)
	{
		camera.position.x = -96;
		camera.position.y = 25;
		camera.position.z = 82;
		camera.up.y = 1;
	}
	if (Quest1Done == true && Quest2Done == true)
	{
		QuestsDone = true;
	}
	rotateGlobeY += (float)(3 * dt);
	if (rotateGlobeY >= 360)
		rotateGlobeY = 0;

	camPosX = (int)camera.position.x;
	camPosY = (int)camera.position.y;
	camPosZ = (int)camera.position.z;

	Engineeranimation(dt);
	//Quest Lady conversation
	if (talkwithQL)
	{
		timer += (float)(10 * dt);
		if (timer >= 0.5f)
		{
			if (i < sDialogue.size())
			{
				ssDialogue << sDialogue[i];
				i++;
				timer = 0;
			}
			else if (i == sDialogue.size() && Application::IsKeyPressed(VK_LBUTTON))
			{
				if (position != Textstuffs.end())
				{
					ssDialogue.str("");
					sDialogue = "";

					sDialogue = *position;
					ssDialogue << sDialogue[0];

					timer = 0;
					i = 1;
					position++;
				}
				else
				{
					if (Application::IsKeyPressed(VK_LBUTTON))
					{
						ssDialogue.str("");
						talkwithQL = false;
						position = Textstuffs.begin();
						sDialogue = *position;
						ssDialogue << sDialogue[0];
						i = 1;
					}
				}
			}
		}
	}
	//Conversation with Engi before giving his beer
	if (talkwithEngi1)
	{
		timer += (float)(10 * dt);
		if (timer >= 0.5f)
		{
			if (j < sEngiDialogue.size())
			{
				ssEngiDialogue << sEngiDialogue[j];
				j++;
				timer = 0;
			}
			else if (j == sEngiDialogue.size() && Application::IsKeyPressed(VK_LBUTTON))
			{
				if (Engipos != TextEngi.end())
				{
					ssEngiDialogue.str("");
					sEngiDialogue = "";

					sEngiDialogue = *Engipos;
					ssEngiDialogue << sEngiDialogue[0];

					timer = 0;
					j = 1;
					Engipos++;
				}
				else
				{
					if (Application::IsKeyPressed(VK_LBUTTON))
					{
						ssEngiDialogue.str("");
						talkwithEngi1 = false;
						Engipos = TextEngi.begin();
						sEngiDialogue = *Engipos;
						ssEngiDialogue << sEngiDialogue[0];
						j = 1;
					}
				}
			}
		}
	}
	//After Giving beer
	if (talkwithEngi2)
	{
		timer += (float)(10 * dt);
		if (timer >= 0.5f)
		{
			if (k < sEngiDialogue2.size())
			{
				ssEngiDialogue2 << sEngiDialogue2[k];
				k++;
				timer = 0;
			}
			else if (k == sEngiDialogue2.size() && Application::IsKeyPressed(VK_LBUTTON))
			{
				if (Engi2pos != TextEngi2.end())
				{
					ssEngiDialogue2.str("");
					sEngiDialogue2 = "";

					sEngiDialogue2 = *Engi2pos;
					ssEngiDialogue2 << sEngiDialogue2[0];

					timer = 0;
					k = 1;
					Engi2pos++;
				}
				else
				{
					if (Application::IsKeyPressed(VK_LBUTTON))
					{
						ssEngiDialogue2.str("");
						talkwithEngi2 = false;
						Engi2pos = TextEngi2.begin();
						sEngiDialogue2 = *Engi2pos;
						ssEngiDialogue2 << sEngiDialogue2[0];
						k = 1;
					}
				}
			}
		}
	}
	//To activate Quest 2
	if (talkwithCommando)
	{
		timer += (float)(10 * dt);
		if (timer >= 0.5f)
		{
			if (l < sCommandoDialogue.size())
			{
				ssCommandoDialogue << sCommandoDialogue[l];
				l++;
				timer = 0;
			}
			else if (l == sCommandoDialogue.size() && Application::IsKeyPressed(VK_LBUTTON))
			{
				if (Commandopos != TextCommando.end())
				{
					ssCommandoDialogue.str("");
					sCommandoDialogue = "";

					sCommandoDialogue = *Commandopos;
					ssCommandoDialogue << sCommandoDialogue[0];

					timer = 0;
					l = 1;
					Commandopos++;
				}
				else
				{
					if (Application::IsKeyPressed(VK_LBUTTON))
					{
						ssDialogue.str("");
						talkwithCommando = false;
						Commandopos = TextCommando.begin();
						sCommandoDialogue = *Commandopos;
						ssCommandoDialogue << sCommandoDialogue[0];
						l = 1;
					}
				}
			}
		}
	}
}
void SceneSoraJewel::Engineeranimation(float dt)
{

	float playermovementx = 0.33f, playermovementz = 1 * 0.6f; dt = 0.04f;
	if (QuestsDone == true)
	{
		if ((Engineerpositionx < -25.f))
		{
			Engineerpositionx += playermovementx;
			characterismoving = true;
		}
		if ((Engineerpositionz < 53.f))
		{
			characterismoving = true;
			Engineerpositionz += playermovementz;
		}
		if ((Engineerpositionx <= -23) && (Engineerpositionx >= -25) && (Engineerpositionz >= 53) && (Engineerpositionz <= 56))
		{
			Engineerrotationy += (float)(800 * dt);
			if (Engineerrotationy != 280)
			{
				Engineerpositiony += (float)(80 * dt);
			}
			if (Engineerpositiony >= 100)
			{
				engineer1maxy = true;
			}
		}
	}
	//The rotation of limbs
	if (characterismoving == true)
	{
		if ((Engineerrotationarmleft >= -45) && (rotationarmmax == true))
		{
			Engineerrotationarmleft -= (float)(80 * dt);
		}
		else if ((Engineerrotationarmleft < -45))
		{
			rotationarmmax = false;
		}
		if ((Engineerrotationarmleft <= 45) && (rotationarmmax == false))
		{
			Engineerrotationarmleft += (float)(80 * dt);
		}

		else if ((Engineerrotationarmleft > 45))
		{
			rotationarmmax = true;
		}

		if ((Engineerrotationarmright >= -45) && (rotationarmmax2 == true))
		{
			Engineerrotationarmright -= (float)(80 * dt);
		}
		else if ((Engineerrotationarmright < -45))
		{
			rotationarmmax2 = false;
		}
		if ((Engineerrotationarmright <= 45) && (rotationarmmax2 == false))
		{
			Engineerrotationarmright += (float)(80 * dt);
		}

		else if ((Engineerrotationarmright > 45))
		{
			rotationarmmax2 = true;
		}


		if ((Engineerrotationlegleft >= -45) && (rotationlegmaxleft == true))
		{
			Engineerrotationlegleft -= (float)(80 * dt);
		}
		else if ((Engineerrotationlegleft < -45))
		{
			rotationlegmaxleft = false;
		}
		if ((Engineerrotationlegleft <= 45) && (rotationlegmaxleft == false))
		{
			Engineerrotationlegleft += (float)(80 * dt);
		}

		else if ((Engineerrotationlegleft > 45))
		{
			rotationlegmaxleft = true;
		}

		if ((Engineerrotationlegright >= -45) && (rotationlegmaxright == true))
		{
			Engineerrotationlegright -= (float)(80 * dt);
		}
		else if ((Engineerrotationlegright < -45))
		{
			rotationlegmaxright = false;
		}
		if ((Engineerrotationlegright <= 45) && (rotationlegmaxright == false))
		{
			Engineerrotationlegright += (float)(80 * dt);
		}

		else if ((Engineerrotationlegright > 45))
		{
			rotationlegmaxright = true;
		}
	}
	if (Engineerpositiony >= 200 && Engineerpositiony2 >= 15.2f && engineer1maxy==true)
	{
		Engineerpositiony2 -= (float)(80 * dt);
	}
	interactions();
}
void SceneSoraJewel::lighting()
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
void SceneSoraJewel::lighting2()
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
void SceneSoraJewel::renderMesh(Mesh *mesh, bool enableLight)
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
void SceneSoraJewel::RenderText(Mesh* mesh, std::string text, Color color)
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
void SceneSoraJewel::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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
void SceneSoraJewel::Render()
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

	//

	modelStack.PushMatrix();
	RenderSkybox();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(20, 20, 20);
	renderMesh(meshList[GEO_SORAJEWEL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(Xwing.x, Xwing.y, Xwing.z);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(5.f, 5.f, 5.f);
	renderMesh(meshList[GEO_XWINGBODY], true);

	modelStack.PushMatrix();
	modelStack.Rotate(RotationWings1, 0, 0, 1);
	renderMesh(meshList[GEO_XWING1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(RotationWings2, 0, 0, 1);
	renderMesh(meshList[GEO_XWING2], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-120, 3, -83);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(25, 15, 25);
	renderMesh(meshList[GEO_SOFA], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(25, 0, -53);
	modelStack.Scale(5, 5, 5);
	renderMesh(meshList[GEO_PROJECTOR], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-25, -10, 53);
	modelStack.Scale(5, 5, 5);
	renderMesh(meshList[GEO_PROJECTOR], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-96, 15, 82);
	modelStack.Scale(5, 5, 5);
	renderMesh(meshList[GEO_PROJECTOR], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(25, 0, -53);
	modelStack.Scale(35, 10, 35);
	renderMesh(meshList[GEO_COUNTER], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(Keg.x, Keg.y, Keg.z);
	modelStack.Scale(5, 5, 5);
	renderMesh(meshList[GEO_KEG], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	glBlendFunc(1.1, 1);
	modelStack.Translate(25, 45, -53);
	modelStack.Rotate(rotateGlobeY, 0, 1, 0);
	modelStack.Scale(30, 30, 30);
	renderMesh(meshList[GEO_GLOBE], true);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	glBlendFunc(1.9, 1);
	modelStack.Translate(64, 0, 68);
	modelStack.Scale(20, 20, 20);
	modelStack.Rotate(90, 0, 1, 0);
	renderMesh(meshList[GEO_GLASS], true);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	modelStack.PopMatrix();


	//NPC Rendering
	modelStack.PushMatrix();
	modelStack.Translate(QuestLady.x, QuestLady.y, QuestLady.z);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(2.4f, 2.4f, 2.4f);
	renderMesh(meshList[GEO_QUESTLADY], false);
	modelStack.PopMatrix();

	if (QuestsDone == true)
	{
		Renderengineers();
	}
	else
	{
		modelStack.PushMatrix();
		modelStack.Translate(Engineer.x, Engineer.y, Engineer.z);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Rotate(90, 0, 0, 1);
		modelStack.Scale(2.4f, 2.4f, 2.4f);
		renderMesh(meshList[GEO_ENGINEER], false);
		modelStack.PopMatrix();
	}
	

	modelStack.PushMatrix();
	modelStack.Translate(25, -1, -40);
	modelStack.Rotate(270, 0, 1, 0);
	modelStack.Scale(2.4f, 2.4f, 2.4f);
	renderMesh(meshList[GEO_NORMALDUDE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(Commando.x, Commando.y, Commando.z);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(2.4f, 2.4f, 2.4f);
	renderMesh(meshList[GEO_COMMANDER], false);
	modelStack.PopMatrix();
	
	renderLast();
	renderminimaptoscreen();

	if (QuestsDone == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "You Completed The Quest For Sora Jewel", Color(0, 1, 0), 2, 2, 10);
	}
	renderText();

	std::stringstream playerPos;
	playerPos << "X = " << camPosX << " Y = " << camPosY << " Z = " << camPosZ;
	std::stringstream ss;
	ss << "FPS:" << fps << "         " << playerPos.str();
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 19);
}
void SceneSoraJewel::renderLast()
{
	// Beer
	if (EmptyinHand == false && BeerinHand == false)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Beer.x, Beer.y, Beer.z);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		renderMesh(meshList[GEO_BEEREMPTY], true);
		modelStack.PopMatrix();
	}
	else if (EmptyinHand == true && BeerinHand == false)
	{
		glDisable(GL_DEPTH_TEST);
		Mtx44 ortho;
		ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
		projectionStack.PushMatrix();
		projectionStack.LoadMatrix(ortho);
		viewStack.PushMatrix();
		viewStack.LoadIdentity(); //No need camera for ortho mode
		modelStack.PushMatrix();
		modelStack.LoadIdentity(); //Reset modelStack

		modelStack.Translate(60, 3, -2);
		modelStack.Rotate(50, 0, 1, 0);
		modelStack.Scale(10, 10, 10);
		renderMesh(meshList[GEO_BEEREMPTY], true);

		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
	}
	else if (BeerinHand == true && EmptyinHand == false)
	{
		glDisable(GL_DEPTH_TEST);
		Mtx44 ortho;
		ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
		projectionStack.PushMatrix();
		projectionStack.LoadMatrix(ortho);
		viewStack.PushMatrix();
		viewStack.LoadIdentity(); //No need camera for ortho mode
		modelStack.PushMatrix();
		modelStack.LoadIdentity(); //Reset modelStack

		modelStack.Translate(60, 3, -2);
		modelStack.Rotate(50, 0, 1, 0);
		modelStack.Scale(10, 10, 10);
		renderMesh(meshList[GEO_BEERFULL], true);

		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
	}
}
void SceneSoraJewel::renderText()
{
	if (talkwithQL || talkwithEngi1 || talkwithEngi2 || talkwithCommando)
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
		modelStack.Scale(85, 60, 1);
		modelStack.Rotate(90, 1, 0, 0);
		renderMesh(meshList[GEO_QUAD], false);
		projectionStack.PopMatrix();
		viewStack.PopMatrix();
		modelStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
	}

	if (talkwithQL)
		RenderTextOnScreen(meshList[GEO_TEXT], ssDialogue.str(), Color(0, 0, 0), 2.3f, 4.7f, 4);
	if (talkwithEngi1)
		RenderTextOnScreen(meshList[GEO_TEXT], ssEngiDialogue.str(), Color(0, 0, 0), 2.5f, 5, 4);
	if (talkwithEngi2)
		RenderTextOnScreen(meshList[GEO_TEXT], ssEngiDialogue2.str(), Color(0, 0, 0), 2.5f, 5, 4);
	if (talkwithCommando)
		RenderTextOnScreen(meshList[GEO_TEXT], ssCommandoDialogue.str(), Color(0, 0, 0), 2.5f, 5, 4);
}
void SceneSoraJewel::Renderengineers()
{
	modelStack.PushMatrix();
	modelStack.Translate(Engineerpositionx, Engineerpositiony, Engineerpositionz);
	modelStack.Rotate(Engineerrotationy, 0, 1, 0);
	modelStack.Scale(2.4f, 2.4f, 2.4f);
	renderMesh(meshList[GEO_ENGINEER_BODY], false);

	modelStack.PushMatrix();
	modelStack.Translate(0, 4.6f, 0);
	modelStack.Rotate(Engineerrotationarmleft, 0, 0, 1);
	modelStack.Scale(1.f, 1.f, 1.f);
	renderMesh(meshList[GEO_ENGINEER_ARMLEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 4.6f, 0);
	modelStack.Rotate(Engineerrotationarmright, 0, 0, 1);
	modelStack.Scale(1.f, 1.f, 1.f);
	renderMesh(meshList[GEO_ENGINEER_ARMRIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, 2.6f, 0.f);
	modelStack.Rotate(Engineerrotationlegleft, 0, 0, 1);
	modelStack.Scale(1.f, 1.f, 1.f);
	renderMesh(meshList[GEO_ENGINEER_LEGLEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, 2.6f, 0.f);
	modelStack.Rotate(Engineerrotationlegright, 0, 0, 1);
	modelStack.Scale(1.f, 1.f, 1.f);
	renderMesh(meshList[GEO_ENGINEER_LEGRIGHT], false);
	modelStack.PopMatrix();
	//Body Parent
	modelStack.PopMatrix();

	//Engineer after teleportin
	modelStack.PushMatrix();
	modelStack.Translate(Engineerpositionx2, Engineerpositiony2, Engineerpositionz2);
	modelStack.Rotate(Engineerrotationy2, 0, 1, 0);
	modelStack.Scale(2.4f, 2.4f, 2.4f);
	renderMesh(meshList[GEO_ENGINEER_BODY], false);

	modelStack.PushMatrix();
	modelStack.Translate(0, 4.6f, 0);
	//modelStack.Rotate(Engineerrotationarmleft, 0, 0, 1);
	modelStack.Scale(1.f, 1.f, 1.f);
	renderMesh(meshList[GEO_ENGINEER_ARMLEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 4.6f, 0);
	//modelStack.Rotate(Engineerrotationarmright, 0, 0, 1);
	modelStack.Scale(1.f, 1.f, 1.f);
	renderMesh(meshList[GEO_ENGINEER_ARMRIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, 2.6f, 0.f);
	//modelStack.Rotate(Engineerrotationlegleft, 0, 0, 1);
	modelStack.Scale(1.f, 1.f, 1.f);
	renderMesh(meshList[GEO_ENGINEER_LEGLEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, 2.6f, 0.f);
	//modelStack.Rotate(Engineerrotationlegright, 0, 0, 1);
	modelStack.Scale(1.f, 1.f, 1.f);
	renderMesh(meshList[GEO_ENGINEER_LEGRIGHT], false);
	modelStack.PopMatrix();
	//Body Parent
	modelStack.PopMatrix();
}
void SceneSoraJewel::renderminimaptoscreen()
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
	modelStack.Translate(75.f, 55.f, -2);
	modelStack.Scale(17.f, 17.f, 17.f);
	modelStack.Rotate(90, 1, 0, 0);
	renderMesh(meshList[GEO_MINIMAPSJ], false);
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
	modelStack.Translate(camera.minimapsoracoords.x, camera.minimapsoracoords.y, -1);
	modelStack.Scale(0.5, 0.5, 0.5);
	modelStack.Rotate(90, 1, 0, 0);
	renderMesh(meshList[GEO_MAINICONSJ], false);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}
void SceneSoraJewel::RenderSkybox()
{
	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Translate(0, 0, -498);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	renderMesh(meshList[GEO_SORAJEWELBACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 498, 0);
	modelStack.Rotate(270, 0, 1, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Scale(1000, 1000, 1000);
	renderMesh(meshList[GEO_SORAJEWELTOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-498, 0, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	renderMesh(meshList[GEO_SORAJEWELLEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -498);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	renderMesh(meshList[GEO_SORAJEWELFRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -498, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	renderMesh(meshList[GEO_SORAJEWELBOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 90, 0);
	modelStack.Translate(0, 0, 498);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	renderMesh(meshList[GEO_SORAJEWELRIGHT], false);
	modelStack.PopMatrix();
}
void SceneSoraJewel::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
void SceneSoraJewel::interactions()
{
	tempview = (camera.target - camera.position); // your camera view
	viewAtQuestLady = (QuestLady - camera.position);
	viewAtEngineer = (Engineer - camera.position);
	viewAtCommando = (Commando - camera.position);
	viewAtKeg = (Keg - camera.position);
	viewAtXwing = (Xwing - camera.position);
	viewAtBeer = (Beer - camera.position);

	RadiusFromQuestLady = (viewAtQuestLady - tempview).Length();//<17
	RadiusFromEngineer = (viewAtEngineer - tempview).Length();//<15
	RadiusFromCommando = (viewAtCommando - tempview).Length();//<15
	RadiusFromKeg = (viewAtKeg - tempview).Length();//<15
	RadiusFromXwing = (viewAtXwing - tempview).Length();//<15
	RadiusFromBeer = (viewAtBeer - tempview).Length();//<7

	//std::cout << RadiusFromBeer << std::endl;
	
	if (RadiusFromQuestLady < 17.0f
		&& Application::IsKeyPressed('E'))
	{
		interact |= 1 << INTERACT_QUESTLADY;
		Quest1 = true;
		talkwithQL = true;
	}
	else if (RadiusFromQuestLady > 17.0f)
	{
		interact &= ~(1 << INTERACT_QUESTLADY);
		talkwithQL = false;
	}

	if (RadiusFromEngineer < 20.0f
		&& Application::IsKeyPressed('E') && !BeerinHand && !QuestsDone)
	{
		interact |= 1 << INTERACT_ENGINEER1;
		talkwithEngi1 = true;
	}
	else if (RadiusFromEngineer > 20.0f)
	{
		interact &= ~(1 << INTERACT_ENGINEER1);
		talkwithEngi1 = false;
	}

	if (RadiusFromEngineer < 20.0f
		&& Application::IsKeyPressed('E') && BeerinHand)
	{
		interact |= 1 << INTERACT_ENGINEER2;
		BeerinHand = false;
		Quest1Done = true;
		Quest2Done = true;
		talkwithEngi2 = true;
	}
	else if (RadiusFromEngineer > 20.0f)
	{
		interact &= ~(1 << INTERACT_ENGINEER2);
		talkwithEngi2 = false;
	}

	if (RadiusFromCommando < 15.0f
		&& Application::IsKeyPressed('E') && Quest1)
	{
		interact |= 1 << INTERACT_COMMANDO;
		Quest2 = true;
		talkwithCommando = true;
	}
	else if (RadiusFromCommando > 15.0f)
	{
		interact &= ~(1 << INTERACT_COMMANDO);
		talkwithCommando = false;
	}

	if (RadiusFromKeg < 15.0f
		&& Application::IsKeyPressed('E') && EmptyinHand)
	{
		interact |= 1 << INTERACT_KEG;
		EmptyinHand = false;
		BeerinHand = true;
	}
	else if (RadiusFromKeg > 15.0f)
	{
		interact &= ~(1 << INTERACT_KEG);
	}

	if (RadiusFromXwing < 15.0f
		&& Application::IsKeyPressed('E') && QuestsDone)
	{
		interact |= 1 << INTERACT_XWING;
		cutscene = true;
	}
	else if (RadiusFromXwing > 15.0f)
	{
		interact &= ~(1 << INTERACT_XWING);
	}

	if (RadiusFromBeer < 7.0f
		&& Application::IsKeyPressed('E') && Quest2)
	{
		interact |= 1 << INTERACT_BEER;
		BeerinHand = false;
		EmptyinHand = true;
	}
	else if (RadiusFromBeer > 7.0f)
	{
		interact &= ~(1 << INTERACT_BEER);
	}
	//use the below to render your text :V
	//((((interact >> TALKING_TO_LADY) & 1) > 0)) // same as talkingtolady == true, Checking
	//((((interact >> TALKING_TO_LADY) & 1) < 1)) // same as talkingtolady == false, Checking
}