#ifndef INSTIGMATA_SOUNDPLAYER_H
#define INSTIGMATA_SOUNDPLAYER_H
#include "soundcore.h"
#include "event.h"
#include "soundlooper.h"
#include <vector>

#define PLAYER_DEFAULT_VOLUME 0.3
#define PLAYER_LPF_DEFAULT_CUTOFF 1.0
#define PLAYER_LPF_DEFAULT_RESONANCE 0.0
#define PLAYER_HPF_DEFAULT_CUTOFF 0.0
#define PLAYER_DEFAULT_DISTORTION 0.0

class SoundPlayer : public EventListener {
	FMOD::ChannelGroup *cg;
	FMOD::Channel *chan[8];

	FMOD::DSP *lowpass;
	FMOD::DSP *hipass;
	FMOD::DSP *distortion;
	
	double vc;
	double vol;

	EventListener *gui;
	std::vector<SoundLooper *> loopers;
	int curchan;
	public:
	SoundPlayer(EventListener *);
	EventListener *registerLooper(EventListener *g);
	void doubleEvent(eventtype et, double data);
	void bar();
};

#endif