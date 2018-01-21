#pragma once
class Character
{
public:
	Character();
	~Character();
	int GetMovespeed();
	enum States
	{
		//stand, attack, cast, right substate ... etc
		S, A, C, R1, R2, L1, L2, U1, U2, D1, D2, UR1, UR2, UL1, UL2, DR1, DR2, DL1, DL2
	};
protected:
	struct position
	{
		int y; //height
		int x; //width
	}position;
	int movespeed = 1;
	int health;
	int attack;
	int range;
};

