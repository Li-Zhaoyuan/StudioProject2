/****************************************************************************/
/*!
\file SceneSoraJewel.h
\author Li Zhaoyuan, Nathan Chia Shi-Lin, Terence Tan Ming Jie, Muhammad Nurhidayat Bin Suderman
\par email: lizhaoyuan123@hotmail.com
\brief
class for the scene at SoraJewel
*/
/****************************************************************************/

#ifndef SCENESORAJEWEL_H_
#define SCENESORAJEWEL_H_

#include "Scene.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"
#include "Camera3.h"
#include "MatrixStack.h"
#include "ReadTextFile.h"
#include <sstream>
#include "Music.h"

/******************************************************************************/
/*!
Class SceneSoraJewel:
\brief	Defines the scene Sora Jewel and its methods
*/
/******************************************************************************/
class SceneSoraJewel : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_LIGHTBALL,
		GEO_TEXT,
		GEO_SORAJEWELLEFT,
		GEO_SORAJEWELRIGHT,
		GEO_SORAJEWELTOP,
		GEO_SORAJEWELBOTTOM,
		GEO_SORAJEWELFRONT,
		GEO_SORAJEWELBACK,
		GEO_SORAJEWEL,
		GEO_XWING,
		GEO_XWINGFLY,
		GEO_GLASS,
		GEO_GLOBE,
		GEO_PROJECTOR,
		GEO_COUNTER,
		GEO_SOFA,
		GEO_QUESTLADY,
		GEO_ENGINEER,
		GEO_ENGINEER_LEGLEFT,
		GEO_ENGINEER_LEGRIGHT,
		GEO_ENGINEER_ARMLEFT,
		GEO_ENGINEER_ARMRIGHT,
		GEO_ENGINEER_BODY,
		GEO_COMMANDER,
		GEO_NORMALDUDE,
		GEO_KEG,
		GEO_BEERFULL,
		GEO_BEEREMPTY,
		GEO_MAINICONSJ,
		GEO_MINIMAPSJ,
		GEO_XWINGBODY,
		GEO_XWING1,
		GEO_XWING2,
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
		U_LIGHT2_POSITION,
		U_LIGHT2_COLOR,
		U_LIGHT2_POWER,
		U_LIGHT2_KC,
		U_LIGHT2_KL,
		U_LIGHT2_KQ,
		U_LIGHT2_TYPE,
		U_LIGHT2_SPOTDIRECTION,
		U_LIGHT2_COSCUTOFF,
		U_LIGHT2_COSINNER,
		U_LIGHT2_EXPONENT,
		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

	enum Interactions
	{
		INTERACT_QUESTLADY,
		INTERACT_ENGINEER1,
		INTERACT_ENGINEER2,
		INTERACT_COMMANDO,
		INTERACT_KEG,
		INTERACT_XWING,
		INTERACT_BEER,
	};
public:
	SceneSoraJewel();
	~SceneSoraJewel();

	void skybox();
	void renderLast();
	void renderText();
	void renderNPCAnimations();
	void interactions();

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
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	//void TextForInteractions();
	void renderminimaptoscreen();

	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Camera3 camera;
	
	std::stringstream ssDialogue;
	std::stringstream ssEngiDialogue;
	std::stringstream ssEngiDialogue2;
	std::stringstream ssCommandoDialogue;
	
	std::string sDialogue;
	std::string sEngiDialogue;
	std::string sEngiDialogue2;
	std::string sCommandoDialogue;
	
	std::vector<std::string> Textstuffs;
	std::vector<std::string> TextEngi;
	std::vector<std::string> TextEngi2;
	std::vector<std::string> TextCommando;

	std::vector<std::string>::iterator position;
	std::vector<std::string>::iterator Engipos;
	std::vector<std::string>::iterator Engi2pos;
	std::vector<std::string>::iterator Commandopos;

	bool pressE;

	bool talkwithQL;
	bool talkwithEngi1;
	bool talkwithEngi2;
	bool talkwithCommando;

	size_t i = 1;
	size_t j = 1;
	size_t k = 1;
	size_t l = 1;

	float timer = 0.f;
	bool cutscene;
	bool timercheck = false;

	float boxX = 0;
	float boxZ = 0;
	int camPosX = 0;
	int camPosY = 0;
	int camPosZ = 0;

	float rotateGlobeY = 0;

	void MunInit();
	void MunRender();

	void GalaxyInit();
	void GalaxyRender();

	void SoraJewelInit();
	void SoraJewelRender();
	void Renderengineers();


	void Engineeranimation(float dt);

	bool Quest1;
	bool Quest1Done;
	bool Quest2;
	bool Quest2Done;
	bool QuestsDone;

	bool TextQ1Activated;
	bool TextQ2Activated;
	
	bool givenBeer;
	bool EmptyinHand;
	bool BeerinHand;

	float Engineerpositionx, Engineerpositiony, Engineerpositionz;
	bool characterismoving = false, rotationarmmax = true; 
	bool rotationarmmax2 = true, rotationlegmaxleft = true, rotationlegmaxright = true;
	bool engineer1maxy = false;
	float Engineerrotationarmleft, Engineerrotationarmright, Engineerrotationlegleft, Engineerrotationlegright, Engineerrotationy;
	float Engineerpositionx2, Engineerpositiony2, Engineerpositionz2, Engineerrotationy2;

	int interact = 0;

	Vector3 tempview;
	Vector3 viewAtQuestLady;
	Vector3 viewAtEngineer;
	Vector3 viewAtCommando;
	Vector3 viewAtKeg;
	Vector3 viewAtXwing;
	Vector3 viewAtBeer;

	float RadiusFromQuestLady;
	float RadiusFromEngineer;
	float RadiusFromCommando;
	float RadiusFromKeg;
	float RadiusFromXwing;
	float RadiusFromBeer;

	float RotationWings1;
	float RotationWings2;


	/*Vector3 viewAtOre;
	Vector3 viewAtLady;
	Vector3 viewAtDude;
	Vector3 viewAtMiner;
	Vector3 viewAtCrashedPlane;*/

	MS modelStack, viewStack, projectionStack;

	Vector3 QuestLady = Vector3(13, -1, -53);
	Vector3 Engineer = Vector3(-96, 5, -40);
	Vector3 Commando = Vector3(-93, 13, 41);
	Vector3 Keg = Vector3(-50, 0, -104);
	Vector3 Xwing = Vector3(-85, 19, 65);
	Vector3 Beer = Vector3(18, 8, -33);
};

#endif