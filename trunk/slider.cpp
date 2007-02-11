#include "slider.h"
#include "colors.h"
#include "looper.h"
#include "soundcore.h"
#include "logconv.h"
#include <math.h>

Slider::Slider(int x, char *text, eventtype et, EventListener *listener, double val, double step, slidertype type) 
	: Box(x, 3, 30, 90, COLOR_DEFAULT_BUTTON, Box::TYPE_BEVEL)
{
	this->text  = text;
	this->et    = et;
	this->step  = step;
	this->listener = listener;
	this->type = type;

	if(type == SLIDER_LOGARITHMIC) {
		this->value = logToLin(val);
	} else if(type == SLIDER_ANTILOGARITHMIC) {
		this->value = antiLogToLin(val);
	} else 
		this->value = val;
}

void Slider::paint(){
	scare_mouse();
	Box::paint();
	textprintf_centre_ex(screen, font, x + w / 2 + 4, y + 5, COLOR_DEFAULT_BUTTONTEXT_SHADOW, -1, "%s", text);
	textprintf_centre_ex(screen, font, x + w / 2 + 2, y + 3, COLOR_DEFAULT_BUTTONTEXT, -1, "%s", text);
	rectfill(screen, x + 2, y + 86 - (int)(72 * value), x + 26, y + 86, COLOR_SLIDER);
	rect(screen, x + 2, y + 14, x + 26, y + 86, 0);
	unscare_mouse();
}
bool Slider::handleDragEvent(int x, int y, int mx, int my) {
	value -= my * step;
	if(value > 1.0) {
		value = 1.0;
	} else if(value < 0) {
		value = 0;
	}
	paint();

	double ret;

	if(type == SLIDER_LOGARITHMIC) {
		ret = linToLog(value);
	} else if(type == SLIDER_ANTILOGARITHMIC) {
		ret = linToAntiLog(value);
	} else 
		ret = value;

	listener->doubleEvent(et, ret);
}
