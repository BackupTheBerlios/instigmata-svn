#include "dualslider.h"
#include "colors.h"
#include "looper.h"
#include "soundcore.h"
#include <math.h>


DualSlider::DualSlider(int x, char *text, eventtype et, eventtype et2, EventListener *listener, 
	double val, double val2, double step, double step2, bool islogarithmic, bool islogarithmic2)
	: Box(x, 3, 30, 90, COLOR_DEFAULT_BUTTON, Box::TYPE_BEVEL)
{
	this->text  = text;
	this->et    = et;
	this->et2   = et2;
	this->step  = step;
	this->step2 = step2;
	this->listener = listener;
	this->islogarithmic = islogarithmic;
	this->islogarithmic2 = islogarithmic2;

	// Copypastecode Rocks!
	if(islogarithmic) {
		val = 1 - val; // Reverse
		val = pow(10, val); // Power
		val = (val - 1) / 9.0; // Scale
		val = 1 - val; // Reverse again
		this->value = val;
	} else
		this->value = val;

	if(islogarithmic2) {
		val2 = 1 - val2; // Reverse
		val2 = pow(10, val2); // Power
		val2 = (val2 - 1) / 9.0; // Scale
		val2 = 1 - val2; // Reverse again
		this->value2 = val2;
	} else
		this->value2 = val2;

}

void DualSlider::paint(){
	scare_mouse();
	Box::paint();
	textprintf_centre_ex(screen, font, x + w / 2 + 4, y + 5, COLOR_DEFAULT_BUTTONTEXT_SHADOW, -1, "%s", text);
	textprintf_centre_ex(screen, font, x + w / 2 + 2, y + 3, COLOR_DEFAULT_BUTTONTEXT, -1, "%s", text);
	rectfill(screen, x + 2, y + 86 - (int)(72 * value), x + 14, y + 86, COLOR_SLIDER);
	rectfill(screen, x + 15, y + 86 - (int)(72 * value2), x + 26, y + 86, COLOR_SLIDER2);
	line(screen, x + 14, y + 14, x + 14, y + 86, 0);
	rect(screen, x + 2, y + 14, x + 26, y + 86, 0);
	unscare_mouse();
}

double solveDrag(double v, int m, double step) {
	v -= m * step;
	if(v > 1.0) {
		v = 1.0;
	} else if(v < 0) {
		v = 0;
	}
	return v;
}

double toLogarithmic(double v) {
	double n = (1 - v) * 9.0 + 1.0;
	n = log10(n);
	n = 1 - n;
	return n;
}

bool DualSlider::handleDragEvent(int x, int y, int mx, int my) {
	if(my) {
		value = solveDrag(value, my, step);

		listener->doubleEvent(et, islogarithmic?toLogarithmic(value):value);
	}

	if(mx) {
		value2 = solveDrag(value2, -mx, step2);
		listener->doubleEvent(et2, islogarithmic2?toLogarithmic(value2):value2);
	}
	paint();
	return true;
}
