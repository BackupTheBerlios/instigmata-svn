#include "eventbutton.h"
#include "event.h"
#include "colors.h"

EventButton::EventButton(int x, int y, int w, int h, int c, EventListener *e, eventtype et, char *name) 
	: Box(x, y, w, h, c, Box::TYPE_BEVEL)
{
	this->target = e;
	this->event = et;
	this->name = strdup(name);
}

bool EventButton::handleMouseEvent(int x, int y, int b){
	target->emptyEvent(event);
	return true;
}

void EventButton::paint() {
	scare_mouse();
	Box::paint();
	textprintf_centre_ex(screen, font, x + w / 2 + 4, y + (h / 2) - 1, COLOR_DEFAULT_BUTTONTEXT_SHADOW, -1, "%s", name);
	textprintf_centre_ex(screen, font, x + w / 2 + 2, y + (h / 2) - 3, COLOR_DEFAULT_BUTTONTEXT, -1, "%s", name);
	unscare_mouse();
}
