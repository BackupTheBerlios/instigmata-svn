#include <math.h>
#include "pan.h"

FMOD_RESULT F_CALLBACK pdspread(FMOD_DSP_STATE *dsp, float *inbuffer, float *outbuffer, unsigned int length, int inchannels,
int outchannels)
{
	float drive = *((float *)dsp->plugindata);
	float lvol = 1 - drive;
	float rvol = 1 - -drive;
	for(int i = 0; i < length * inchannels; i += inchannels){
    	 outbuffer[i]=inbuffer[i]*lvol;
	     outbuffer[i+1]=inbuffer[i+1]*rvol;
	}
	return FMOD_OK;
}


FMOD_RESULT F_CALLBACK pdsprelease(FMOD_DSP_STATE *dsp)
{
    float *gain = (float *)dsp->plugindata;

    free(gain);

    return FMOD_OK;
}


FMOD_RESULT F_CALLBACK pdspcreate(FMOD_DSP_STATE *dsp)
{
    dsp->plugindata = malloc(sizeof(float));

    return FMOD_OK;
}


FMOD_RESULT F_CALLBACK pdspsetparam(FMOD_DSP_STATE *dsp, int index, float value)
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

FMOD::DSP *getPanner() {

	FMOD_DSP_DESCRIPTION *pdsp = (FMOD_DSP_DESCRIPTION *)malloc(sizeof(FMOD_DSP_DESCRIPTION));
	memset(pdsp, 0, sizeof(FMOD_DSP_DESCRIPTION));

	FMOD_DSP_PARAMETERDESC *pdsc = (FMOD_DSP_PARAMETERDESC *)malloc(sizeof(FMOD_DSP_PARAMETERDESC));

	memset(pdsc, 0, sizeof(FMOD_DSP_PARAMETERDESC));

	pdsc->min = -1;
	pdsc->max = 1;
	pdsc->defaultval = 0;

	strcpy(pdsp->name, "Panner");
	pdsp->read = pdspread;
	pdsp->create = pdspcreate;
	pdsp->setparameter = pdspsetparam;
	pdsp->release = pdsprelease;
	pdsp->numparameters = 1;
	pdsp->paramdesc = pdsc;

	FMOD::DSP *amp;
	
	ERRCHECK(sound->system->createDSP(pdsp, &amp));
	return amp;

}

