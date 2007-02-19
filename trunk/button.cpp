#include "button.h"
#include "colors.h"

Button::Button(int x, int y, int w, int h, int c, bool status, char *name) 
	: Box(x, y, w, h, c, status?Box::TYPE_GRAVE:Box::TYPE_BEVEL)
{
	this->name   = strdup(name);
	this->status = status;
}

void Button::changeType(){
	if(status)
		type = TYPE_GRAVE;
	else
		type = TYPE_BEVEL;
	paint();
}

bool Button::handleMouseEvent(int x, int y, int b){
	if(b & 1) {
		status = !status;
		changeType();
	}
	return true;
}

void Button::setStatus(bool status){
	this->status = status;
	changeType();
}

void Button::paint() {
	scare_mouse();
	Box::paint();
	textprintf_centre_ex(screen, font, x + w / 2 + 3, y + (h / 2) - 5, COLOR_DEFAULT_BUTTONTEXT_SHADOW, -1, "%s", name);
	textprintf_centre_ex(screen, font, x + w / 2 + 1, y + (h / 2) - 7, COLOR_DEFAULT_BUTTONTEXT, -1, "%s", name);
	unscare_mouse();
}

bool Button::getStatus(){
	return this->status;
}

