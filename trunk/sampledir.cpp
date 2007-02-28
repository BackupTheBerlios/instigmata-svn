#include "sampledir.h"
#include <stdio.h>
#include <list>
#include <string>

SampleDir::SampleDir(const char *d) {
	char path[1024];
	snprintf(path, 1023, "samples/%s", d);
	
	title = strdup(d);

	DIR *dh = opendir(path);
	struct dirent *de;
	std::list <std::string> smpllist;
	while( (de = readdir(dh)) ){
		if(de->d_type == DT_DIR) // Skip all directories
			continue;
		smpllist.push_back(de->d_name);
	}
	closedir(dh);
	smpllist.sort();

	while(smpllist.size() > 0) {
		std::string str = smpllist.front();
		samples.push_back(strdup(str.c_str()));
		smpllist.pop_front();
	}
}

char *SampleDir::getSample(int i) {
	if(i >= samples.size())
		return NULL;
	return samples[i];
}
