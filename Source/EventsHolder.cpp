/// ==================================================================================================
/// MastEventReceiver code is © (Copyright) Robert E. Demarest, AKA Mastiff or Mastiff Odit and was modified a bit by me (Dembele)
/// This file may be used in any non-commercial or commercial project as long as the following conditions are met:
/// You may not claim this code as being your own.
/// You may not use this code for any harmful, malicious or otherwise damaging programs.
///
/// This is version 1.2a of the class.
/// This class is designed for use with the Irrlicht Engine, it was written for version 1.3 of the engine.
/// ==================================================================================================

#include "EventsHolder.h"

bool EventsHolder::OnEvent(const irr::SEvent & event)
{

	bool eventprocessed = false;

	//////////////////////////////
	// Keyboard Input Event
	//////////////////////////////
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
	{
		if (processState == STARTED)
		{
			// if key is Pressed Down
			if (event.KeyInput.PressedDown == true)
			{
				// If key was not down before
				if (keyState[event.KeyInput.Key] != DOWN)
				{
					keyState[event.KeyInput.Key] = PRESSED; // Set to Pressed
				}
				else
				{
					// if key was down before
					keyState[event.KeyInput.Key] = DOWN; // Set to Down
				}
			}
			else
			{

				// if the key is down
				if (keyState[event.KeyInput.Key] != UP)
				{
					keyState[event.KeyInput.Key] = RELEASED; // Set to Released
				}
			}
		}


		eventprocessed = true;
	}

	//////////////////////////////
	// Mouse Input Event
	//////////////////////////////

	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		if (processState == STARTED)
		{
			//Mouse changed position
			if (event.MouseInput.Event == irr::EMIE_MOUSE_MOVED)
			{
				mouse.Y = event.MouseInput.Y;
				mouse.X = event.MouseInput.X;
			}

			//Wheel moved.
			if (event.MouseInput.Event == irr::EMIE_MOUSE_WHEEL)
			{
				mouse.wheel += event.MouseInput.Wheel;
			}

			//Left Mouse Button Pressed
			if (event.MouseInput.Event == irr::EMIE_LMOUSE_PRESSED_DOWN)
			{
				//
				if (mouseButtonState[0] == UP || mouseButtonState[0] == RELEASED)
				{
					mouseButtonState[0] = PRESSED;
				}
				else
				{
					mouseButtonState[0] = DOWN;
				}
			}

			//Left Mouse Button Rleased
			if (event.MouseInput.Event == irr::EMIE_LMOUSE_LEFT_UP)
			{
				//
				if (mouseButtonState[0] != UP)
				{
					mouseButtonState[0] = RELEASED;
				}
			}

			//Middle Mouse Button Pressed
			if (event.MouseInput.Event == irr::EMIE_MMOUSE_PRESSED_DOWN)
			{
				//
				if (mouseButtonState[1] == UP || mouseButtonState[1] == RELEASED)
				{
					mouseButtonState[1] = PRESSED;
				}
				else
				{
					mouseButtonState[1] = DOWN;
				}
			}

			//Middle Mouse Button Rleased
			if (event.MouseInput.Event == irr::EMIE_MMOUSE_LEFT_UP)
			{
				//
				if (mouseButtonState[1] != UP)
				{
					mouseButtonState[1] = RELEASED;
				}
			}

			//Right Mouse Button Pressed
			if (event.MouseInput.Event == irr::EMIE_RMOUSE_PRESSED_DOWN)
			{
				//
				if (mouseButtonState[2] == UP || mouseButtonState[2] == RELEASED)
				{
					mouseButtonState[2] = PRESSED;
				}
				else
				{
					mouseButtonState[2] = DOWN;
				}
			}

			//Right Mouse Button Rleased
			if (event.MouseInput.Event == irr::EMIE_RMOUSE_LEFT_UP)
			{
				//
				if (mouseButtonState[2] != UP)
				{
					mouseButtonState[2] = RELEASED;
				}
			}
		}


		eventprocessed = true;
	}


	return eventprocessed;
}

float EventsHolder::mouseWheel()
{
	return mouse.wheel;
}

int EventsHolder::mouseX()
{
	return mouse.X;
}

int EventsHolder::mouseY()
{
	return mouse.Y;
}

bool EventsHolder::leftMouseReleased()
{
	if (mouseButtonState[0] == RELEASED)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool EventsHolder::leftMouseUp()
{
	if (mouseButtonState[0] == RELEASED || mouseButtonState[0] == UP)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool EventsHolder::leftMousePressed()
{
	if (mouseButtonState[0] == PRESSED)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool EventsHolder::leftMouseDown()
{
	if (mouseButtonState[0] == PRESSED || mouseButtonState[0] == DOWN)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool EventsHolder::middleMouseReleased()
{
	if (mouseButtonState[1] == RELEASED)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool EventsHolder::middleMouseUp()
{
	if (mouseButtonState[1] == RELEASED || mouseButtonState[1] == UP)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool EventsHolder::middleMousePressed()
{
	if (mouseButtonState[1] == PRESSED)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool EventsHolder::middleMouseDown()
{
	if (mouseButtonState[1] == PRESSED || mouseButtonState[1] == DOWN)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool EventsHolder::rightMouseReleased()
{
	if (mouseButtonState[2] == RELEASED)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool EventsHolder::rightMouseUp()
{
	if (mouseButtonState[2] == RELEASED || mouseButtonState[2] == UP)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool EventsHolder::rightMousePressed()
{
	if (mouseButtonState[2] == PRESSED)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool EventsHolder::rightMouseDown()
{
	if (mouseButtonState[2] == PRESSED || mouseButtonState[2] == DOWN)
	{
		return true;
	}
	else
	{
		return false;
	}
}//

bool EventsHolder::keyPressed(char keycode)
{
	if (keyState[keycode] == PRESSED)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool EventsHolder::keyDown(char keycode)
{
	if (keyState[keycode] == DOWN || keyState[keycode] == PRESSED)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool EventsHolder::keyUp(char keycode)
{
	if (keyState[keycode] == UP || keyState[keycode] == RELEASED)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool EventsHolder::keyReleased(char keycode)
{
	if (keyState[keycode] == RELEASED)
	{
		return true;
	}
	else
	{
		return false;
	}
}


// This is used so that the Key States will not be changed during execution of your Main game loop.
// Place this at the very START of your Main Loop
void EventsHolder::endEventProcess()
{
	processState = ENDED;
}

// This is used so that the Key States will not be changed during execution of your Main game loop.
// Place this function at the END of your Main Loop.
void EventsHolder::startEventProcess()
{

	processState = STARTED;
	//Keyboard Key States
	for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
	{
		if (keyState[i] == RELEASED)
		{
			keyState[i] = UP;
		}

		if (keyState[i] == PRESSED)
		{
			keyState[i] = DOWN;
		}
	}
	//Mouse Button States
	for (int i = 0; i <= 2; i++)
	{
		if (mouseButtonState[i] == RELEASED)
		{
			mouseButtonState[i] = UP;
		}

		if (mouseButtonState[i] == PRESSED)
		{
			mouseButtonState[i] = DOWN;
		}
	}
	//Mouse Wheel state
	mouse.wheel = 0.0f;

}

void EventsHolder::init()
{
	//KeyBoard States.
	for (int i = 0; i <= irr::KEY_KEY_CODES_COUNT; i++)
	{
		keyState[i] = UP;
	}
	//Mouse states
	for (int i = 0; i <= 2; i++)
	{
		mouseButtonState[i] = UP;
	}
	//Mouse X/Y coordenates.
	mouse.X = 0;
	mouse.Y = 0;
	mouse.wheel = 0.0f;
}
/// ==========================================
/// END OF MastEventReceiver
/// ==========================================

