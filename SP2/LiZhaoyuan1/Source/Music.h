#ifndef MUSIC_H_
#define MUSIC_H_

#include <iostream>
#include <string>
#include <Windows.h>
#include "include/irrKlang.h"

using namespace std;
using namespace irrklang;

#pragma comment(lib,"irrKlang.lib")

class music
{
public:
	music();
	~music();

	void musicInit();
	void musicSoraJewel();
	void musicGalaxy();
	void musicMun();

	ISoundEngine* se;
	ISoundSource* MusicSoraJewel;
	ISoundSource* MusicGalaxy;
	ISoundSource* MusicMun;
};


#endif