/******************************************************************************/
/*!
\file Camera3.cpp
\author Li Zhaoyuan, Nathan Chia Shi-Lin, Terence Tan Ming Jie, Muhammad Nurhidayat Bin Suderman
\par email: lizhaoyuan123@hotmail.com
\brief
Camera
*/
/******************************************************************************/
#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"
#include "Physics.h"

/****************************************************************************/
/*!
\brief
	constructor for Camera3.cpp file
*/
/****************************************************************************/
Camera3::Camera3()
{
}

/****************************************************************************/
/*!
\brief
	deconstructor for Camera3.cpp file
*/
/****************************************************************************/
Camera3::~Camera3()
{
}

/****************************************************************************/
/*!
\brief
	Camera3 initializer
*/
/****************************************************************************/
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
	//minimapcoords = (78.f, 55.f, -1.f);
	minimapsoracoords = (78.f,55.f, -1.f);;
	SetCursorPos( 800 / 2, 600 / 2);
	mass = 70;
	Force = 1000;
	speed = 0.f;
	gravity = -2.f;
}

/****************************************************************************/
/*!
\brief
	running functions, checks, keypress in the .cpp file every frame
*/
/****************************************************************************/
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

	if (Application::IsKeyPressed('A')) /////
	{
		float speed = 5.0f;
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		view.y = 0;

		Vector3 Testvalue;
		Testvalue = (position + right * dt * -CAMERA_SPEED);

		if ((position + right * dt * -CAMERA_SPEED).x < bounds && (position + right * dt * -CAMERA_SPEED).x > -bounds && OBJboundaryX(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 1) == true)
			{
				position.x -= right.x * (float)(CAMERA_SPEED * dt);
				target.x -= right.x * (float)(CAMERA_SPEED * dt);
				minimapcoords.y += (right.x*(float)(CAMERA_SPEED*dt*0.1));
			}
		}
		if ((position + right * dt * -CAMERA_SPEED).z < bounds && (position + right * dt * -CAMERA_SPEED).z > -bounds && OBJboundaryZ(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 2) == true)
			{
				position.z += (float)(right.z * dt * -CAMERA_SPEED);
				target.z += right.z * dt * -CAMERA_SPEED;
				minimapcoords.x += (right.z*(float)(CAMERA_SPEED*dt*0.1));
			}
		}
	}
	if (Application::IsKeyPressed('D'))  ///////
	{
		float speed = 5.0f;
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		view.y = 0;

		Vector3 Testvalue;
		Testvalue = (position + right * dt * CAMERA_SPEED);

		if ((position + right * dt * CAMERA_SPEED).x < bounds && (position + right * dt * CAMERA_SPEED).x > -bounds && OBJboundaryX(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 1) == true)
			{
				position.x += right.x * dt * CAMERA_SPEED;
				target.x += right.x * dt * CAMERA_SPEED;
				minimapcoords.y -= (right.x*(float)(CAMERA_SPEED*dt*0.1));
			}
		}
		if ((position + right * dt * CAMERA_SPEED).z < bounds && (position + right * dt * CAMERA_SPEED).z > -bounds && OBJboundaryZ(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 2) == true)
			{
				position.z += right.z * dt * CAMERA_SPEED;
				target.z += right.z * dt * CAMERA_SPEED;
				minimapcoords.x -= (right.z*(float)(CAMERA_SPEED*dt*0.1));
			}
		}
	}
	if (Application::IsKeyPressed('W'))
	{
		float speed = 20.0f;
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		view.y = 0;

		Vector3 Testvalue;
		Testvalue = (position + view * dt * CAMERA_SPEED);

		if ((position + view * dt * CAMERA_SPEED).x < bounds && (position + view * dt * CAMERA_SPEED).x > -bounds && OBJboundaryX(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 1) == true)
			{
				position.x += view.x * dt * CAMERA_SPEED;
				target.x += view.x * dt * CAMERA_SPEED;
				minimapcoords.y -= (view.x*(float)(CAMERA_SPEED*dt*0.1));
			}
		}
		if ((position + view * dt * CAMERA_SPEED).z < bounds && (position + view * dt * CAMERA_SPEED).z > -bounds && OBJboundaryZ(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 2) == true)
			{
				position.z += view.z * dt * CAMERA_SPEED;
				target.z += view.z * dt * CAMERA_SPEED;
				minimapcoords.x -= (view.z*(float)(CAMERA_SPEED*dt*0.1));
			}
		}

	}
	if (Application::IsKeyPressed('S'))
	{
		float speed = -20.0f;
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		view.y = 0;

		Vector3 Testvalue;
		Testvalue = (position + view * dt * -CAMERA_SPEED);

		if ((position + view * dt * -CAMERA_SPEED).x < bounds && (position + view * dt * -CAMERA_SPEED).x > -bounds && OBJboundaryX(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 1) == true)
			{
				position.x += view.x * dt * -CAMERA_SPEED;
				target.x += view.x * dt * -CAMERA_SPEED;
				minimapcoords.y += (view.x*(float)(CAMERA_SPEED*dt*0.1));
			}
		}
		if ((position + view * dt * -CAMERA_SPEED).z < bounds && (position + view * dt * -CAMERA_SPEED).z > -bounds && OBJboundaryZ(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 2) == true)
			{
				position.z += view.z * dt * -CAMERA_SPEED;
				target.z += view.z * dt * -CAMERA_SPEED;
				minimapcoords.x += (view.z*(float)(CAMERA_SPEED*dt*0.1));
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

/****************************************************************************/
/*!
\brief
	reset the camera settings to default
*/
/****************************************************************************/
void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
	view = (target - position).Normalized();
}

/****************************************************************************/
/*!
\brief
	
\param
	boundary, double dt
*/
/****************************************************************************/
void Camera3::UpdateCollision(float bounds, double dt)
{
	static const float CAMERA_SPEED = 25.f;
	if (Application::IsKeyPressed('A'))  /////
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
			minimapcoords.y += (right.x*(float)(CAMERA_SPEED*dt*0.1));
		}
		if (position.z - (right.z * (float)(CAMERA_SPEED * dt)) > -bounds
			&& position.z - (right.z * (float)(CAMERA_SPEED * dt)) < bounds)
		{
			position.z += right.z * (float)(CAMERA_SPEED * dt);
			target.z += right.z * (float)(CAMERA_SPEED * dt);
			minimapcoords.x += (right.z*(float)(CAMERA_SPEED*dt*0.1));
		}

	}
	if (Application::IsKeyPressed('D'))  ///////
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
			minimapcoords.y -= (right.x*(float)(CAMERA_SPEED*dt*0.1));
		}
		if (position.z + (right.z * (float)(CAMERA_SPEED * dt)) > -bounds
			&& position.z + (right.z * (float)(CAMERA_SPEED * dt)) < bounds)
		{
			position.z -= right.z * (float)(CAMERA_SPEED * dt);
			target.z -= right.z * (float)(CAMERA_SPEED * dt);
			minimapcoords.x -= (right.z*(float)(CAMERA_SPEED*dt*0.1));
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
			minimapcoords.y -= (view.x*(float)(CAMERA_SPEED*dt*0.1));
		}
		if (position.z + (view.z * (float)(CAMERA_SPEED * dt)) > -bounds
			&& position.z + (view.z * (float)(CAMERA_SPEED * dt)) < bounds)
		{
			position.z -= view.z * (float)(CAMERA_SPEED * dt);
			target.z -= view.z * (float)(CAMERA_SPEED * dt);
			minimapcoords.x -= (view.z*(float)(CAMERA_SPEED*dt*0.1));
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
			minimapcoords.y += (view.x*(float)(CAMERA_SPEED*dt*0.1)); //
		}
		if (position.z - (view.z * (float)(CAMERA_SPEED * dt)) > -bounds
			&& position.z - (view.z * (float)(CAMERA_SPEED * dt)) < bounds)
		{
			position.z += view.z * (float)(CAMERA_SPEED * dt);
			target.z += view.z * (float)(CAMERA_SPEED * dt);
			minimapcoords.x += (view.z*(float)(CAMERA_SPEED*dt*0.1));
		}
	}

}

/****************************************************************************/
/*!
\brief
	XWing Camera with the limitation view angle
\param
	double dt, boundary
*/
/****************************************************************************/
void Camera3::XWingCamera(double dt, float bounds)
{
	POINT mousecursor;
	static const float CAMERA_SPEED = 5.f;
	GetCursorPos(&mousecursor);

	if (Application::IsKeyPressed('R'))
	{
		Reset();
	}
	if (mousecursor.x<800 / 2)
	{
		if (target.x >(position.x - 0.4))
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
	}
	if (mousecursor.x>800 / 2)
	{
		if (target.x < (position.x + 0.4))
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
	}
	if (mousecursor.y<600 / 2)
	{
		if (target.y < (position.y + 0.4))
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
		if (target.y > (position.y - 0.4))
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

/****************************************************************************/
/*!
\brief
	formula for X checker
\param
	minimum x, maximum x, minimum z, maximum z, vector3 value
\return
	true/false
*/
/****************************************************************************/
bool Camera3::boundaryCheckerX(float smallx, float largex, float smallz, float largez, Vector3 value)
{
	if ((value.z > smallz) && (value.z < largez) && (value.x > smallx) && (value.x < smallx + 6)){ return false; }
	if ((value.z > smallz) && (value.z < largez) && (value.x < largex) && (value.x > largex - 6)){ return false; }
	return true;
}

/****************************************************************************/
/*!
\brief
	formula for Z checker
\param
	minimum x, maximum x, minimum z, maximum z, vector3 value
\return
	true/false
*/
/****************************************************************************/
bool Camera3::boundaryCheckerZ(float smallx, float largex, float smallz, float largez, Vector3 value)
{
	if ((value.x > smallx) && (value.x < largex) && (value.z > smallz) && (value.z < smallz + 6)){ return false; }
	if ((value.x > smallx) && (value.x < largex) && (value.z < largez) && (value.z > largez - 6)){ return false; }
	return true;
}

/****************************************************************************/
/*!
\brief
	X Coord Boundary
\param
	Testvalue (value of current camera.position)
\return
	true/false
*/
/****************************************************************************/
bool Camera3::OBJboundaryX(Vector3 Testvalue)
{
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

/****************************************************************************/
/*!
\brief
	Z Coord Boundary
\param
	Testvalue (value of current camera.position)
\return
	true/false
*/
/****************************************************************************/
bool Camera3::OBJboundaryZ(Vector3 Testvalue)
{
	if (SceneMun == true)
	{
		if (AllMunBoundaryZ(Testvalue)){ return false; }
	}
	if (SceneSoraJewel == true)
	{
		if (AllSoraJewelBoundaryZ(Testvalue)){ return false; }
	}
	return true;
}

/****************************************************************************/
/*!
\brief
	Y Coord Boundary
\param
	Testvalue (value of current camera.position) and int XZ
\return
	true/false
*/
/****************************************************************************/
bool Camera3::OBJboundaryY(Vector3 Testvalue, int XZ)
{
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

		if (Testvalue.y <= 7)
		{
			if (XZ == 1)
			{
				if (!boundaryCheckerX(-110, 59, -1, 0, Testvalue))
				{
					return false;
				}
			}
			else if (XZ == 2)
			{
				if (!boundaryCheckerZ(-110, 59, -1, 0, Testvalue))
				{
					return false;
				}
			}
		}
	}
	return true;
}

/****************************************************************************/
/*!
\brief
	inputting Mun Coord for X checker
\param
	Testvalue (value of current camera.position)
\return
	true/false
*/
/****************************************************************************/
bool Camera3::AllMunBoundaryX(Vector3 Testvalue)
{
	//women's house
	if (!boundaryCheckerX(0, 50, -50, -26, Testvalue))
		return true;
	//crashed plane
	if (!boundaryCheckerX(-39, -32, -51, -44, Testvalue))
		return true;
	//quest dude house
	if (!boundaryCheckerX(20, 44, 0, 48, Testvalue))
		return true;
	//cave left wall
	if (!boundaryCheckerX(-47, -18, 22, 29, Testvalue))
		return true;
	//cave center wall
	if (!boundaryCheckerX(-48, -40.5, 26, 45, Testvalue))
		return true;
	//cave right wall
	if (!boundaryCheckerX(-48, -20, 41, 48, Testvalue))
		return true;
	return false;
}

/****************************************************************************/
/*!
\brief
	inputting Mun Coord for Z checker
\param
	Testvalue (value of current camera.position)
\return
	true/false
*/
/****************************************************************************/
bool Camera3::AllMunBoundaryZ(Vector3 Testvalue)
{
	//women's house
	if (!boundaryCheckerZ(0, 50, -50, -26, Testvalue))
		return true; 
	//crashed plane
	if (!boundaryCheckerZ(-39, -32, -51, -44, Testvalue))
		return true;
	//quest dude house
	if (!boundaryCheckerZ(20, 44, 0, 48, Testvalue))
		return true;
	//cave left wall
	if (!boundaryCheckerZ(-47, -18, 22, 29, Testvalue))
		return true;
	//cave center wall
	if (!boundaryCheckerZ(-48, -40.5, 26, 45, Testvalue))
		return true;
	//cave right wall
	if (!boundaryCheckerZ(-48, -20, 41, 48, Testvalue))
		return true;
	return false;
}

/****************************************************************************/
/*!
\brief
	inputting SoraJewel Coord for X checker
\param
	Testvalue (value of current camera.position)
\return
	true/false
*/
/****************************************************************************/
bool Camera3::AllSoraJewelBoundaryX(Vector3 Testvalue)
{
	if (!boundaryCheckerX(0.2f, 50, -78, -28, Testvalue))
		return true;
	if (!boundaryCheckerX(-57, -43, -111, -97, Testvalue))
		return true;
	if (!boundaryCheckerX(-111, -75, -111, -85, Testvalue))
		return true;
	return false;
}

/****************************************************************************/
/*!
\brief
	inputting SoraJewel Coord for Z checker
\param
	Testvalue (value of current camera.position)
\return
	true/false
*/
/****************************************************************************/
bool Camera3::AllSoraJewelBoundaryZ(Vector3 Testvalue)
{
	if (!boundaryCheckerZ(0.2f, 50, -78, -28, Testvalue))
		return true;
	if (!boundaryCheckerZ(-57, -43, -111, -97, Testvalue))
		return true;
	if (!boundaryCheckerZ(-111, -75, -111, -85, Testvalue))
		return true;
	return false;
}

/****************************************************************************/
/*!
\brief

\param

\return

*/
/****************************************************************************/
void Camera3::SJUpdate(double dt, float maxboundsx, float minboundsx, float minboundsz, float maxboundsz)
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

	if (Application::IsKeyPressed('A')) /////
	{
		float speed = 5.0f;
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		view.y = 0;

		Vector3 Testvalue;
		Testvalue = (position + right * dt * -CAMERA_SPEED);
		if (position.x - (right.x * (float)(CAMERA_SPEED * dt)) > minboundsx
			&& position.x - (right.x * (float)(CAMERA_SPEED * dt)) < maxboundsx
			&& OBJboundaryX(Testvalue) == true)
		if ((position + right * dt * -CAMERA_SPEED).x < maxboundsx && (position + right * dt * -CAMERA_SPEED).x > minboundsx && OBJboundaryX(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 1) == true)
			{
				position.x -= right.x * (float)(CAMERA_SPEED * dt);
				target.x -= right.x * (float)(CAMERA_SPEED * dt);
				minimapcoords.y += (right.x*(float)(CAMERA_SPEED*dt*0.1)); //A x
				minimapsoracoords.x -= (right.x*(float)(CAMERA_SPEED*dt*0.05f));
			}
		}
		if (position.z - (right.z * (float)(CAMERA_SPEED * dt)) > minboundsz
			&& position.z - (right.z * (float)(CAMERA_SPEED * dt)) < maxboundsz
			&& OBJboundaryZ(Testvalue) == true)
		if ((position + right * dt * -CAMERA_SPEED).z < maxboundsz && (position + right * dt * -CAMERA_SPEED).z > minboundsz && OBJboundaryZ(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 2) == true)
			{
				position.z += (float)(right.z * dt * -CAMERA_SPEED);
				target.z += right.z * dt * -CAMERA_SPEED;
				minimapcoords.x += (right.z*(float)(CAMERA_SPEED*dt*0.1)); //A z
				minimapsoracoords.y += (right.z*(float)(CAMERA_SPEED*dt*0.05f*(10.f / 11.f)));
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

	if (Application::IsKeyPressed('D'))  ///////
	{
		float speed = 5.0f;
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		view.y = 0;

		Vector3 Testvalue;
		Testvalue = (position + right * dt * CAMERA_SPEED);
		if (position.x + (right.x * (float)(CAMERA_SPEED * dt)) > minboundsx
			&& position.x + (right.x * (float)(CAMERA_SPEED * dt)) < maxboundsx
			&& OBJboundaryX(Testvalue) == true)
		if ((position + right * dt * CAMERA_SPEED).x < maxboundsx && (position + right * dt * CAMERA_SPEED).x > minboundsx && OBJboundaryX(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 1) == true)
			{
				position.x += right.x * dt * CAMERA_SPEED;
				target.x += right.x * dt * CAMERA_SPEED;
				minimapcoords.y -= (right.x*(float)(CAMERA_SPEED*dt*0.1)); //D x
				minimapsoracoords.x += (right.x*(float)(CAMERA_SPEED*dt*0.05f));
			}
		}
		if (position.z + (right.z * (float)(CAMERA_SPEED * dt)) > minboundsz
			&& position.z + (right.z * (float)(CAMERA_SPEED * dt)) < maxboundsz
			&& OBJboundaryZ(Testvalue) == true)
		if ((position + right * dt * CAMERA_SPEED).z < maxboundsz && (position + right * dt * CAMERA_SPEED).z > minboundsz && OBJboundaryZ(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 2) == true)
			{
				position.z += right.z * dt * CAMERA_SPEED;
				target.z += right.z * dt * CAMERA_SPEED;
				minimapcoords.x -= (right.z*(float)(CAMERA_SPEED*dt*0.1)); //D z
				minimapsoracoords.y -= (right.z*(float)(CAMERA_SPEED*dt*0.05f*(10.f / 11.f)));
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
		float speed = 20.0f;
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		view.y = 0;

		Vector3 Testvalue;
		Testvalue = (position + view * dt * CAMERA_SPEED);
		if (position.x + (view.x * (float)(CAMERA_SPEED * dt)) > minboundsx
			&& position.x + (view.x * (float)(CAMERA_SPEED * dt)) < maxboundsx
			&& OBJboundaryX(Testvalue) == true)
		if ((position + view * dt * CAMERA_SPEED).x < maxboundsx && (position + view * dt * CAMERA_SPEED).x > minboundsx && OBJboundaryX(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 1) == true)
			{
				position.x += view.x * dt * CAMERA_SPEED;
				target.x += view.x * dt * CAMERA_SPEED;
				minimapcoords.y -= (view.x*(float)(CAMERA_SPEED*dt*0.1));//W x
				minimapsoracoords.x += (view.x*(float)(CAMERA_SPEED*dt*0.05f));
			}
		}
		if (position.z + (view.z * (float)(CAMERA_SPEED * dt)) > minboundsz
			&& position.z + (view.z * (float)(CAMERA_SPEED * dt)) < maxboundsz
			&& OBJboundaryZ(Testvalue) == true)
		if ((position + view * dt * CAMERA_SPEED).z < maxboundsz && (position + view * dt * CAMERA_SPEED).z > minboundsz && OBJboundaryZ(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 2) == true)
			{
				position.z += view.z * dt * CAMERA_SPEED;
				target.z += view.z * dt * CAMERA_SPEED;
				minimapcoords.x -= (view.z*(float)(CAMERA_SPEED*dt*0.1)); //W z
				minimapsoracoords.y -= (view.z*(float)(CAMERA_SPEED*dt*0.05f*(10.f / 11.f)));
			}
		}

	}
	if (Application::IsKeyPressed(VK_DOWN))
	{
		if (target.y > position.y - 0.8)
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
		float speed = -20.0f;
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		view.y = 0;

		Vector3 Testvalue;
		Testvalue = (position + view * dt * -CAMERA_SPEED);
		if (position.x - (view.x * (float)(CAMERA_SPEED * dt)) > minboundsx
			&& position.x - (view.x * (float)(CAMERA_SPEED * dt)) < maxboundsx
			&& OBJboundaryX(Testvalue) == true)
		if ((position + view * dt * -CAMERA_SPEED).x < maxboundsx && (position + view * dt * -CAMERA_SPEED).x > minboundsx && OBJboundaryX(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 1) == true)
			{
				position.x += view.x * dt * -CAMERA_SPEED;
				target.x += view.x * dt * -CAMERA_SPEED;
				minimapcoords.y += (view.x*(float)(CAMERA_SPEED*dt*0.1));//S x
				minimapsoracoords.x += (view.x*(float)(CAMERA_SPEED*dt*0.05f));
			}
		}
		if (position.z - (view.z * (float)(CAMERA_SPEED * dt)) > minboundsz
			&& position.z - (view.z * (float)(CAMERA_SPEED * dt)) < maxboundsz
			&& OBJboundaryZ(Testvalue) == true)
		if ((position + view * dt * -CAMERA_SPEED).z < maxboundsz && (position + view * dt * -CAMERA_SPEED).z > minboundsz && OBJboundaryZ(Testvalue) == true)
		{
			if (OBJboundaryY(Testvalue, 2) == true)
			{
				position.z += view.z * dt * -CAMERA_SPEED;
				target.z += view.z * dt * -CAMERA_SPEED;
				minimapcoords.x += (view.z*(float)(CAMERA_SPEED*dt*0.1));// S z
				minimapsoracoords.y += (view.z*(float)(CAMERA_SPEED*dt*0.05f*(10.f / 11.f)));
			}
		}
	}

	if (Application::IsKeyPressed('R'))
	{
		minimapcoords.x = 78.9;
		minimapcoords.y = 59.9;
		minimapsoracoords.x = 78.9f; 
		minimapsoracoords.y = 53.9f;
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

	if (Application::IsKeyPressed(VK_SPACE))
	{
		if (speed == 0.f)
			speed = 50.f * dt;
	}

	position.y += speed;
	target.y += speed;
	speed += gravity * dt;

	if (OnGround())
	{
		speed = 0.f;
	}
	OnGround();
}

/****************************************************************************/
/*!
\brief

\param

\return

*/
/****************************************************************************/
bool Camera3::OnGround()
{
	if (position.y <= 25 && (position.x >= -117 && position.z >= 30) && (position.x <= -51 && position.z <= 100))
		return true;
	if (position.y <= 5 && (position.x >= -140 && position.z >= 0) && (position.x <= 61 && position.z <= 113))
		return true;
	else if (position.y <= 10 && (position.x >= -140 && position.z >= -112) && (position.x <= 62 && position.z <= 0))
		return true;

	return false;
}