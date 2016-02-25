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
	
	Vector3 target;
	Vector3 position;
	Vector3 XWing = Vector3(0, 495, -10);
	Vector3 Asteroid = Vector3(-123, 486, -600);
	Vector3 Asteroid2 = Vector3(-104, 520, -230);
	Vector3 Asteroid3 = Vector3(124, 570, -300);
	Vector3 Asteroid4 = Vector3(110, 600, -238);
	Vector3 Asteroid5 = Vector3(-153, 467, -374);
	Vector3 Asteroid6 = Vector3(40, 470, -149);
	Vector3 Asteroid7 = Vector3(-70, 450, -596);
	Vector3 Asteroid8 = Vector3(-124, 500, -849);
	Vector3 Asteroid9 = Vector3(-40, 600, -723);
	Vector3 Asteroid10 = Vector3(67, 578, -423);

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

	void MunInit();
	void MunRender();

	void GalaxyInit();
	void GalaxyRender();

	void SoraJewelInit();
	void SoraJewelRender();

	MS modelStack, viewStack, projectionStack;
};

#endif