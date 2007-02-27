		#include "soundplayer.h"
#include "soundcore.h"
#include "soundlooper.h"
#include <allegro.h>
#include <math.h>

#define OPTLPFCO(v) ((v) * 21990.0 + 10)
#define OPTLPFRE(v) ((v) * 9.0 + 1)
#define VOLUMECORRECT(v) (v * (1 - 0.99 * vc))
#define EQCC(v) (v * (22000.0 - 20.0) + 20.0)
#define EQGC(v) (v * (3.0 - 0.05) + 0.05)

FMOD_DSP_DESCRIPTION ddsp;

FMOD_RESULT F_CALLBACK dspdistortion(FMOD_DSP_STATE *dsp, float *inbuffer, float *outbuffer, unsigned int length, int inchannels,
int outchannels)
{
	float drive = *((float *)dsp->plugindata);
/*	if(drive == 0) {
		memcpy(outbuffer, inbuffer, length * sizeof(float) * inchannels);
		return FMOD_OK; // Bypass
	}*/

	for(int i = 0; i < length * inchannels; i += inchannels){
		 float mult=pow(10,drive*drive*3.0)-1.0+0.001;
	     float div=1.0+drive*8;
    	 outbuffer[i]=atan(inbuffer[i]*mult)/atan(mult);
	     outbuffer[i+1]=atan(inbuffer[i+1]*mult)/atan(mult);
    	 outbuffer[i]/=div;
	     outbuffer[i+1]/=div;
	}
	return FMOD_OK;
}


FMOD_RESULT F_CALLBACK dsprelease(FMOD_DSP_STATE *dsp)
{
    float *gain = (float *)dsp->plugindata;

    free(gain);

    return FMOD_OK;
}


FMOD_RESULT F_CALLBACK dspcreate(FMOD_DSP_STATE *dsp)
{
    dsp->plugindata = malloc(sizeof(float));

    return FMOD_OK;
}


FMOD_RESULT F_CALLBACK dspsetparam(FMOD_DSP_STATE *dsp, int index, float value)
{
    float *gain = (float *)dsp->plugindata;

    switch (index)
    {
        case 0:
        {
            (*gain) = value;
            break;
        }
    }
    return FMOD_OK;
}

SoundPlayer::SoundPlayer(EventListener *g) {
	sound->system->createChannelGroup(NULL, &cg);

	sound->system->createDSPByType(FMOD_DSP_TYPE_LOWPASS, &lowpass);
	sound->system->createDSPByType(FMOD_DSP_TYPE_HIGHPASS, &hipass);
	ERRCHECK(sound->system->createDSPByType(FMOD_DSP_TYPE_PARAMEQ, &eq1));
	
	vc = PLAYER_DEFAULT_DISTORTION;
	vol = PLAYER_DEFAULT_VOLUME;

	cg->addDSP(lowpass);
	cg->addDSP(hipass);
//	cg->addDSP(distortion);
//	ERRCHECK(cg->addDSP(eq1));



	memset(&ddsp, 0, sizeof(ddsp));

	FMOD_DSP_PARAMETERDESC *pdsc = (FMOD_DSP_PARAMETERDESC *)malloc(sizeof(FMOD_DSP_PARAMETERDESC));

	memset(pdsc, 0, sizeof(ddsp));

	pdsc->min = 0;
	pdsc->max = 1;
	pdsc->defaultval = 0;

	strcpy(ddsp.name, "Distortion");
	ddsp.read = dspdistortion;
	ddsp.create = dspcreate;
	ddsp.setparameter = dspsetparam;
	ddsp.release = dsprelease;
	ddsp.numparameters = 1;
	ddsp.paramdesc = pdsc;
	
	ERRCHECK(sound->system->createDSP(&ddsp, &distortion));

	ERRCHECK(cg->addDSP(distortion));

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
			eq1->setActive(true);
			ERRCHECK(eq1->setParameter(FMOD_DSP_PARAMEQ_CENTER, EQCC(data)));
			break;
		case EVENT_CHANGE_EQ1_GAIN:
			ERRCHECK(eq1->setParameter(FMOD_DSP_PARAMEQ_CENTER, EQGC(data)));
			break;	
	}
}
