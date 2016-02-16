
#include <sstream>

#include "SP2.h"
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
#include "RenderMun.h"

void SP2::MunInit()
{
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
	meshList[GEO_MUNGROUND] = MeshBuilder::GenerateQuad("ground", Color(0.2, 0.2, 0.2));
	meshList[GEO_CRASHEDPLANE] = MeshBuilder::GenerateOBJ("crashedplane", "OBJ//XWingCrash.obj");
	meshList[GEO_CRASHEDPLANE]->textureID = LoadTGA("Image//XWingCrash_Texture.tga");
	meshList[GEO_CRASHEDPLANE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CRASHEDPLANE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CRASHEDPLANE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CRASHEDPLANE]->material.kShininess = 5.f;
	meshList[GEO_HOUSE] = MeshBuilder::GenerateOBJ("house", "OBJ//house.obj");
	meshList[GEO_HOUSE]->textureID = LoadTGA("Image//house.tga");
	meshList[GEO_HOUSE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HOUSE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HOUSE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HOUSE]->material.kShininess = 5.f;
	meshList[GEO_MALE] = MeshBuilder::GenerateOBJ("Guy", "OBJ//CharacterModel.obj");
	meshList[GEO_MALE]->textureID = LoadTGA("Image//HumanCharacter.tga");
	meshList[GEO_MALE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MALE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MALE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MALE]->material.kShininess = 5.f;
	meshList[GEO_CAVE] = MeshBuilder::GenerateOBJ("Guy", "OBJ//Cave.obj");
	meshList[GEO_CAVE]->textureID = LoadTGA("Image//Cave.tga");
	meshList[GEO_CAVE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CAVE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CAVE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CAVE]->material.kShininess = 5.f;
	camera.Init(Vector3(0, 0, 1), Vector3(0, -4.0, 0), Vector3(0, 1, 0));
}

void SP2::MunRender()
{
	modelStack.PushMatrix();
	modelStack.Rotate(180, 1, 0, 0);
	renderMunSkybox();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -5, 0);
	modelStack.Scale(100, 100, 100);
	renderMesh(meshList[GEO_MUNGROUND], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-36, 4.9, -34);
	modelStack.Scale(2.2, 2.2, 2.2);
	renderMesh(meshList[GEO_CRASHEDPLANE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(15, -5, 20);
	renderMesh(meshList[GEO_HOUSE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(34, -4, 3);
	modelStack.Rotate(90, 0, 1, 0);
	renderMesh(meshList[GEO_MALE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(34, -4, 3);
	modelStack.Rotate(90, 0, 1, 0);
	renderMesh(meshList[GEO_CAVE], true);
	modelStack.PopMatrix();
}

void SP2::renderMunSkybox()
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