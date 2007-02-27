#include "soundplayer.h"
#include "soundcore.h"
#include "soundlooper.h"
#include "distortion.h"
#include "slicer.h"
#include <allegro.h>
#include <math.h>

#define OPTLPFCO(v) ((v) * 21990.0 + 10)
#define OPTLPFRE(v) ((v) * 9.0 + 1)
#define VOLUMECORRECT(v) (v * (1 - 0.99 * vc))
#define EQCC(v) (v * (22000.0 - 20.0) + 20.0)
#define EQGC(v) (v * (3.0 - 0.05) + 0.05)


SoundPlayer::SoundPlayer(EventListener *g) {
	sound->system->createChannelGroup(NULL, &cg);

	sound->system->createDSPByType(FMOD_DSP_TYPE_LOWPASS, &lowpass);
	sound->system->createDSPByType(FMOD_DSP_TYPE_HIGHPASS, &hipass);
	ERRCHECK(sound->system->createDSPByType(FMOD_DSP_TYPE_PARAMEQ, &eq1));
	
	vc = PLAYER_DEFAULT_DISTORTION;
	vol = PLAYER_DEFAULT_VOLUME;

	cg->addDSP(lowpass);
	cg->addDSP(hipass);

	distortion = getDistortion();
	slicer = getSlicer();
	
	ERRCHECK(cg->addDSP(distortion));
	ERRCHECK(cg->addDSP(slicer));
	slicer->setBypass(true);

	cg->setVolume(VOLUMECORRECT(PLAYER_DEFAULT_VOLUME));

	lowpass->setParameter(FMOD_DSP_LOWPASS_CUTOFF, OPTLPFCO(PLAYER_LPF_DEFAULT_CUTOFF));
	lowpass->setParameter(FMOD_DSP_LOWPASS_RESONANCE, OPTLPFRE(PLAYER_LPF_DEFAULT_RESONANCE));
	hipass->setParameter(FMOD_DSP_HIGHPASS_CUTOFF, OPTLPFCO(PLAYER_HPF_DEFAULT_CUTOFF));
	eq1->setParameter(FMOD_DSP_PARAMEQ_CENTER, EQCC(PLAYER_EQ1_DEFAULT_CENTER));
	eq1->setParameter(FMOD_DSP_PARAMEQ_GAIN, EQGC(PLAYER_EQ1_DEFAULT_GAIN));
	distortion->setParameter(0, PLAYER_DEFAULT_DISTORTION);

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
		default:
			break;
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
			distortion->setParameter(0, data);
			break;
		case EVENT_CHANGE_EQ1_CENTER:
			eq1->setBypass(false);
			eq1->setBypass(true);
			ERRCHECK(eq1->setParameter(FMOD_DSP_PARAMEQ_CENTER, EQCC(data)));
			break;
		case EVENT_CHANGE_EQ1_GAIN:
			ERRCHECK(eq1->setParameter(FMOD_DSP_PARAMEQ_CENTER, EQGC(data)));
			break;	
	}
}
