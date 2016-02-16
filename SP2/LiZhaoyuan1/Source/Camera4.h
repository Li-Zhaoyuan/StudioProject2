#ifndef CAMERA_4_H
#define CAMERA_4_H

#include "Camera.h"
#include "Application.h"

class Camera4 : public Camera
{
public:
	//Vector3 position;
	//Vector3 target;
	//Vector3 up;

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;

	Camera4();
	~Camera4();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt, float bounds);
	virtual void Reset();

	void UpdateCollision(float bounds, double dt);

	float rotateChar;

	//angle of rotation
	float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, zrot = 0;
	float Charradius=10.f; //radial distance from character
	float lastx, lasty;

	//keyboard ctrls
	void keyboard(int x, int y);
};


#endif