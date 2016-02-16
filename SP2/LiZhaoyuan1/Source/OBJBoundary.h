#ifndef OBJBoundary_H_
#define OBJBoundary_H_

#include "Scene.h"
#include "Camera.h"
#include "Camera2.h"
#include "Camera3.h"
#include "Camera4.h"
#include "MatrixStack.h"
#include "RenderMun.h"
class OBJBoundary : public Scene
{

public:
	OBJBoundary();
	~OBJBoundary();

	virtual void AABB(float xS, float xL, float zS, float zL);
	bool boundaryCheckerX(float smallx, float largex, float smallz, float largez, Vector3 value);
	bool boundaryCheckerZ(float smallx, float largex, float smallz, float largez, Vector3 value);
	bool OBJboundaryX(Vector3 Testvalue);
	bool OBJboundaryZ(Vector3 Testvalue);
	bool OBJboundaryY(Vector3 Testvalue, int XZ);
	void OBJobjectvalues();
private:
	
	Camera3 camera;

};

#endif