/****************************************************************************/
/*!
\file Missile.h
\author Li Zhaoyuan, Nathan Chia Shi-Lin, Terence Tan Ming Jie, Muhammad Nurhidayat Bin Suderman
\par email: lizhaoyuan123@hotmail.com
\brief
	class for the shooting of missile
*/
/****************************************************************************/

#ifndef MISSILE_H
#define MISSILE_H

#include "Vector3.h"
#include "Camera3.h"

/******************************************************************************/
/*!
Class Missile:
\brief	Defines Missile and its methods
*/
/******************************************************************************/
class Missile
{
public:
	Missile();
	Missile(const int &AmmoInMag);
	~Missile();
	Vector3 getPositionOfMissile();
	void updatePosition(const Vector3 &pos);
	void setView(const Vector3 &view);

	Vector3 position;
	Vector3 missilePosition;

	void Animation(double dt);
	void init(Camera3 *target);
	void Firing();
	void update(double dt);

	int Missiles;
	int MissileUsed = 100;
	int delay = 0;
	Missile* Capacity;


private:
	Vector3 view;
	Camera3 *camera;

};

#endif