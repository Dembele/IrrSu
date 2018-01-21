#pragma once
#include "Character.h"
class Player :
	public Character
{
public:
	Player();
	~Player();
	void setCoordinates(double x, double y);
	int getCoordinatesX();
	int getCoordinatesY();
protected:
	struct exp
	{
		int currentExp;
		int expToLevelUp;
	} exp;
	int strength;
	int agility;
	int intelect;
	int vitality;
};

