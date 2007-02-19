#include "loader.h"
#include "colors.h"
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include "soundcore.h"

Loader::Loader() 
	: Box(0, 32, 1024, 736, 0, Box::TYPE_FLAT)
{
	// Parse the samples directory
	display = false;

	DIR *dh = opendir("samples");
	struct dirent *de;
	struct stat s;
	while( (de = readdir(dh)) ){
		if(de->d_type != DT_DIR) // Only count directories
			continue;
		if(de->d_name[0] == '.') // Skip dirs starting with dot
			continue;
		addDir(de->d_name);
		printf("%s\n", de->d_name);
	}
	closedir(dh);

	printf("We have %i sample dirs\n", dirs.size());

	if(dirs.size())
		current_dir = dirs[0];
	else
		current_dir = 0;
}

bool Loader::addDir(char *d){
	dirs.push_back(new SampleDir(d));
	return true;
}

bool Loader::needsDisplay(){
	return display;
}

void Loader::cancelDisplay(){
	display = false;
}

void Loader::drawDirectories() {
	char title[23];
	memset(title, 0, 23);
	int i;
	for(int i = 0; i < dirs.size(); i++){
		sound->update();
		strncpy(title, dirs[i]->getName(), 22);
		if(current_dir == dirs[i])
			rectfill(screen, 0, i * 40 + 32, 200, i * 40 + 39 + 32, COLOR_SELECTED_DIRECTORY);
		else
			rectfill(screen, 0, i * 40 + 32, 200, i * 40 + 39 + 32, COLOR_DEFAULT_DIRECTORY);

		textprintf_ex(screen, font, 10, i * 40 + 32 + 15, makecol(255,255,255), -1, "%s", title); 
		rect(screen, 0, i * 40 + 32, 200, i * 40 + 39 + 32, 0);
	}
}

void Loader::drawSamples(){
	if(!current_dir)
		return;

	char title[23];
	memset(title, 0, 23);
	int i;

	for(i = 0; char *sample = current_dir->getSample(i); i++){
		sound->update();
		int x = 201 + (i % 4) * 206;
		int y = i / 4 * 40 + 32;
		strncpy(title, sample, 22);

		rectfill(screen, x, y, x + 206, y + 40, COLOR_SAMPLE_FILE);
		textprintf_ex(screen, font, x + 10, y + 15, makecol(255,255,255), -1, "%s", title); 
		rect(screen, x, y, x + 206, y + 40, 0);
	}
	numsamples = i;
}

void Loader::chooseSample(int i){
	display = false;
	char *name = (char *)malloc(2048 * sizeof(char));
	snprintf(name, 2047, "samples/%s/%s", current_dir->getName(), current_dir->getSample(i));
	demander->strEvent(EVENT_SAMPLE_LOAD, name);
}

void Loader::getSample(EventListener *s){
	demander = s;
	display = true;
	paint();
} 

bool Loader::handleMouseEvent(int x, int y, int b){
	if(x < 200) {
		int dir = (y - 32) / 40;
		if(dir < dirs.size()) {
			current_dir = dirs[dir];
			paint();
		}	
	} else {
		x = x - 200;
		y = y - 32;
		int s = (x / 206) + (y / 40 * 4);
		if(s < numsamples){
			chooseSample(s);
		}
	}
	return true;
}

void Loader::paint() {
	scare_mouse();
	Box::paint(); // Too lazy to use the normal GUI, also hoping to speed things up...
	drawDirectories();
	drawSamples();
	unscare_mouse();
}


