#ifndef CURRENTGAMESTATE_H_
#define CURRENTGAMESTATE_H_

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