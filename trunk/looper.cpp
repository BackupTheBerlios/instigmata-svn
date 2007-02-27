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

	sampleName = 0;
	dirName = 0;
	
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
	quePaint();
	looper->strEvent(EVENT_SAMPLE_LOAD, data);
	if(sampleName != 0)
		free(sampleName);
	if(dirName != 0)
		free(dirName);

	data += strlen(SAMPLEDIR) + 1;
	char *tmp = index(data, '/');
	*tmp = 0;
	if(strlen(tmp + 1) > 12)
		*(tmp+12) = 0;
	if(char *tmp2 = index(tmp + 1, '.'))
		*tmp2 = 0;

	sampleName = strdup(tmp + 1);
	
	
	if(strlen(data) > 11)
		*(data+11) = 0;

	dirName = strdup(data);
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

void Looper::paint() {
	Box::paint();
	if(sampleName == 0)
		return;
	textprintf_ex(screen, font, x + 55, y + 53 + 2, COLOR_DEFAULT_BUTTONTEXT_SHADOW, -1, "%s", dirName);
	textprintf_ex(screen, font, x + 55 , y + 53, COLOR_DEFAULT_BUTTONTEXT, -1, "%s", dirName);

	textprintf_ex(screen, font, x + 55, y + 69 + 2, COLOR_DEFAULT_BUTTONTEXT_SHADOW, -1, "%s", sampleName);
	textprintf_ex(screen, font, x + 55 , y + 69, COLOR_DEFAULT_BUTTONTEXT, -1, "%s", sampleName);
}
