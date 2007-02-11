#include "looper.h"
#include "button.h"
#include "colors.h"
#include "selectgroup.h"
#include "loader.h"
#include "eventbutton.h"
#include "soundcore.h"
#include "soundplayer.h"

Looper::Looper(int x, int color, EventListener *player) 
	: Box(x, 3, 148, 90, color, Box::TYPE_BEVEL)
{
	char *loop_names[] = { "4", "8", "16", "32" };
	char *start_names[] = { "1", "2", "3", "4" };

	this->player = player;
	this->looper = ((SoundPlayer *)player)->registerLooper(this);
	this->trigger = new EventButton(1, 1, 50, 44, COLOR_TRG_NOTLOADED, this, EVENT_SAMPLE_TRIGGER, "Trg");
	
	addChild(trigger);
	addChild(new EventButton(1, 45, 50, 44, COLOR_DEFAULT_BUTTON, this, EVENT_SAMPLE_LOAD_BUTTON, "Load"));
	addChild(new SelectGroup(51, 1, 4, loop_names, 0, COLOR_DEFAULT_BUTTON, EVENT_CHANGE_LOOP_LENGTH, looper));
	addChild(new SelectGroup(51, 25, 4, start_names, 0, COLOR_DEFAULT_BUTTON, EVENT_CHANGE_LOOP_START, looper));
}

void Looper::strEvent(eventtype et, char *data) {
	// currently catches only sample load
	looper->strEvent(EVENT_SAMPLE_LOAD, data);
}

void Looper::intEvent(eventtype et, int data){
	switch(et) {
		case EVENT_CHANGE_TRG_COLOR:
			trigger->changeColor(data);
			if(!(loader->needsDisplay()))
				trigger->quePaint();
			break;
	}
}

void Looper::emptyEvent(eventtype et) {
	switch(et) {
		case EVENT_SAMPLE_LOAD_BUTTON:
			loader->getSample(this);
			break;
		
		case EVENT_SAMPLE_TRIGGER:
			looper->emptyEvent(EVENT_SAMPLE_TRIGGER);
			break;
	}
}

