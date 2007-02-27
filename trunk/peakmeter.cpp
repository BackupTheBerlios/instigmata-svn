#include "colors.h"
#include "soundcore.h"
#include "peakmeter.h"
#include <math.h>
#include "loader.h"

PeakMeter::PeakMeter(int x, int y) 
	: Box(x, y, 60, 280, COLOR_DEFAULT_BUTTON, Box::TYPE_BEVEL)
{
	sound->registerPeakMeter(this);
	lp = 0;
	rp = 0;
}

void PeakMeter::paint() {
	if(loader->needsDisplay())
		return;

	scare_mouse();
	Box::paint();
	for(int i = 0; i < 280; i += 20) {
		if(i == 60)
			line(screen, x + 2, y + 10 + i, x + 56,  y + 10 + i, 0);
		else
			line(screen, x + 15, y + 10 + i, x + 45,  y + 10 + i, 0);
	}

	double v;
	v = (10.0 * log10(lp) * 2.0) / -80.0;
	if((210 * v + 70) < 270) {
		rectfill(screen, x + 20, (int)(y + 210 * v + 70), 
						 x + 27, y + 270,
				COLOR_SLIDER
		);
	}


	v = (10.0 * log10(rp) * 2.0) / -80.0;
	if((210 * v + 70) < 270) {
		rectfill(screen, x + 33, (int)(y + 210 * v + 70), 
						 x + 40, y + 270,
				COLOR_SLIDER
		);
	}

	unscare_mouse();
}

void PeakMeter::doubleEvent(eventtype et, double data) {
	switch(et){
		case EVENT_PEAKMETER_LEFT_CHANNEL:
			lp = data;
			break;
		case EVENT_PEAKMETER_RIGHT_CHANNEL:
			rp = data;
			break;
	}
	quePaint();
}

