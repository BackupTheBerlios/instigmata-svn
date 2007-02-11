#ifndef INSTIGMATA_SLIDER_H
#define INSTIGMATA_SLIDER_H 1
#include "box.h"
#include "event.h"

typedef enum slidertype {
	SLIDER_LINEAR,
	SLIDER_LOGARITHMIC,
	SLIDER_ANTILOGARITHMIC
};

class Slider : public Box, public EventListener {
	private:
	EventListener *listener;
	eventtype et;
	double value;
	double step;
	char *text;
	slidertype type;
	public:
	Slider(int x, char *text, eventtype et, EventListener *listener, double val, double step, slidertype type);
	bool handleDragEvent(int x, int y, int mx, int my);
	void paint();
};

#endif /* INSTIGMATA_SLIDER_H */
