/******************************************************************************/
/*!
\file Missile.cpp
\author Li Zhaoyuan, Nathan Chia Shi-Lin, Terence Tan Ming Jie, Muhammad Nurhidayat Bin Suderman
\par email: lizhaoyuan123@hotmail.com
\brief
SceneGalaxy cpp file, everything needed inside the scene, found here
*/
/******************************************************************************/
#include "Missile.h"

/****************************************************************************/
/*!
\brief
	constructor of Missile.cpp
*/
/****************************************************************************/
Missile::Missile()
{
}

/****************************************************************************/
/*!
\brief
	copy constructor to initialize variables
\param
	const int reference AmmoInMag
*/
/****************************************************************************/
Missile::Missile(const int &AmmoInMag)
{	
	Missiles = AmmoInMag;
	Capacity = new Missile[AmmoInMag];
}

/****************************************************************************/
/*!
\brief
	deconstructor of the Missile.cpp
*/
/****************************************************************************/
Missile::~Missile()
{
}

/****************************************************************************/
/*!
\brief
	position set for the missile
\param
	const Vector3 reference position
*/
/****************************************************************************/
void Missile::updatePosition(const Vector3 &pos)
{
	position.x = 0;
	position.y = 495;
	position.z = 0;
}

/****************************************************************************/
/*!
\brief
	return position
\return
	return position from update
*/
/****************************************************************************/
Vector3 Missile::getPositionOfMissile()
{
	return position;
}

/****************************************************************************/
/*!
\brief
	setting this cpp view as camera.view
\param
	const Vector3 reference view
*/
/****************************************************************************/
void Missile::setView(const Vector3 &view)
{
	this->view = view;
}

/****************************************************************************/
/*!
\brief
	animation for the missile
\param
	double dt
*/
/****************************************************************************/
void Missile::Animation(double dt)
{
	float speed = 750.f;
	position += view * speed * dt;
	if (position.x > 750 || position.y > 750 || position.z > 750|| position.x < -750 || position.y < -750 || position.z < -750)
	{
		view = Vector3(0, 0, 0);
	}
}

/****************************************************************************/
/*!
\brief

\param
	Camera3 pointer
*/
/****************************************************************************/
void Missile::init(Camera3 *target)
{
	camera = target;
}

/****************************************************************************/
/*!
\brief
	missiles will update position and view
*/
/****************************************************************************/
void Missile::Firing()
{
	if (MissileUsed < Missiles)
	{
		Capacity[MissileUsed].updatePosition(camera->target);
		Capacity[MissileUsed].setView(camera->view);
		MissileUsed++;

	}
	else
	{
		MissileUsed = 0;
	}
}

/****************************************************************************/
/*!
\brief
	getting position of the position, missile will update and animate
\param
	double dt
*/
/****************************************************************************/
void Missile::update(double dt)
{
	for (int i = 0; i < Missiles; ++i)
	{
		if (Capacity[i].getPositionOfMissile() != Vector3(0, -10, 0))
		{
			Capacity[i].Animation(dt);
		}
	}
}



