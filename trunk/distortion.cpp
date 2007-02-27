#include <math.h>
#include "distortion.h"

FMOD_RESULT F_CALLBACK ddspread(FMOD_DSP_STATE *dsp, float *inbuffer, float *outbuffer, unsigned int length, int inchannels,
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


FMOD_RESULT F_CALLBACK ddsprelease(FMOD_DSP_STATE *dsp)
{
    float *gain = (float *)dsp->plugindata;

    free(gain);

    return FMOD_OK;
}


FMOD_RESULT F_CALLBACK ddspcreate(FMOD_DSP_STATE *dsp)
{
    dsp->plugindata = malloc(sizeof(float));

    return FMOD_OK;
}


FMOD_RESULT F_CALLBACK ddspsetparam(FMOD_DSP_STATE *dsp, int index, float value)
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

FMOD::DSP *getDistortion() {

	FMOD_DSP_DESCRIPTION *ddsp = (FMOD_DSP_DESCRIPTION *)malloc(sizeof(FMOD_DSP_DESCRIPTION));
	memset(ddsp, 0, sizeof(FMOD_DSP_DESCRIPTION));

	FMOD_DSP_PARAMETERDESC *pdsc = (FMOD_DSP_PARAMETERDESC *)malloc(sizeof(FMOD_DSP_PARAMETERDESC));

	memset(pdsc, 0, sizeof(FMOD_DSP_PARAMETERDESC));

	pdsc->min = 0;
	pdsc->max = 1;
	pdsc->defaultval = 0;

	strcpy(ddsp->name, "Distortion");
	ddsp->read = ddspread;
	ddsp->create = ddspcreate;
	ddsp->setparameter = ddspsetparam;
	ddsp->release = ddsprelease;
	ddsp->numparameters = 1;
	ddsp->paramdesc = pdsc;

	FMOD::DSP *distortion;
	
	ERRCHECK(sound->system->createDSP(ddsp, &distortion));
	return distortion;

}

