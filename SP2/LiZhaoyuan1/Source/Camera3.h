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

	Vector3 currentV = (0.f, 0.f, 0.f);
	Vector3 displacement = (0.f, 0.f, 0.f);

	Vector3 minimapcoords;
	Vector3 minimapsoracoords;



	Camera3();
	~Camera3();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt, float bounds);
	virtual void SJUpdate(double dt, float bounds);
	virtual void Reset();

	
	void XWingCamera(double dt, float bounds);
	void UpdateCollision(float bounds, double dt);

	bool SceneSoraJewel = false;
	bool SceneMun = false;
	bool SceneGalaxy = false;
	bool boundaryCheckerX(float smallx, float largex, float smallz, float largez, Vector3 value);
	bool boundaryCheckerZ(float smallx, float largex, float smallz, float largez, Vector3 value);
	bool OBJboundaryX(Vector3 Testvalue);
	bool OBJboundaryZ(Vector3 Testvalue);
	bool OBJboundaryY(Vector3 Testvalue, int XZ);
	bool AllMunBoundaryX(Vector3 Testvalue);
	bool AllMunBoundaryZ(Vector3 Testvalue);
	bool AllSoraJewelBoundaryX(Vector3 Testvalue);
	bool AllSoraJewelBoundaryZ(Vector3 Testvalue);
	bool OnGround();

	bool jump = false;
	bool wherecube = true;

	float rotateChar;
	float translateChar;

	float Force;
	float mass;
	float gravity;
	float acceleration;
	float speed;

};

#endif