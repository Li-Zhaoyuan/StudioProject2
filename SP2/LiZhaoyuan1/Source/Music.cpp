#include "Music.h"

music::music()
{
	se = createIrrKlangDevice();
	
}

music::~music()
{
	se->drop();
}

void music::musicSoraJewel()
{
	se->stopAllSounds();
	MusicSoraJewel = se->addSoundSourceFromFile("Music//bensound-theelevatorbossanova.mp3");
	se->play2D(MusicSoraJewel);
}

void music::musicGalaxy()
{
	se->stopAllSounds();
	MusicGalaxy = se->addSoundSourceFromFile("Music//MusicGalaxy.mp3");
	se->play2D(MusicGalaxy);
}

void music::musicMun()
{
	se->stopAllSounds();
	MusicMun = se->addSoundSourceFromFile("Music//MusicMun.mp3");
	se->play2D(MusicMun);
}

void music::musicMainMenu()
{
	se->stopAllSounds();
}