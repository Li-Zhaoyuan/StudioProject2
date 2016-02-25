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

class SceneSoraJewel : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
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

public:
	SceneSoraJewel();
	~SceneSoraJewel();

	void skybox();
	void renderLast();
	void renderNPCAnimations();

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

	/*float rotateAngle;
	float planet1RevAngle, planet1RotAngle, moon1RotAngle;*/

	Camera3 camera;

	std::vector<std::string> Textstuffs;
	std::vector<std::string> Dialogue;
	std::vector<std::string>::iterator position;

	float timer = 0;
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
	bool characterismoving = false; bool rotationarmmax = true; bool rotationarmmax2 = true, rotationlegmaxleft = true, rotationlegmaxright = true;
	int engineerhasteleported;
	float Engineerrotationarmleft, Engineerrotationarmright, Engineerrotationlegleft, Engineerrotationlegright;

	MS modelStack, viewStack, projectionStack;
};

#endif