#ifndef INSTIGMATA_SOUNDCORE_H
#define INSTIGMATA_SOUNDCORE_H 1
#include "fmodapi/inc/fmod.hpp"
#include "fmodapi/inc/fmod_errors.h"
#include "event.h"
#include "barcounter.h"
#include <vector>
#include <pthread.h>

class SoundCore {
	private:
	std::vector<EventListener *> players;

	double otime;
	int tempo;
	BarCounter *bc;
	int samplerate;
	int granularity;
	public:
	FMOD::System *system;
	SoundCore();
	void init(int tempo, BarCounter *bc);
	void generateBarEvents();
	void update();
	EventListener *registerPlayer(EventListener *pg);
};

extern SoundCore *sound;

void ERRCHECK(FMOD_RESULT result);

#endif /* INSTIGMATA_SOUNDCORE_H */