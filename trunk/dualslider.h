#ifndef INSTIGMATA_DUALSLIDER_H
#define INSTIGMATA_DUALSLIDER_H 1
#include "box.h"
#include "event.h"

class DualSlider : public Box, public EventListener {
	private:
	EventListener *listener;
	eventtype et;
	eventtype et2;
	double value;
	double value2;
	double step;
	double step2;
	char *text;
	bool islogarithmic;
	bool islogarithmic2;
	public:
	DualSlider(int x, char *text, eventtype et, eventtype et2, EventListener *listener, 
		double val, double val2, double step, double step2, bool islogarithmic, bool islogarithmic2);
	bool handleDragEvent(int x, int y, int mx, int my);
	void paint();
};

#endif /* INSTIGMATA_DUALSLIDER_H */
