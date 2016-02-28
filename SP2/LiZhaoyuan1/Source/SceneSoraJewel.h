#ifndef SCENESORAJEWEL_H_
#define SCENESORAJEWEL_H_

#include "Scene.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"
#include "Camera2.h"
#include "Camera3.h"
#include "Camera4.h"
#include "MatrixStack.h"
#include "Physics.h"
#include "ReadTextFile.h"
#include <sstream>

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
	double fps = 0;

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

	std::string sDialogue;
	std::string sEngiDialogue;
	
	std::vector<std::string> Textstuffs;
	std::vector<std::string> TextEngi;

	std::vector<std::string>::iterator position;
	std::vector<std::string>::iterator Engipos;

	bool talkwithQL;
	bool talkwithEngi1;
	bool talkwithEngi2;

	size_t i = 1;
	size_t j = 1;
	float timer = 0.f;
	bool timercheck = false;

	float boxX = 0;
	float boxZ = 0;
	float camPosX = 0;
	float camPosY = 0;
	float camPosZ = 0;

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

	bool EmptyinHand;
	bool BeerinHand;

	float Engineerpositionx, Engineerpositiony, Engineerpositionz;
	bool characterismoving = false, rotationarmmax = true; 
	bool rotationarmmax2 = true, rotationlegmaxleft = true, rotationlegmaxright = true;
	bool engineer1maxy = false;
	float Engineerrotationarmleft, Engineerrotationarmright, Engineerrotationlegleft, Engineerrotationlegright, Engineerrotationy;
	float Engineerpositionx2, Engineerpositiony2, Engineerpositionz2, Engineerrotationy2;

	Vector3 tempview;
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
};

#endif