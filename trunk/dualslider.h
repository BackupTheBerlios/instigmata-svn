#ifndef INSTIGMATA_DUALSLIDER_H
#define INSTIGMATA_DUALSLIDER_H 1
#include "box.h"
#include "event.h"
#include <vector>

class DualSlider : public Box, public EventListener {
	private:
	EventListener *listener;
	eventtype et;
	eventtype et2;

	double value;
	double value2;
	
	double sval1;
	double sval2;
	bool recording;
	bool playback;
	
	std::vector<double> record1;
	std::vector<double> record2;

	int rp1, rp2;

	double step;
	double step2;
	char *text;
	bool islogarithmic;
	bool islogarithmic2;
	
	

	public:
	DualSlider(int x, char *text, eventtype et, eventtype et2, EventListener *listener, 
		double val, double val2, double step, double step2, bool islogarithmic, bool islogarithmic2);
	bool handleDragEvent(int x, int y, int mx, int my);
	bool handleMouseEvent(int x, int y, int b);
	void emptyEvent(eventtype et);
	
	void paint();
};

#endif /* INSTIGMATA_DUALSLIDER_H */
