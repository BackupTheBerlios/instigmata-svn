#ifndef INSTIGMATA_BARCOUNTER_H
#define INSTIGMATA_BARCOUNTER_H 1
#include "box.h"

class BarCounter : public Box {
	int bars;
	public:
	BarCounter(int x, int y);
	void paint();
	void bar();
};

#endif
