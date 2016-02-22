#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"



Camera3::Camera3()
{
}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	translateChar = 0;
	rotateChar = 0;
	minimapcoords = (60.f, 10.f, -1.f);
	minimapsoracoords = (78.f, 55.f, -1.f);
	SetCursorPos( 800 / 2, 600 / 2);
}

void Camera3::Update(double dt, float bounds)
{
	POINT mousecursor;
	static const float CAMERA_SPEED = 25.f;
	
	GetCursorPos(&mousecursor);
	if ((Application::IsKeyPressed(VK_LEFT)))
	{
		float yaw = (float)(CAMERA_SPEED * 2 * dt);
		rotateChar += yaw;
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = position + view;
		up = rotation * up;	
	}
	
	if (Application::IsKeyPressed('A'))
	{
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();

		Vector3 Testvalue;
		Testvalue = (position + view * dt * CAMERA_SPEED);

		if (position.x - (right.x * (float)(CAMERA_SPEED * dt)) > -bounds
			&& position.x - (right.x * (float)(CAMERA_SPEED * dt)) < bounds
			&& OBJboundaryX(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 1) == true)
			{
				position.x -= right.x * (float)(CAMERA_SPEED * dt);
				target.x -= right.x * (float)(CAMERA_SPEED * dt);
				minimapcoords.y += (right.x*(float)(CAMERA_SPEED*dt*0.1));
				minimapsoracoords.x += (right.x*(float)(CAMERA_SPEED*dt*0.1));
			}
		}
		if (position.z - (right.z * (float)(CAMERA_SPEED * dt)) > -bounds
			&& position.z - (right.z * (float)(CAMERA_SPEED * dt)) < bounds
			&& OBJboundaryZ(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 2) == true)
			{
				position.z -= right.z * (float)(CAMERA_SPEED * dt);
				target.z -= right.z * (float)(CAMERA_SPEED * dt);
				minimapcoords.x += (right.z*(float)(CAMERA_SPEED*dt*0.1));
				minimapsoracoords.y += (right.z*(float)(CAMERA_SPEED*dt*0.1));
			}
		}

	}
	if (Application::IsKeyPressed(VK_RIGHT))
	{
		float yaw = (float)(-CAMERA_SPEED * 2 * dt);
		rotateChar += yaw;
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = position + view;
		up = rotation * up;
			
	}

	if (Application::IsKeyPressed('D'))
	{
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();

		Vector3 Testvalue;
		Testvalue = (position + view * dt * CAMERA_SPEED);

		if (position.x + (right.x * (float)(CAMERA_SPEED * dt)) > -bounds
			&& position.x + (right.x * (float)(CAMERA_SPEED * dt)) < bounds
			&& OBJboundaryX(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 1) == true)
			{
				position.x += right.x * (float)(CAMERA_SPEED * dt);
				target.x += right.x * (float)(CAMERA_SPEED * dt);
				minimapcoords.y -= (right.x*(float)(CAMERA_SPEED*dt*0.1));
				minimapsoracoords.x += (right.x*(float)(CAMERA_SPEED*dt*0.1));
			}
		}
		if (position.z + (right.z * (float)(CAMERA_SPEED * dt)) > -bounds
			&& position.z + (right.z * (float)(CAMERA_SPEED * dt)) < bounds
			&& OBJboundaryZ(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 2) == true)
			{
				position.z += right.z * (float)(CAMERA_SPEED * dt);
				target.z += right.z * (float)(CAMERA_SPEED * dt);
				minimapcoords.x -= (right.z*(float)(CAMERA_SPEED*dt*0.1));
				minimapsoracoords.y -= (right.z*(float)(CAMERA_SPEED*dt*0.1));
			}
		}
	}
	if (Application::IsKeyPressed(VK_UP))
	{
		if (target.y < (position.y + 0.8))
		{
			float pitch = (float)(CAMERA_SPEED * 2 * dt);
			Vector3 view = (target - position).Normalized();
			Vector3 right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(view).Normalized();
			if (view.y < 0.984)
			{
				Mtx44 rotation;
				rotation.SetToRotation(pitch, right.x, right.y, right.z);
				view = rotation * view;
				target = view + position;
			}
		}
			
	}

	if (Application::IsKeyPressed('W'))
	{
		Vector3 view = (target - position).Normalized();

		Vector3 Testvalue;
		Testvalue = (position + view * dt * CAMERA_SPEED);

		if (position.x + (view.x * (float)(CAMERA_SPEED * dt)) > -bounds
			&& position.x + (view.x * (float)(CAMERA_SPEED * dt)) < bounds
			&& OBJboundaryX(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 1) == true)
			{
				position.x += view.x * (float)(CAMERA_SPEED * dt);
				target.x += view.x * (float)(CAMERA_SPEED * dt); 
				minimapcoords.y -= (view.x*(float)(CAMERA_SPEED*dt*0.1));
				minimapsoracoords.x += (view.x*(float)(CAMERA_SPEED*dt*0.1));
			}
		}
		if (position.z + (view.z * (float)(CAMERA_SPEED * dt)) > -bounds
			&& position.z + (view.z * (float)(CAMERA_SPEED * dt)) < bounds
			&& OBJboundaryZ(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 2) == true)
			{
				position.z += view.z * (float)(CAMERA_SPEED * dt);
				target.z += view.z * (float)(CAMERA_SPEED * dt);
				minimapcoords.x -= (view.z*(float)(CAMERA_SPEED*dt*0.1));
				minimapsoracoords.y -= (view.z*(float)(CAMERA_SPEED*dt*0.1));
			}
		}
	}
	if (Application::IsKeyPressed(VK_DOWN))
	{
		if (target.y > position.y -0.8)
		{
			float pitch = (float)(-CAMERA_SPEED * dt);
			Vector3 view = (target - position).Normalized();
			Vector3 right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(view).Normalized();
			Mtx44 rotation;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			view = rotation * view;
			target = view + position;
		}
			
	}
	if (Application::IsKeyPressed('S'))
	{
		Vector3 view = (target - position).Normalized();

		Vector3 Testvalue;
		Testvalue = (position - view * dt * CAMERA_SPEED);

		if (position.x - (view.x * (float)(CAMERA_SPEED * dt)) > -bounds
			&& position.x - (view.x * (float)(CAMERA_SPEED * dt)) < bounds
			&& OBJboundaryX(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 1) == true)
			{
				position.x -= view.x * (float)(CAMERA_SPEED * dt);
				target.x -= view.x * (float)(CAMERA_SPEED * dt);
				minimapcoords.y += (view.x*(float)(CAMERA_SPEED*dt*0.1));
				minimapsoracoords.x += (view.x*(float)(CAMERA_SPEED*dt*0.1));
			}
		}
		if (position.z - (view.z * (float)(CAMERA_SPEED * dt)) > -bounds
			&& position.z - (view.z * (float)(CAMERA_SPEED * dt)) < bounds
			&& OBJboundaryZ(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 2) == true)
			{
				position.z -= view.z * (float)(CAMERA_SPEED * dt);
				target.z -= view.z * (float)(CAMERA_SPEED * dt);
				minimapcoords.x += (view.z*(float)(CAMERA_SPEED*dt*0.1));
				minimapsoracoords.y += (view.z*(float)(CAMERA_SPEED*dt*0.1));

			}
		}
	}
	
	if (Application::IsKeyPressed('R'))
	{
		minimapcoords.x = 75;
		minimapcoords.y = 55;
		minimapsoracoords.x = 78;
		minimapsoracoords.y = 55;
		Reset();
	}
	
	if (mousecursor.x<800 / 2)
	{
		float yaw = (float)(CAMERA_SPEED * 0.5 * dt*(800 / 2 - mousecursor.x));
		rotateChar += yaw;
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = position + view;
		up = rotation * up;
	}
	if (mousecursor.x>800 / 2)
	{
		float yaw = (float)(-CAMERA_SPEED* 0.5 * dt*(mousecursor.x - 800 / 2));
		rotateChar += yaw;
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = position + view;
		up = rotation * up;

	}
	if (mousecursor.y<600 / 2)
	{
		if (target.y < (position.y + 0.8))
		{
			float pitch = (float)(CAMERA_SPEED * 0.5* dt*(600 / 2 - mousecursor.y));
			Vector3 view = (target - position).Normalized();
			Vector3 right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(view).Normalized();

			Mtx44 rotation;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			view = rotation * view;
			target = view + position;
		}

	}
	if (mousecursor.y>600 / 2)
	{
		if (target.y > (position.y - 0.8))
		{
			float pitch = (float)(-CAMERA_SPEED * 0.5 * 2 * dt*(mousecursor.y - 600 / 2));
			Vector3 view = (target - position).Normalized();
			Vector3 right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(view).Normalized();
			Mtx44 rotation;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			view = rotation * view;
			target = view + position;
		}

	}
	view = (target - position).Normalized();
	SetCursorPos(800 / 2, 600 / 2);
}

void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
	view = (target - position).Normalized();
}

void Camera3::UpdateCollision(float bounds, double dt)
{
	static const float CAMERA_SPEED = 25.f;
	if (Application::IsKeyPressed('A'))
	{
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		if (position.x - (right.x * (float)(CAMERA_SPEED * dt)) > -bounds
			&& position.x - (right.x * (float)(CAMERA_SPEED * dt)) < bounds)
		{
			position.x += right.x * (float)(CAMERA_SPEED * dt);
			target.x += right.x * (float)(CAMERA_SPEED * dt);
		}
		if (position.z - (right.z * (float)(CAMERA_SPEED * dt)) > -bounds
			&& position.z - (right.z * (float)(CAMERA_SPEED * dt)) < bounds)
		{
			position.z += right.z * (float)(CAMERA_SPEED * dt);
			target.z += right.z * (float)(CAMERA_SPEED * dt);
		}

	}
	if (Application::IsKeyPressed('D'))
	{
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		if (position.x + (right.x * (float)(CAMERA_SPEED * dt)) > -bounds
			&& position.x + (right.x * (float)(CAMERA_SPEED * dt)) < bounds)
		{
			position.x -= right.x * (float)(CAMERA_SPEED * dt);
			target.x -= right.x * (float)(CAMERA_SPEED * dt);
		}
		if (position.z + (right.z * (float)(CAMERA_SPEED * dt)) > -bounds
			&& position.z + (right.z * (float)(CAMERA_SPEED * dt)) < bounds)
		{
			position.z -= right.z * (float)(CAMERA_SPEED * dt);
			target.z -= right.z * (float)(CAMERA_SPEED * dt);
		}
	}
	if (Application::IsKeyPressed('W'))
	{
		Vector3 view = (target - position).Normalized();
		if (position.x + (view.x * (float)(CAMERA_SPEED * dt)) > -bounds
			&& position.x + (view.x * (float)(CAMERA_SPEED * dt)) < bounds)
		{
			position.x -= view.x * (float)(CAMERA_SPEED * dt);
			target.x -= view.x * (float)(CAMERA_SPEED * dt);
		}
		if (position.z + (view.z * (float)(CAMERA_SPEED * dt)) > -bounds
			&& position.z + (view.z * (float)(CAMERA_SPEED * dt)) < bounds)
		{
			position.z -= view.z * (float)(CAMERA_SPEED * dt);
			target.z -= view.z * (float)(CAMERA_SPEED * dt);
		}
	}
	if (Application::IsKeyPressed('S'))
	{
		Vector3 view = (target - position).Normalized();
		if (position.x - (view.x * (float)(CAMERA_SPEED * dt)) > -bounds
			&& position.x - (view.x * (float)(CAMERA_SPEED * dt)) < bounds)
		{
			position.x += view.x * (float)(CAMERA_SPEED * dt);
			target.x += view.x * (float)(CAMERA_SPEED * dt);
		}
		if (position.z - (view.z * (float)(CAMERA_SPEED * dt)) > -bounds
			&& position.z - (view.z * (float)(CAMERA_SPEED * dt)) < bounds)
		{
			position.z += view.z * (float)(CAMERA_SPEED * dt);
			target.z += view.z * (float)(CAMERA_SPEED * dt);
		}
	}

}

bool Camera3::boundaryCheckerX(float smallx, float largex, float smallz, float largez, Vector3 value)
{
	if ((value.z > smallz) && (value.z<largez) && (value.x > smallx) && (value.x<smallx + 4)){ return false; }
	if ((value.z > smallz) && (value.z<largez) && (value.x < largex) && (value.x>largex - 4)){ return false; }
	return true;
}

bool Camera3::boundaryCheckerZ(float smallx, float largex, float smallz, float largez, Vector3 value)
{
	if ((value.x > smallx) && (value.x<largex) && (value.z > smallz) && (value.z<smallz + 4)){ return false; }
	if ((value.x > smallx) && (value.x<largex) && (value.z < largez) && (value.z>largez - 4)){ return false; }
	return true;
}

bool Camera3::OBJboundaryX(Vector3 Testvalue)
{
	if (SceneGalaxy == true)
	{
		if (AllGalaxyBoundaryX(Testvalue)){ return false; }
	}
	if (SceneMun == true)
	{
		if (AllMunBoundaryX(Testvalue)){ return false; }
	}
	if (SceneSoraJewel == true)
	{
		if (AllSoraJewelBoundaryX(Testvalue)){ return false; }
	}
	return true;
}

bool Camera3::OBJboundaryZ(Vector3 Testvalue)
{
	if (SceneGalaxy == true)
	{
		if (AllGalaxyBoundaryZ(Testvalue)){ return false; }
	}
	if (SceneMun == true)
	{
		if (AllGalaxyBoundaryZ(Testvalue)){ return false; }
	}
	if (SceneSoraJewel == true)
	{
		if (AllSoraJewelBoundaryZ(Testvalue)){ return false; }
	}
	return true;
}

bool Camera3::OBJboundaryY(Vector3 Testvalue, int XZ)
{
	if (SceneGalaxy == true)
	{
		if (Testvalue.y <= 100)
		{
			if (XZ == 1)
			{
				if (AllGalaxyBoundaryX(Testvalue))
				{
					return false;
				}
			}
			else if (XZ == 2)
			{
				if (AllGalaxyBoundaryZ(Testvalue))
				{
					return false;
				}
			}
		}
	}
	if (SceneMun == true)
	{
		if (Testvalue.y <= 100)
		{
			if (XZ == 1)
			{
				if (AllMunBoundaryX(Testvalue))
				{
					return false;
				}
			}
			else if (XZ == 2)
			{
				if (AllMunBoundaryZ(Testvalue))
				{
					return false;
				}
			}
		}
	}
	if (SceneSoraJewel == true)
	{

		if (Testvalue.y >= 20)

		if (Testvalue.y <= 100)

		{
			if (XZ == 1)
			{
				if (AllSoraJewelBoundaryX(Testvalue))
				{
					return false;
				}
			}
			else if (XZ == 2)
			{
				if (AllSoraJewelBoundaryZ(Testvalue))
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool Camera3::AllGalaxyBoundaryX(Vector3 Testvalue)
{
	if (!boundaryCheckerX(20, 50, 20, 50, Testvalue))
		return true;
	return false;
}

bool Camera3::AllGalaxyBoundaryZ(Vector3 Testvalue)
{
	if (!boundaryCheckerZ(20, 50, 20, 50, Testvalue))
		return true;
	return false;
}

bool Camera3::AllMunBoundaryX(Vector3 Testvalue)
{
	if (!boundaryCheckerX(2, 50, -50, -26, Testvalue))
		return true;
	if (!boundaryCheckerX(-39, -32, -38, -28, Testvalue))
		return true;
	return false;
}

bool Camera3::AllMunBoundaryZ(Vector3 Testvalue)
{
	if (!boundaryCheckerZ(2, 50, -50, -26, Testvalue))
		return true;
	if (!boundaryCheckerZ(-39, -32, -38, -28, Testvalue))
		return true;
	return false;
}

bool Camera3::AllSoraJewelBoundaryX(Vector3 Testvalue)
{
	if (!boundaryCheckerX(-0.4f, 50, -79, -27, Testvalue))
		return true;
	return false;
}

bool Camera3::AllSoraJewelBoundaryZ(Vector3 Testvalue)
{
	if (!boundaryCheckerZ(-0.4f, 50, -79, -27, Testvalue))
		return true;
	return false;
}