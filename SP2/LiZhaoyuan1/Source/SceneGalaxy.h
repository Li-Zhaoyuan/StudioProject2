/****************************************************************************/
/*!
\file SceneGalaxy.h
\author Li Zhaoyuan, Nathan Chia Shi-Lin, Terence Tan Ming Jie, Muhammad Nurhidayat Bin Suderman
\par email: lizhaoyuan123@hotmail.com
\brief
class for the scene at Galaxy
*/
/****************************************************************************/

#ifndef SceneGalaxy_H_
#define SceneGalaxy_H_

#include "Scene.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera.h"
#include "Camera3.h"
#include "Camera4.h"
#include "MatrixStack.h"
#include <vector>
#include "Missile.h"
#include <cmath>
#include "SP2.h"
#include "CurrentGameState.h"

/******************************************************************************/
/*!
Class SceneGalaxy:
\brief	Defines the scene Galaxy and its methods
*/
/******************************************************************************/

class SceneGalaxy : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE,
		GEO_SPHERE,
		GEO_LIGHTBALL,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
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
		SEO_SORAJEWELGROUND,
		GEO_ASTEROID,
		GEO_GLOBE,
		GEO_PROJECTOR,
		GEO_SOFA,
		GEO_HOUSE,
		GEO_ORE,
		GEO_PICKAXE,
		GEO_XWING,
		GEO_CRASHEDPLANE,
		GEO_MUN,
		GEO_FEMALEA,
		GEO_FEMALEB,
		GEO_ALIEN,
		GEO_MALE,
		GEO_PROTAGANIST,
		GEO_CAVE,
		GEO_MISSILE,
		GEO_BLACKSCREEN,
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
	SceneGalaxy();
	~SceneGalaxy();

	void skybox();
	virtual void Init();
	virtual void Update(double dt);
	void XWingHealth();
	virtual void Render();
	virtual void RenderXwing();
	virtual void RenderAsteroid();
	virtual void MovingAsteroid(double dt);
	int getMagnitude(Vector3 A, Vector3 B);
	virtual void RenderMissile();
	bool CheckCollision(Vector3 A, Vector3 B);
	bool CheckAsteroidStartWave();
	bool CheckAsteroidWave1();
	bool CheckAsteroidWave2();
	bool CheckLargeAsteroid();
	void CutScene(double dt);
	virtual void Exit();

private:
	Light light[2];
	bool enableLight = false;
	float LSPEED = 10.f;
	int fps = 0;
	int destroyedAsteroids = 0;

	float rotateXWing = 0.f;
	bool rotateXWing_Limit;

	bool shootMissile = false; 

	bool renderAsteroid = true;
	bool renderAsteroid2 = true;
	bool renderAsteroid3 = true;
	bool renderAsteroid4 = true;
	bool renderAsteroid5 = true;
	bool renderAsteroid6 = true;
	bool renderAsteroid7 = true;
	bool renderAsteroid8 = true;
	bool renderAsteroid9 = true;
	bool renderAsteroid10 = true;
	bool renderAsteroidLarge = true;
	bool renderXWing = true;
	bool renderSkybox = true;
	
	Vector3 target;
	Vector3 position;
	Vector3 XWing = Vector3(0, 495, -10);
	Vector3 Asteroid = Vector3(-123, 486, -600);
	Vector3 Asteroid2 = Vector3(4, 520, -600);
	Vector3 Asteroid3 = Vector3(124, 570, -600);
	Vector3 Asteroid4 = Vector3(10, 600, -600);
	Vector3 Asteroid5 = Vector3(-153, 467, -600);
	Vector3 Asteroid6 = Vector3(40, 470, -600);
	Vector3 Asteroid7 = Vector3(-70, 450, -600);
	Vector3 Asteroid8 = Vector3(-124, 500, -609);
	Vector3 Asteroid9 = Vector3(-40, 600, -723);
	Vector3 Asteroid10 = Vector3(67, 578, -600);
	Vector3 LAsteroid = Vector3(0, 700, -600);

	Vector3 missilePos = Vector3(0, 0, 0);
	Vector3 missileTar = Vector3(0, 0, 0);
	Vector3 missileView;

	

	void renderMesh(Mesh *mesh, bool enableLight);
	void lighting();
	void lighting2();
	void RenderSkybox();

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Camera3 camera;

	float boxX = 0;
	float boxZ = 0;
	float camPosX = 0;
	float camPosY = 0;
	float camPosz = 0;
	float camView = 0;

	void MunInit();
	void MunRender();

	void GalaxyInit();
	void GalaxyRender();

	void SoraJewelInit();
	void SoraJewelRender();

	MS modelStack, viewStack, projectionStack;
};

#endif