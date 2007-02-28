#ifndef INSTIGMATA_SLIDER_H
#define INSTIGMATA_SLIDER_H 1
#include "box.h"
#include "event.h"
#include <vector>

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

	std::vector<double> record;
	int rp;
	double sval;

	bool recording, playback;

	public:
	Slider(int x, char *text, eventtype et, EventListener *listener, double val, double step, slidertype type);
	bool handleDragEvent(int x, int y, int mx, int my);
	void paint();

	bool handleMouseEvent(int x, int y, int b);
	void emptyEvent(eventtype et);


};

#endif /* INSTIGMATA_SLIDER_H */
