#include "Character.h"



Character::Character()
{
	position.x = 0;
	position.y = 0;
}


Character::~Character()
{
}

double Character::GetMovespeed()
{
	return movespeed;
}