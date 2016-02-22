#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "Camera.h"
#include "Application.h"

class XwingCamera : public Camera
{
public:
	//Vector3 position;
	//Vector3 target;
	//Vector3 up;

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;

	XwingCamera();
	~XwingCamera();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt, float bounds);
	virtual void Reset();

	void UpdateCollision(float bounds, double dt);

	bool SceneSoraJewel = false;
	bool SceneMun = false;
	bool SceneGalaxy = false;

	float rotateChar;
	float translateChar;

};

#endif