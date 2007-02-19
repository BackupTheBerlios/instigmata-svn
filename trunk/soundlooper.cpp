#include "soundlooper.h"
#include "colors.h"
#include <math.h>
#include <sys/time.h>
#include <time.h>

SoundLooper::SoundLooper(FMOD::ChannelGroup *cg, EventListener *gui) {
	this->cg = cg;
	this->gui = gui;
	this->status = LOOPER_UNLOADED;
	bars = 0;
	start_at = 0;
	play_to = 3;
}

void SoundLooper::loadSample(char *fname) {
	ERRCHECK(sound->system->createSound(fname, FMOD_SOFTWARE|FMOD_LOOP_OFF|FMOD_NONBLOCKING, 0, &sample));
	gui->intEvent(EVENT_CHANGE_TRG_COLOR, COLOR_TRG_IDLE);
	status = LOOPER_IDLE;
}

void SoundLooper::strEvent(eventtype et, char *data){
	if(et == EVENT_SAMPLE_LOAD) {
		loadSample(data);
	}
}

void SoundLooper::intEvent(eventtype et, int data){
	switch(et) {
		case EVENT_CHANGE_LOOP_LENGTH:
			play_to = (4 * (int)pow(2, data)) - 1;
			break;
		case EVENT_CHANGE_LOOP_START:
			start_at = data;
			break;
	}	
}

void SoundLooper::emptyEvent(eventtype et){
	switch(et){
		case EVENT_SAMPLE_TRIGGER:
			if(status == LOOPER_IDLE || status == LOOPER_STOPPING) {
				status = LOOPER_QUEUED;
				gui->intEvent(EVENT_CHANGE_TRG_COLOR, COLOR_TRG_QUEUED);
			} else if(status == LOOPER_PLAYING || status == LOOPER_QUEUED) {
				status = LOOPER_STOPPING;
				gui->intEvent(EVENT_CHANGE_TRG_COLOR, COLOR_TRG_STOPPING);		
			}
			break;
	}
}

void SoundLooper::bar() {
	if(!(bars % 4) && bars > play_to){
		bars = 0;
	}
	if(bars == start_at){
		int status_was = status;
		// Play sound
		if (status == LOOPER_QUEUED){
			status = LOOPER_PLAYING;
		}
	
		if (status == LOOPER_STOPPING){
			status = LOOPER_IDLE;
			gui->intEvent(EVENT_CHANGE_TRG_COLOR, COLOR_TRG_IDLE);
		}
		if (status == LOOPER_PLAYING){
			FMOD::Channel *ch;
			ERRCHECK(sound->system->playSound(FMOD_CHANNEL_FREE, sample, false, &ch));
			ERRCHECK(ch->setChannelGroup(cg));
		}
		if(status_was != status) {
			gui->intEvent(EVENT_CHANGE_TRG_COLOR, status==LOOPER_PLAYING?COLOR_TRG_PLAYING:COLOR_TRG_IDLE);
		}
	}

	if(bars == play_to) {
		bars = 0;
	}
	else
		bars++;
}


