/****************************************************************************/
/*!
\file SceneMun.h
\author Li Zhaoyuan, Nathan Chia Shi-Lin, Terence Tan Ming Jie, Muhammad Nurhidayat Bin Suderman
\par email: lizhaoyuan123@hotmail.com
\brief
class for the scene at Mun
*/
/****************************************************************************/
#ifndef SCENEMUN_H_
#define SCENEMUN_H_

#include "Scene.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"
#include "Camera2.h"
#include "Camera3.h"
#include "Camera4.h"
#include "MatrixStack.h"
#include "CurrentGameState.h"
#include "ReadTextFile.h"

#include <sstream>


/******************************************************************************/
/*!
Class SceneMun:
\brief	Defines the scene Mun and its methods
*/
/******************************************************************************/

class SceneMun : public Scene
{

	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE,
		GEO_SPHERE,
		GEO_LIGHTBALL,
		GEO_TEXT,
		GEO_MUNLEFT,
		GEO_MUNRIGHT,
		GEO_MUNTOP,
		GEO_MUNBOTTOM,
		GEO_MUNFRONT,
		GEO_MUNBACK,
		GEO_MUNGROUND,
		GEO_HOUSE,
		GEO_ORE,
		GEO_PICKAXE,
		GEO_CRASHEDPLANE,
		GEO_PLANE,
		GEO_PLANE_TAKEOFF,
		GEO_MUN,
		GEO_MINIMAP,
		GEO_MAINICON,
		GEO_FEMALEA,
		GEO_FEMALEB,
		GEO_ALIEN,
		GEO_MALE,
		GEO_PROTAGANIST,
		GEO_SNAKE,
		GEO_CAVE,
		GEO_VILLAGER_LEGLEFT,
		GEO_VILLAGER_LEGRIGHT,
		GEO_VILLAGER_ARMLEFT,
		GEO_VILLAGER_ARMRIGHT,
		GEO_VILLAGER_BODY,
		GEO_CRATE,
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
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,
		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

	enum Interactions
	{
		TALKED_QUEST_DUDE = 0,
		MINER_GET_LETTER,
		PLAYER_GET_PICKAXE,
		MINING,
		REPAIRING,
		TALKING_TO_LADY,
		TALKING_TO_QUEST_DUDE,
		TALKING_TO_MINER_CASE_1,
		TALKING_TO_MINER_CASE_2,
		MINED,
		REPAIRED,
		CAN_INTERACT,
		TALKING_TO_SNAKE,
	};
public:
	SceneMun();
	~SceneMun();

	void skybox();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();



private:
	Light light[2];
	bool enableLight = false;
	float LSPEED = 10.f;
	int fps = 0;

	void renderMesh(Mesh *mesh, bool enableLight);
	void lighting();
	void lighting2();
	void RenderSkybox();
	void interactionWithRobby();
	void interactionWithSnowBalls();
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void Renderpicturetoscreen();
	void npcRotate();
	void interactions();
	void RenderPickaxeOnScreen();
	void RenderLoadingBarOnScreen();
	void RenderOreOnScreen();
	void RenderTextBoxOnScreen();
	void RenderLetterOnScreen();
	void RenderInfomationOnScreen();
	void RenderCalefare();
	void RenderSceneOBJ();
	void fultoninteraction();
	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Camera3 camera;

	float boxX = 0;
	float boxZ = 0;
	int camPosX = 0;
	int camPosY = 0;
	int camPosz = 0;
	
	int interact = 0;

	int fultonleft;

	float timing = 0;

	bool textWL = false;
	bool textQD = false;
	bool textminer1 = false;
	bool textminer2 = false;
	bool fultonreceived = false;

	size_t a = 1;
	size_t b = 1;
	size_t c = 1;
	size_t d = 1;

	std::stringstream ssWLady;
	std::stringstream ssQuestDude;
	std::stringstream ssMiner;
	std::stringstream ssMiner2;
	std::stringstream thisisastring;

	std::string sWLady;
	std::string sQuestDude;
	std::string sMiner;
	std::string sMiner2;

	std::vector<std::string> TextLady;
	std::vector<std::string> TextQuestDude;
	std::vector<std::string> TextMiner;
	std::vector<std::string> TextMiner2;

	std::vector<std::string>::iterator Ladypos;
	std::vector<std::string>::iterator QuestDudepos;
	std::vector<std::string>::iterator Minerpos;
	std::vector<std::string>::iterator Minerpos2;


	Vector3 crashedplaneCoord = Vector3(-36.f,4.9f,-49.f);
	Vector3 planecoord = Vector3(-36.f, -2.9f, -49.f);
	Vector3 questdudehouseCoord = Vector3(33, -5, 20);
	Vector3 worriedladyhouseCoord = Vector3(20, -5, -38);
	Vector3 worriedladyCoord = Vector3(2, -4, -38);
	Vector3 questdudeCoord = Vector3(33, -4, 3);
	Vector3 minerandplusCoord = Vector3(-19, 0, 25);
	Vector3 caveCoord = Vector3(-35, -5, 35);
	Vector3 oreCoord = Vector3(-42, -2.75f, 35);
	Vector3 CalefareACoord = Vector3(26, -0.9f, -21);
	Vector3 CalefareBCoord = Vector3(26, -0.9f, -10);
	Vector3 CalefareCCoord = Vector3(15, -0.9f, 25);
	Vector3 SNAKEcoords = Vector3(47.f, -5.5f, 46.f);
	Vector3 tempview;
	Vector3 viewAtOre;
	Vector3 viewAtLady;
	Vector3 viewAtDude;
	Vector3 viewAtMiner;
	Vector3 viewAtCrashedPlane;
	Vector3 viewatSNAKE;
	float worriedladytempx = 0;
	float worriedladytempz = 0;

	float minerandplusx = 0;
	float minerandplusz = 0;

	float questdudex = 0;
	float questdudez = 0;

	float rotateworriedlady = 0;
	float rotateminer = 0;
	float rotatequestdude = 0;

	float loadingbar = 0.01f;
	
	float RadiusFromOre;
	float RadiusFromLady;
	float RadiusFromDude;
	float RadiusFromMiner;
	float RadiusFromCrashedPlane;
	float RadiusFromSnake;
	float rotateAngle = 0;
	float rotateLimbs = 0;
	float rotateWhole = 0;
	float translatingChar = 0;
	float hoverheight = 0;
	float rotateplane = 0;
	float translateplane = 0;

	MS modelStack, viewStack, projectionStack;
};

#endif