
#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>


#include "SP2.h"
#include "LoadingScreen.h"
#include "SceneMun.h"
#include "SceneGalaxy.h"
#include "SceneSoraJewel.h"
#include "Music.h"
GLFWwindow* m_window;
GLFWmonitor* primary;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

Application::Application()
{
}

Application::~Application()
{
}

void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h); //update opengl the new window size
}

void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	
	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	primary = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primary);
	//Create a window and create its OpenGL context
	m_window = glfwCreateWindow(mode->width, mode->height, "Computer Graphics", NULL, NULL);
	
	/*glfwSetCursorPos(m_window, 800 / 2, 600 / 2);*/
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetWindowSizeCallback(m_window, resize_callback);
	
	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}
}

void Application::Run()
{
	int loadingitonceSoraJewel=1;
	int loadingitonceGalaxy = 1;
	int loadingitonceMun = 1;
	
	//Main Loop
	Scene *currscene = new SP2();
	Scene *scenestart = new SP2();
	Scene *scene1 = new SceneSoraJewel();
	Scene *scene2 = new SceneGalaxy();
	Scene *scene3 = new SceneMun();
	Scene *loading = new LoadingScreen();
	currscene->Init();
	/*scene1->Init();
	scene2->Init();
	scene3->Init();*/
	
	m_timer.startTimer();    // Start timer to calculate how long it takes to render this fr
	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE))
	{
		if (IsKeyPressed('I'))
		{
			currscene->Init();
		}
		else if (IsKeyPressed('O'))
		{
			loadingitonceSoraJewel = 1;
			loadingitonceGalaxy = 1;
			loadingitonceMun = 1;
		}
		else if (IsKeyPressed('Z'))
		{
			currscene = scene1;
			//currscene->Init();
			sceneischanged = true;
			playmusic.musicSoraJewel();
		}
		else if (IsKeyPressed('X'))
		{
			currscene = scene2;
			currscene->Init();
			playmusic.musicGalaxy();
		}
		else if (IsKeyPressed('C'))
		{
			currscene = scene3;
			//currscene->Init();
			sceneischanged = true;
			playmusic.musicMun();
		}
		if (Gamemode::getinstance()->currentgamestate == 1)
		{
			currscene = new SP2();
			loadingitonceSoraJewel = 1;
			loadingitonceGalaxy = 1;
			loadingitonceMun = 1;
			currscene->Init();
			playmusic.musicMainMenu();
		}
		else if (Gamemode::getinstance()->currentgamestate == 2 && loadingitonceSoraJewel == 1)
		{
			currscene = loading;
			currscene->Init();
			sceneischanged = true;
		}
		else if (Gamemode::getinstance()->currentgamestate == 3 && loadingitonceSoraJewel == 1)
		{
			currscene = scene1;
			//currscene->Init();
			sceneischanged = true;
			playmusic.musicSoraJewel();
			loadingitonceSoraJewel += 1;
		}
		else if (Gamemode::getinstance()->currentgamestate == 4 && loadingitonceSoraJewel == 2)
		{
			currscene = loading;
			currscene->Init();
			sceneischanged = true;
		}
		else if (Gamemode::getinstance()->currentgamestate == 4 && loadingitonceSoraJewel == 1)
		{
			currscene = loading;
			currscene->Init();
			sceneischanged = true;
		}
		else if (Gamemode::getinstance()->currentgamestate == 5 && loadingitonceGalaxy == 1)
			{
				currscene = scene2;
				//currscene->Init();
				sceneischanged = true;
				playmusic.musicGalaxy();
				loadingitonceGalaxy += 1;
			}
		else if (Gamemode::getinstance()->currentgamestate == 6 && loadingitonceMun == 1)
		{
			currscene = loading;
			currscene->Init();
			sceneischanged = true;
		}
		else if (Gamemode::getinstance()->currentgamestate == 7 && loadingitonceMun==1)
			{
				currscene = scene3;
				//currscene->Init();
				sceneischanged = true;
				playmusic.musicMun();
				loadingitonceMun += 1;
			}
		if (sceneischanged == true)
		{
			currscene->Init();
			sceneischanged = false;
		}
			currscene->Update(m_timer.getElapsedTime());
			currscene->Render();
			//Swap buffers
			glfwSwapBuffers(m_window);
			//Get and organize events, like keyboard and mouse input, window resizing, etc...
			glfwPollEvents();
			m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

		} //Check if the ESC key had been pressed or if the window had been closed
		currscene->Exit();
		delete currscene;
	
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}

