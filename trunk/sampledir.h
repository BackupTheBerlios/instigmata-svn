#ifndef INSTIGMATA_SAMPLEDIR_H
#define INSTIGMATA_SAMPLEDIR_H 1
#include <dirent.h>
#include <vector>

class SampleDir {
	private:
	std::vector<char *> samples;
	char *title;
	
	public:
	SampleDir(char *d);
 	char *getSample(int i);
	char *getName() { return title; }
};

#endif /* INSTIGMATA_LOADER_H */
