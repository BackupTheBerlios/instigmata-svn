#ifndef INSTIGMATA_SOUNDLOOPER_H
#define INSTIGMATA_SOUNDLOOPER_H
#include "soundcore.h"
#include "event.h"

class SoundLooper : public EventListener {
	FMOD::ChannelGroup *cg;
	EventListener *gui;
	EventListener *player;
	std::vector<SoundLooper *> loopers;
	FMOD::Sound *sample;

	int bars;
	int start_at;
	int play_to;

	enum looperstatus {
		LOOPER_UNLOADED,
		LOOPER_IDLE,
		LOOPER_QUEUED,
		LOOPER_PLAYING,
		LOOPER_STOPPING
	};

	int status;

	void loadSample(char *fname);
	public:
	SoundLooper(FMOD::ChannelGroup *cg, EventListener *);
	void strEvent(eventtype et, char *data);
	void intEvent(eventtype et, int data);
	void emptyEvent(eventtype et);
	void bar();
};

#endif
