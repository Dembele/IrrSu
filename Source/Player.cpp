#include "Player.h"

void Player::setCoordinates(double x, double y)
{
	position.x = x;
	position.y = y;
}

double Player::getCoordinatesX()
{
	return position.x;
}

double Player::getCoordinatesY()
{
	return position.y;
}


Player::Player()
{
	
}


Player::~Player()
{

}
