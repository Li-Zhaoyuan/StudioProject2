#include "XwingCamera.h"
#include "Application.h"
#include "Mtx44.h"



XwingCamera::XwingCamera()
{
}

XwingCamera::~XwingCamera()
{
}

void XwingCamera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
}

void XwingCamera::Update(double dt, float bounds)
{

	if (Application::IsKeyPressed('R'))
	{
		Reset();
	}
}

void XwingCamera::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
	view = (target - position).Normalized();
}