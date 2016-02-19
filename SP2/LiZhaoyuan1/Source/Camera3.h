#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "Camera.h"
#include "Application.h"

class Camera3 : public Camera
{
public:
	//Vector3 position;
	//Vector3 target;
	//Vector3 up;

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;

	Vector3 minimapcoords = (75.f, 55.f, -1.f);
	Vector3 minimapsoracoords = (75.f, 55.f, -1.f);

	Camera3();
	~Camera3();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt, float bounds);
	virtual void Reset();

	void UpdateCollision(float bounds, double dt);

	bool SceneSoraJewel = false;
	bool SceneMun = false;
	bool SceneGalaxy = false;
	bool boundaryCheckerX(float smallx, float largex, float smallz, float largez, Vector3 value);
	bool boundaryCheckerZ(float smallx, float largex, float smallz, float largez, Vector3 value);
	bool OBJboundaryX(Vector3 Testvalue);
	bool OBJboundaryZ(Vector3 Testvalue);
	bool OBJboundaryY(Vector3 Testvalue, int XZ);
	bool AllGalaxyBoundaryX(Vector3 Testvalue);
	bool AllGalaxyBoundaryZ(Vector3 Testvalue);
	bool AllMunBoundaryX(Vector3 Testvalue);
	bool AllMunBoundaryZ(Vector3 Testvalue);
	bool AllSoraJewelBoundaryX(Vector3 Testvalue);
	bool AllSoraJewelBoundaryZ(Vector3 Testvalue);

	float rotateChar;
	float translateChar;
	
};

#endif