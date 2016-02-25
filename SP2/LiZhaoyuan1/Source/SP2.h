#ifndef SP2_H_
#define SP2_H_

#include "Scene.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"
#include "Camera2.h"
#include "Camera3.h"
#include "MatrixStack.h"
class SP2 : public Scene
{

	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE2,
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
		GEO_GALAXYLEFT,
		GEO_GALAXYRIGHT,
		GEO_GALAXYTOP,
		GEO_GALAXYBOTTOM,
		GEO_GALAXYFRONT,
		GEO_GALAXYBACK,
		GEO_GALAXYGROUND,
		GEO_SORAJEWELLEFT,
		GEO_SORAJEWELRIGHT,
		GEO_SORAJEWELTOP,
		GEO_SORAJEWELBOTTOM,
		GEO_SORAJEWELFRONT,
		GEO_SORAJEWELBACK,
		GEO_SORAJEWEL,
		GEO_ASTEROID,
		GEO_GLOBE,
		GEO_PROJECTOR,
		GEO_SOFA,
		GEO_HOUSE,
		GEO_ORE,
		GEO_PICKAXE,
		GEO_CRASHEDPLANE,
		GEO_MUN,
		GEO_FEMALEA,
		GEO_FEMALEB,
		GEO_ALIEN,
		GEO_MALE,
		GEO_PROTAGANIST,
		GEO_CAVE,
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
	SP2();
	~SP2();

	void skybox();

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
	void Rendermainmenutoscreen();
	void interactionWithRobby();
	void interactionWithSnowBalls();
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	/*float rotateAngle;
	float planet1RevAngle, planet1RotAngle, moon1RotAngle;*/

	Camera3 camera;

	float boxX = 0;
	float boxZ = 0;
	float camPosX = 0;
	float camPosY = 0;
	float camPosz = 0;
	
	void MunInit();
	void MunRender();

	void GalaxyInit();
	void GalaxyRender();
	
	void SoraJewelInit();
	void SoraJewelRender();

	void renderMunSkybox();
	void renderGalaxySkybox();
	void renderSoraJewelSkybox();

	float arrowpositiony;
	Application application;

	MS modelStack, viewStack, projectionStack;
};

#endif