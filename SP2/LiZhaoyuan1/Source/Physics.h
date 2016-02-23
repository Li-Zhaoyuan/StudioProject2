#ifndef PHYSICS_H
#define PHYSICS_H

#include "Vector3.h"

struct Physics
{
public:
	Physics();
	~Physics();

	static float VelocityUAT(float u, float a, float t);
	static float DisplacementUVT(float u, float v, float t);
	static float DisplacemnetUTAT(float u, float t, float a);
	static float VelocityU2AS(float u, float a, float s);
	static float AccelerationFM(float M, float F);
};

#endif