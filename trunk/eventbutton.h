#ifndef INSTIGMATA_EVENTBUTTON_H
#define INSTIGMATA_EVENTBUTTON_H 1
#include "box.h"
#include "event.h"

class EventButton : public Box {
	private:
	EventListener *target;
	eventtype event;
	char *name;
	protected:
	bool handleMouseEvent(int x, int y, int b);
	public:
	EventButton(int x, int y, int w, int h, int c, EventListener *e, eventtype et, char *name);
	void paint();
};

#endif /* INSTIGMATA_EVENTBUTTON_H */
