#ifndef INSTIGMATA_LOOPER_H
#define INSTIGMATA_LOOPER_H 1
#include "box.h"
#include "event.h"
#include "eventbutton.h"

class Looper 
	: public Box,
	 public EventListener
{
	private:
	EventListener *player;
	EventListener *looper;
	EventButton *trigger;
	// SoundLooper *looper;
	public:
	Looper(int y, int c, EventListener *);
	void emptyEvent(eventtype et);
	void strEvent(eventtype et, char *data);
	void intEvent(eventtype et, int data);
};

#endif /* INSTIGMATA_LOOPER_H */
