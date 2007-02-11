#ifndef INSTIGMATA_LOADER_H
#define INSTIGMATA_LOADER_H 1
#include "box.h"
#include <dirent.h>
#include <vector>
#include "sampledir.h"
#include "event.h"

class Loader : public Box {
	std::vector<SampleDir *> dirs;
	SampleDir *current_dir;
	EventListener *demander;
	bool addDir(char *d);
	int numsamples;
	bool display;
	void chooseSample(int i);
	public:
	Loader();
	bool needsDisplay();
	void cancelDisplay();
	void drawDirectories();
	void drawSamples();
	void paint();
	bool handleMouseEvent(int x, int y, int b);
	void getSample(EventListener *s);
};

extern Loader *loader;

#endif /* INSTIGMATA_LOADER_H */
