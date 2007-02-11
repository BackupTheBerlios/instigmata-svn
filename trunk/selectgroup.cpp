#include "selectgroup.h"
#include "colors.h"
#include "button.h"

SelectGroup::SelectGroup(int x, int y, int nbuttons, char *names[], int selected, int color, eventtype et, EventListener *listener) 
	: Box(x, y, nbuttons * 24, 24, color, Box::TYPE_FLAT)
{
	this->et = et;
	this->listener = listener;

	for(int i = 0; i < nbuttons; i++){
		addChild(new Button(i * 24, 0, 24, 24, COLOR_DEFAULT_BUTTON, i==selected, names[i]));
	}
}

void SelectGroup::childHandledMouseEvent(int x, int y, int b, Box *child) {
	for(int i = 0; i < children.size(); i++) {
		if(children[i] != child) {
			((Button *)children[i])->setStatus(false);
		} else {
			listener->intEvent(et, i);
			((Button *)children[i])->setStatus(true);
		}
	}
}
