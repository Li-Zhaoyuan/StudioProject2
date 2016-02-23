#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include "Currentgamestate.h"

class Application
{
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	void changescenes();
	bool sceneischanged = false;
private:
	//Declare a window object
	StopWatch m_timer;

};
#endif