#ifndef INSTIGMATA_BUTTON_H
#define INSTIGMATA_BUTTON_H 1
#include "box.h"
#include "event.h"

class Button : public Box {
	private:
	bool status;
	void changeType();
	char *name;
	eventtype et;
	EventListener *listener;

	protected:
	bool handleMouseEvent(int x, int y, int b);

	public:
	Button(int x, int y, int w, int h, int color, bool state, char *name);
	Button(int x, int y, int w, int h, int c, bool status, char *name, EventListener *listener, eventtype et); 
	void setStatus(bool);
	bool getStatus(void);
	void paint();
};

#endif /* INSTIGMATA_BUTTON_H */
