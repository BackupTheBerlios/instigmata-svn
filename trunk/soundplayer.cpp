#include "soundplayer.h"
#include "soundcore.h"
#include "soundlooper.h"
#include <allegro.h>

#define OPTLPFCO(v) ((v) * 21990.0 + 10)
#define OPTLPFRE(v) ((v) * 9.0 + 1)
#define VOLUMECORRECT(v) (v * (1 - 0.99 * vc))

SoundPlayer::SoundPlayer(EventListener *g) {
	sound->system->createChannelGroup(NULL, &cg);

	sound->system->createDSPByType(FMOD_DSP_TYPE_LOWPASS, &lowpass);
	sound->system->createDSPByType(FMOD_DSP_TYPE_HIGHPASS, &hipass);
	sound->system->createDSPByType(FMOD_DSP_TYPE_DISTORTION, &distortion);
	
	vc = PLAYER_DEFAULT_DISTORTION;
	vol = PLAYER_DEFAULT_VOLUME;

	cg->addDSP(lowpass);
	cg->addDSP(hipass);
	cg->addDSP(distortion);
	cg->setVolume(VOLUMECORRECT(PLAYER_DEFAULT_VOLUME));

	lowpass->setParameter(FMOD_DSP_LOWPASS_CUTOFF, OPTLPFCO(PLAYER_LPF_DEFAULT_CUTOFF));
	lowpass->setParameter(FMOD_DSP_LOWPASS_RESONANCE, OPTLPFRE(PLAYER_LPF_DEFAULT_RESONANCE));
	hipass->setParameter(FMOD_DSP_HIGHPASS_CUTOFF, OPTLPFCO(PLAYER_HPF_DEFAULT_CUTOFF));
	distortion->setParameter(FMOD_DSP_DISTORTION_LEVEL, PLAYER_DEFAULT_DISTORTION);

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

void SoundPlayer::doubleEvent(eventtype et, double data){
	switch(et){
		case EVENT_CHANGE_VOLUME:
			cg->setVolume(VOLUMECORRECT(data));
			vol = data;
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
			// Needs volume correction
			vc = data;
			cg->setVolume(VOLUMECORRECT(vol));
			distortion->setParameter(FMOD_DSP_DISTORTION_LEVEL, data);
			break;
	}
}
