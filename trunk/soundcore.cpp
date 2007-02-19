#include "soundcore.h"
#include "soundplayer.h"
#include "logger.h"
#include <sys/time.h>
#include <time.h>

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}

int timer = 0;

FMOD_RESULT F_CALLBACK dspread(FMOD_DSP_STATE *dsp, float *inbuffer, float *outbuffer, unsigned int length, int inchannels,
int outchannels)
{
	memcpy(outbuffer, inbuffer, length * sizeof(float) * inchannels);
	timer += length;	
}

SoundCore::SoundCore() {
	otime = 0;
}

void SoundCore::init(int tempo, BarCounter *bc) {
	this->tempo = tempo;
	this->bc = bc;
	
	ERRCHECK(FMOD::System_Create(&system));

	// Calculate buffer granularity based on tempo
	// FIXME: Uses 48000 by default, but I can't check
	// the real sample rate before initializing the engine?
	// Doubleinit engine?
	this->granularity = (int)(((60.0 / tempo) * 48000) / 8);

	ERRCHECK(system->setDSPBufferSize(granularity, 4));
	ERRCHECK(system->init(64, FMOD_INIT_NORMAL, 0));
	
	FMOD_DSP_DESCRIPTION tdsp;

	memset(&tdsp, 0, sizeof(tdsp));

	strcpy(tdsp.name, "timer");
	tdsp.read = dspread;
	tdsp.numparameters = 0;

	FMOD::DSP *td;

	ERRCHECK(system->createDSP(&tdsp, &td));
	ERRCHECK(system->addDSP(td));

	system->getSoftwareFormat(&samplerate, 0, 0, 0, 0, 0);
}

void SoundCore::generateBarEvents() {
	struct timeval t;
	gettimeofday(&t, 0);
    double ntime = (double)t.tv_sec + (t.tv_usec / 1000000.0);
	if(!otime){
		otime = ntime;
		return;
	}
	if(timer / granularity >= 32){
		if(timer / granularity > 32) {
			LOG("(WW) Glitch detected!");
		}
		timer = 0;
		otime = ntime;
		for(int i = 0; i < players.size(); i++){
			((SoundPlayer *)players[i])->bar();
		}
		bc->bar();
	}
}

void SoundCore::update() {
	generateBarEvents();
	ERRCHECK(system->update());
	generateBarEvents();
}

EventListener *SoundCore::registerPlayer(EventListener *pg) {
	SoundPlayer *sp = new SoundPlayer(pg);
	players.push_back(sp);
	return sp;
}
