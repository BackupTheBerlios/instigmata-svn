#include "soundcore.h"
#include "soundplayer.h"
#include "logger.h"
#include <sys/time.h>
#include <time.h>
#include <math.h>

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}

int timer = 0;
int oldtimer = 0;
float lpeak = 0;
float rpeak = 0;

FMOD_RESULT F_CALLBACK dspread(FMOD_DSP_STATE *dsp, float *inbuffer, float *outbuffer, unsigned int length, int inchannels,
int outchannels)
{
	memcpy(outbuffer, inbuffer, length * sizeof(float) * inchannels);
	lpeak = 0;
	rpeak = 0;
	for(int i = 0; i < length * inchannels; i += inchannels){
		if(fabs(inbuffer[i]) > lpeak)
			lpeak = fabs(inbuffer[i]);
		if(fabs(inbuffer[i + 1]) > rpeak)
			rpeak = fabs(inbuffer[i]);
	}
	timer += length;	
}

SoundCore::SoundCore() {
	otime = 0;
	timertick = 0;
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

	sound->system->createDSPByType(FMOD_DSP_TYPE_COMPRESSOR, &compressor);
	compressor->setParameter(FMOD_DSP_COMPRESSOR_ATTACK, 10);
	// compressor->setParameter(FMOD_DSP_COMPRESSOR_ATTACK, 10);

	system->addDSP(compressor);

	ERRCHECK(system->createDSP(&tdsp, &td));
	ERRCHECK(system->addDSP(td));

	system->getSoftwareFormat(&samplerate, 0, 0, 0, 0, 0);
}

void SoundCore::generateBarEvents() {
	if(timer / granularity >= 32){
		if(timer / granularity > 32) {
			LOG("(WW) Glitch detected!");
		}
		timer = 0;
		for(int i = 0; i < players.size(); i++){
			((SoundPlayer *)players[i])->bar();
		}
		bc->bar();
	}
}

void SoundCore::timerTick(){
	if(peakmeter != 0) {
		peakmeter->doubleEvent(EVENT_PEAKMETER_LEFT_CHANNEL, lpeak);
		peakmeter->doubleEvent(EVENT_PEAKMETER_RIGHT_CHANNEL, rpeak);
	}
}

void SoundCore::update() {
	generateBarEvents();
	ERRCHECK(system->update());
	if(timer != oldtimer){
		timerTick();
		oldtimer = timer;
	}
	generateBarEvents();
}

EventListener *SoundCore::registerPlayer(EventListener *pg) {
	SoundPlayer *sp = new SoundPlayer(pg);
	players.push_back(sp);
	return sp;
}

void SoundCore::registerPeakMeter(EventListener *pm) {
	peakmeter = pm;
}
