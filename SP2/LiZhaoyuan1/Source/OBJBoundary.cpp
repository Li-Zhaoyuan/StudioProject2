#include "OBJBoundary.h"

OBJBoundary::OBJBoundary()
{

}

OBJBoundary::~OBJBoundary()
{

}

// Original Boundary Code
void OBJBoundary::AABB(float xS, float xL, float zS, float zL)
{
	if ((camera.position.x > xS) && (camera.position.x < xL) && (camera.position.z > zS) && (camera.position.z < zS + 2)) { camera.position.z = zS; }
	if ((camera.position.x > xS) && (camera.position.x < xL) && (camera.position.z < zL) && (camera.position.z > zL - 2)) { camera.position.z = zL; }
	if ((camera.position.z > zS) && (camera.position.z < zL) && (camera.position.x > xS) && (camera.position.x < xS + 2)) { camera.position.x = xS; }
	if ((camera.position.z > zS) && (camera.position.z < zL) && (camera.position.x > xL) && (camera.position.x < xL - 2)) { camera.position.x = xL; }

}
void OBJBoundary::OBJobjectvalues()
{
	AABB(23,43,-28,-2);
}
////Was going to Implement the follow bottom codes instead
//bool OBJBoundary::boundaryCheckerX(float smallx, float largex, float smallz, float largez, Vector3 value)
//{
//	if ((value.z > smallz) && (value.z<largez) && (value.x > smallx) && (value.x<smallx + 2)){ return false; }
//	if ((value.z > smallz) && (value.z<largez) && (value.x < largex) && (value.x>largex - 2)){ return false; }
//	return true;
//}
//
//bool OBJBoundary::boundaryCheckerZ(float smallx, float largex, float smallz, float largez, Vector3 value)
//{
//	if ((value.x > smallx) && (value.x<largex) && (value.z > smallz) && (value.z<smallz + 2)){ return false; }
//	if ((value.x > smallx) && (value.x<largex) && (value.z < largez) && (value.z>largez - 2)){ return false; }
//	return true;
//}
//
//bool OBJBoundary::OBJboundaryX(Vector3 Testvalue)
//{
//	if (boundaryCheckerX(-50, 50, -105, -40, Testvalue) == false){ return false; }
//	return true;
//}
//
//bool OBJBoundary::OBJboundaryZ(Vector3 Testvalue)
//{
//	if (boundaryCheckerZ(-50, 50, -105, -40, Testvalue) == false){ return false; }
//	return true;
//}
//
//bool OBJBoundary::OBJboundaryY(Vector3 Testvalue, int XZ)
//{
//	if (Testvalue.y >= 20)
//	{
//		if (XZ == 1)
//		{
//			if (boundaryCheckerX(-89, -70, -25, 0, Testvalue) == false)
//			{
//				return false;
//			}
//		}
//		else if (XZ == 2)
//		{
//			if (boundaryCheckerZ(-89, -70, -25, 0, Testvalue) == false)
//			{
//				return false;
//			}
//		}
//	}
//	return true;
//}