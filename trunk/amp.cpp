#include <math.h>
#include "amp.h"

FMOD_RESULT F_CALLBACK adspread(FMOD_DSP_STATE *dsp, float *inbuffer, float *outbuffer, unsigned int length, int inchannels,
int outchannels)
{
	float drive = *((float *)dsp->plugindata);
	for(int i = 0; i < length * inchannels; i += inchannels){
    	 outbuffer[i]=inbuffer[i]*drive;
	     outbuffer[i+1]=inbuffer[i+1]*drive;
	}
	return FMOD_OK;
}


FMOD_RESULT F_CALLBACK adsprelease(FMOD_DSP_STATE *dsp)
{
    float *gain = (float *)dsp->plugindata;

    free(gain);

    return FMOD_OK;
}


FMOD_RESULT F_CALLBACK adspcreate(FMOD_DSP_STATE *dsp)
{
    dsp->plugindata = malloc(sizeof(float));

    return FMOD_OK;
}


FMOD_RESULT F_CALLBACK adspsetparam(FMOD_DSP_STATE *dsp, int index, float value)
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

FMOD::DSP *getAmp() {

	FMOD_DSP_DESCRIPTION *adsp = (FMOD_DSP_DESCRIPTION *)malloc(sizeof(FMOD_DSP_DESCRIPTION));
	memset(adsp, 0, sizeof(FMOD_DSP_DESCRIPTION));

	FMOD_DSP_PARAMETERDESC *pdsc = (FMOD_DSP_PARAMETERDESC *)malloc(sizeof(FMOD_DSP_PARAMETERDESC));

	memset(pdsc, 0, sizeof(FMOD_DSP_PARAMETERDESC));

	pdsc->min = 0;
	pdsc->max = 1;
	pdsc->defaultval = 0;

	strcpy(adsp->name, "Amp");
	adsp->read = adspread;
	adsp->create = adspcreate;
	adsp->setparameter = adspsetparam;
	adsp->release = adsprelease;
	adsp->numparameters = 1;
	adsp->paramdesc = pdsc;

	FMOD::DSP *amp;
	
	ERRCHECK(sound->system->createDSP(adsp, &amp));
	return amp;

}

