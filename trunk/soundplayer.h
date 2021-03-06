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
#define PLAYER_EQ1_DEFAULT_CENTER 0.05
#define PLAYER_DEFAULT_PAN 0.5
// #define PLAYER_EQ1_DEFAULT_GAIN 0.32203389
// #define PLAYER_EQ1_DEFAULT_GAIN 0.



class SoundPlayer : public EventListener {
	FMOD::ChannelGroup *cg;
	FMOD::Channel *chan[8];

	FMOD::DSP *lowpass;
	FMOD::DSP *hipass;
	FMOD::DSP *distortion;
	FMOD::DSP *slicer;
	FMOD::DSP *echo;
	FMOD::DSP *reverb;
	FMOD::DSP *amp;
	FMOD::DSP *pan;
	
	double vc;
	double vol;
	float distgain;

	EventListener *gui;
	std::vector<SoundLooper *> loopers;
	int curchan;
	public:
	SoundPlayer(EventListener *);
	EventListener *registerLooper(EventListener *g);
	void doubleEvent(eventtype et, double data);
	void boolEvent(eventtype et, bool data);
	void bar();
};

#endif
