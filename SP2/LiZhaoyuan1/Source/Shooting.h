#ifndef SHOOTING_H
#define SHOOTING_H

#include "Camera3.h"
#include "SceneGalaxy.h"
#include <vector>
#include "Vector3.h"
#include "Missile.h"

class Shooting : public Missile
{
public:
	Shooting(const int &AmmoInMag);
	~Shooting();
	void init(Camera3 *target);
	void Firing();
	void update(double dt);


	int AmmoInClip;
	int bulletCount = 0;
	Missile* Capacity;

private:
	Camera3 *camera;
};

#endif //SHOOTING_H