#include <iostream>
#include <string>
#include <Windows.h>
#include "include/irrKlang.h"
#include "Music.h"

using namespace std;
using namespace irrklang;

#pragma comment(lib,"irrKlang.lib")

void music::musicInit()
{
	se = createIrrKlangDevice();
}

void music::musicSoraJewel()
{
	se->play2D("Music//bensound-theelevatorbossanova.mp3");
}

void music::musicGalaxy()
{

}

void music::musicMun()
{
}