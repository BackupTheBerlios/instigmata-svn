#ifndef INSTIGMATA_SOUNDCORE_H
#define INSTIGMATA_SOUNDCORE_H 1
#include "fmodapi/inc/fmod.hpp"
#include "fmodapi/inc/fmod_errors.h"
#include "event.h"
#include "barcounter.h"
#include <vector>
#include <pthread.h>

class SoundCore : public EventListener {
	private:
	std::vector<EventListener *> players;
	EventListener *peakmeter;

	double otime;
	int tempo;
	BarCounter *bc;
	int samplerate;
	int granularity;
	int timertick;
	void timerTick();
	FMOD::DSP *compressor;

	public:
	FMOD::System *system;
	SoundCore();
	void init(int tempo, BarCounter *bc);
	void generateBarEvents();
	void update();
	EventListener *registerPlayer(EventListener *pg);
	void registerPeakMeter(EventListener *pm);
};

extern SoundCore *sound;

void ERRCHECK(FMOD_RESULT result);

#endif /* INSTIGMATA_SOUNDCORE_H */
