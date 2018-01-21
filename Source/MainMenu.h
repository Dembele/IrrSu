#pragma once
#include <irrlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

struct SAppContext
{
	IrrlichtDevice *device;
	s32             counter;
	IGUIListBox*    listbox;
};

// Define some values that we'll use to identify individual GUI controls.
enum Buttons { B_NEWGAME, B_LOAD, B_OPTIONS, B_EXIT, GAMMA };

class MyEventReceiver : public IEventReceiver
{
public:
	int clicked = 0;
	MyEventReceiver() {}

	void set(SAppContext context) 
	{
		Context = context;
	}

	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment* env = Context.device->getGUIEnvironment();

			switch (event.GUIEvent.EventType)
			{
			case EGET_SCROLL_BAR_CHANGED:
				if (id == GAMMA)
				{
					s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
				}
				break;
			case EGET_BUTTON_CLICKED:
				switch (id)
				{
				case B_EXIT:
					Context.device->closeDevice();
					return true;

				case B_NEWGAME:
				{
					clicked = 2;
					return true;
				}
				case B_OPTIONS:
				{
					clicked = 3;
					return true;
				}
				case B_LOAD:
				{
					clicked = 4;
					return true;
				}
				return true;

				default:
					return false;
				}
				break;

			case EGET_FILE_SELECTED:
			{
				// show the model filename, selected in the file dialog
				IGUIFileOpenDialog* dialog =
					(IGUIFileOpenDialog*)event.GUIEvent.Caller;
				Context.listbox->addItem(dialog->getFileName());
			}
			break;

			default:
				break;
			}
		}

		return false;
	}

private:
	SAppContext Context;
};