#include <math.h>
#include "distortion.h"

FMOD_RESULT F_CALLBACK sdspread(FMOD_DSP_STATE *dsp, float *inbuffer, float *outbuffer, unsigned int length, int inchannels,
int outchannels)
{
	int slice = (int)(60.0 / sound->getTempo() / 4 * sound->getSamplerate());
    int counter = *(int *)(dsp->plugindata);

	for(int i = 0; i < length * inchannels; i += inchannels){
		if(counter < slice) {
			outbuffer[i] = inbuffer[i];
			outbuffer[i+1] = inbuffer[i+1];
		} else {
			outbuffer[i] = 0;//inbuffer[i] * 0.1;
			outbuffer[i+1] = 0;//inbuffer[i + 1] * 0.1;
		}
		if(counter < slice * 2)
			counter++;
		else
			counter = 0;
	}

	(*(int *)(dsp->plugindata)) = counter;
	
	return FMOD_OK;
}


FMOD_RESULT F_CALLBACK sdsprelease(FMOD_DSP_STATE *dsp)
{
    int *counter = (int *)dsp->plugindata;

    free(counter);

    return FMOD_OK;
}


FMOD_RESULT F_CALLBACK sdspcreate(FMOD_DSP_STATE *dsp)
{
    dsp->plugindata = malloc(sizeof(int));
    int *counter = (int *)dsp->plugindata;
	*counter = 0;
    return FMOD_OK;
}

FMOD_RESULT F_CALLBACK sdspreset(FMOD_DSP_STATE *dsp)
{
    int *counter = (int *)dsp->plugindata;
	*counter = 0;
    return FMOD_OK;
}

FMOD::DSP *getSlicer() {

	FMOD_DSP_DESCRIPTION *sdsp = (FMOD_DSP_DESCRIPTION *)malloc(sizeof(FMOD_DSP_DESCRIPTION));
	memset(sdsp, 0, sizeof(FMOD_DSP_DESCRIPTION));

	strcpy(sdsp->name, "Slicer");
	sdsp->read = sdspread;
	sdsp->create = sdspcreate;
	sdsp->release = sdsprelease;
	sdsp->reset = sdspreset;

	FMOD::DSP *slicer;
	
	ERRCHECK(sound->system->createDSP(sdsp, &slicer));
	return slicer;
}

