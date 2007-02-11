#ifndef INSTIGMATA_SELECTGROUP_H
#define INSTIGMATA_SELECTGROUP_H 1
#include "box.h"
#include "event.h"

class SelectGroup : public Box {
	private:
	eventtype et;
	EventListener *listener;
	public:
	SelectGroup(int x, int y, int nbuttons, char *names[], int selected, int color, eventtype et, EventListener *listener);
	void childHandledMouseEvent(int x, int y, int b, Box *child);
};

#endif /* INSTIGMATA_SELECTGROUP_H */
