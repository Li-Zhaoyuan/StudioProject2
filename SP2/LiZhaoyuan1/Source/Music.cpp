/****************************************************************************/
/*!
\file Music.cpp
\author Li Zhaoyuan
\par email: lizhaoyuan123@hotmail.com
\brief
class for the Music class
*/
/****************************************************************************/
#include "Music.h"
/******************************************************************************/
/*!
\brief	music constructor
*/
/******************************************************************************/
music::music()
{
	se = createIrrKlangDevice();
}
/******************************************************************************/
/*!
\brief	music destructor
*/
/******************************************************************************/
music::~music()
{
	se->drop();
}
/******************************************************************************/
/*!
\brief	music function to play music for Sora Jewel scene
*/
/******************************************************************************/
void music::musicSoraJewel()
{
	se->stopAllSounds();
	MusicSoraJewel = se->addSoundSourceFromFile("Music//bensound-theelevatorbossanova.mp3");
	se->play2D(MusicSoraJewel);
}
/******************************************************************************/
/*!
\brief	music function to play music for Galaxy scene
*/
/******************************************************************************/
void music::musicGalaxy()
{
	se->stopAllSounds();
	MusicGalaxy = se->addSoundSourceFromFile("Music//MusicGalaxy.mp3");
	se->play2D(MusicGalaxy);
}
/******************************************************************************/
/*!
\brief	music function to play music for Mun scene
*/
/******************************************************************************/
void music::musicMun()
{
	se->stopAllSounds();
	MusicMun = se->addSoundSourceFromFile("Music//MusicMun.mp3");
	se->play2D(MusicMun);
}
/******************************************************************************/
/*!
\brief	music function to play music for main menu
*/
/******************************************************************************/
void music::musicMainMenu()
{
	se->stopAllSounds();
}