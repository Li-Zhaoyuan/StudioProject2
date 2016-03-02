/****************************************************************************/
/*!
\file LoadingScreen.h
\author Nathan Chia
\par email: 150503N@mymail.nyp.edu.sg
\brief
Class of the Gamestates of the game
*/
/****************************************************************************/
#ifndef CURRENTGAMESTATE_H_
#define CURRENTGAMESTATE_H_

/******************************************************************************/
/*!
Class Gamemode:
\brief	Defines the Gamemode and its methods
*/
/******************************************************************************/
class Gamemode
{
public:
	static Gamemode *getinstance()
	{
		static Gamemode data;
		return &data;
	}
	int currentgamestate = 0;
private:
	Gamemode(){}
};
#endif