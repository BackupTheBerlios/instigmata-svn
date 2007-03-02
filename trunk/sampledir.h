#ifndef INSTIGMATA_SAMPLEDIR_H
#define INSTIGMATA_SAMPLEDIR_H 1
#include <dirent.h>
#include <vector>
#include "soundcore.h"

class SampleDir {
	private:
	std::vector<char *> samples;
	std::vector<FMOD::Sound *> rsamples;
	char *title;
	
	public:
	SampleDir(const char *d);
 	char *getSample(int i);
	void *getMemorySample(int i);
	char *getName() { return title; }
};

#endif /* INSTIGMATA_LOADER_H */
