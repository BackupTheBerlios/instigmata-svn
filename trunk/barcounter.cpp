#include <allegro.h>
#include "colors.h"
#include "barcounter.h"
#include "loader.h"

BarCounter::BarCounter(int x, int y)
	: Box(x, y, 92, 20, 0, Box::TYPE_BEVEL)
{
	this->x = x;
	this->y = y;
	bars = -1;
}

void BarCounter::paint() {
	if(loader->needsDisplay())
		return;
	scare_mouse();
	for(int i = 0; i < 4; i++) {
		int c = (bars==i)?COLOR_BAR_PASSED:COLOR_BAR_DUE;
		circlefill(screen, x + 23 * i, y, 10, c);
		circle(screen, x + 23 * i, y, 10, 0);
	}
	unscare_mouse();
}

void BarCounter::bar() {
	if(bars < 3)
		bars++;
	else
		bars = 0;
	quePaint();
}
