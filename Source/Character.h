#pragma once
class Character
{
public:
	Character();
	~Character();
	double GetMovespeed();
protected:
	struct position
	{
		double y; //height
		double x; //width
	}position;
	double movespeed = 0.1;
	int health;
	int attack;
	int range;
};

