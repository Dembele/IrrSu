#include "Player.h"

void Player::setCoordinates(double x, double y)
{
	position.x = x;
	position.y = y;
}

int Player::getCoordinatesX()
{
	return position.x;
}

int Player::getCoordinatesY()
{
	return position.y;
}


Player::Player()
{
	
}


Player::~Player()
{

}
