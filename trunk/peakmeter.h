#ifndef INSTIGMATA_PEAKMETER_H
#define INSTIGMATA_PEAKMETER_H 1

#include "box.h"
#include "event.h"

class PeakMeter : public Box, public EventListener
{
	private:
	double lp, rp;

	public:
	PeakMeter(int x, int y);
	void doubleEvent(eventtype et, double data);
	void paint();
};

#endif
