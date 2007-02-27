#include "soundplayer.h"
#include "soundcore.h"
#include "soundlooper.h"
#include "distortion.h"
#include "slicer.h"
#include "amp.h"
#include <allegro.h>
#include <math.h>

#define OPTLPFCO(v) ((v) * 21990.0 + 10)
#define OPTLPFRE(v) ((v) * 9.0 + 1)
#define EQCC(v) (v * (22000.0 - 20.0) + 20.0)
#define EQGC(v) (v * (3.0 - 0.05) + 0.05)


SoundPlayer::SoundPlayer(EventListener *g) {
	sound->system->createChannelGroup(NULL, &cg);

	sound->system->createDSPByType(FMOD_DSP_TYPE_LOWPASS, &lowpass);
	sound->system->createDSPByType(FMOD_DSP_TYPE_HIGHPASS, &hipass);
	sound->system->createDSPByType(FMOD_DSP_TYPE_ECHO, &echo);
	sound->system->createDSPByType(FMOD_DSP_TYPE_REVERB, &reverb);
	
	vc = PLAYER_DEFAULT_DISTORTION;
	vol = PLAYER_DEFAULT_VOLUME;
	
	cg->setVolume(PLAYER_DEFAULT_VOLUME);

	distortion = getDistortion();
	slicer = getSlicer();
	amp = getAmp();
	
	cg->addDSP(amp);
	cg->addDSP(reverb);
	cg->addDSP(echo);
	cg->addDSP(lowpass);
	cg->addDSP(hipass);
	ERRCHECK(cg->addDSP(distortion));
	ERRCHECK(cg->addDSP(slicer));

	slicer->setBypass(true);
	echo->setBypass(true);
	reverb->setBypass(true);
	
	printf("Echo delay is: %f", 60.0 / (float)sound->getTempo() * 1000 / 2);

	echo->setParameter(FMOD_DSP_ECHO_DELAY, 60.0 / (float)sound->getTempo() * 1000 / 2);
	echo->setParameter(FMOD_DSP_ECHO_WETMIX, 0.4);
	echo->setParameter(FMOD_DSP_ECHO_DRYMIX, 1);

	lowpass->setParameter(FMOD_DSP_LOWPASS_CUTOFF, OPTLPFCO(PLAYER_LPF_DEFAULT_CUTOFF));
	lowpass->setParameter(FMOD_DSP_LOWPASS_RESONANCE, OPTLPFRE(PLAYER_LPF_DEFAULT_RESONANCE));
	hipass->setParameter(FMOD_DSP_HIGHPASS_CUTOFF, OPTLPFCO(PLAYER_HPF_DEFAULT_CUTOFF));
	distortion->setParameter(0, PLAYER_DEFAULT_DISTORTION);
	amp->setParameter(0, PLAYER_DEFAULT_VOLUME);

	this->gui = g;
}

EventListener *SoundPlayer::registerLooper(EventListener *g) {
	SoundLooper *sl = new SoundLooper(cg, g);
	loopers.push_back(sl);
	return sl;
}

void SoundPlayer::bar() {
	for(int i = 0; i < loopers.size(); i++) {
		loopers[i]->bar();
	}
}

void SoundPlayer::boolEvent(eventtype et, bool data) {
	switch(et){
		case EVENT_TOGGLE_SLICER:
			slicer->setBypass(!data);
			break;
		case EVENT_TOGGLE_ECHO:
			echo->setBypass(!data);
			break;
		case EVENT_TOGGLE_REVERB:
			reverb->setBypass(!data);
			break;
		default:
			break;
	}
}

void SoundPlayer::doubleEvent(eventtype et, double data){
	switch(et){
		case EVENT_CHANGE_VOLUME:
			cg->setVolume(data);
			break;
		case EVENT_CHANGE_POST_VOLUME:
			amp->setParameter(0, data);
			break;
		case EVENT_CHANGE_LPF_CUTOFF:
			lowpass->setParameter(FMOD_DSP_LOWPASS_CUTOFF, OPTLPFCO(data));
			break;
		case EVENT_CHANGE_LPF_RESONANCE:
			lowpass->setParameter(FMOD_DSP_LOWPASS_RESONANCE, OPTLPFRE(data));
			break;
		case EVENT_CHANGE_HPF_CUTOFF:
			hipass->setParameter(FMOD_DSP_HIGHPASS_CUTOFF, OPTLPFCO(data));
			break;
		case EVENT_CHANGE_DISTORTION:
			distortion->setParameter(0, data);
			break;
	}
}
