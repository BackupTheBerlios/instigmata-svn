#include "sampledir.h"
#include <stdio.h>

SampleDir::SampleDir(char *d) {
	char path[1024];
	snprintf(path, 1023, "samples/%s", d);
	
	title = strdup(d);

	DIR *dh = opendir(path);
	struct dirent *de;
	while( (de = readdir(dh)) ){
		if(de->d_type == DT_DIR) // Skip all directories
			continue;
		printf("Sample: %s\n", de->d_name);
		samples.push_back(strdup(de->d_name));
	}
	closedir(dh);
}

char *SampleDir::getSample(int i) {
	if(i >= samples.size())
		return NULL;
	return samples[i];
}
