#include "loader.h"
#include "colors.h"
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <list>
#include <string>
#include "soundcore.h"

Loader::Loader() 
	: Box(0, 0, 1024, 786, 0, Box::TYPE_FLAT)
{
	// Parse the samples directory
	display = false;
	
	dbuf = 0;

	DIR *dh = opendir(SAMPLEDIR);
	struct dirent *de;
	struct stat s;
	std::list<std::string> dirlist;

	while( (de = readdir(dh)) ){
		if(de->d_type != DT_DIR) // Only count directories
			continue;
		if(de->d_name[0] == '.') // Skip dirs starting with dot
			continue;
		
		dirlist.push_back(de->d_name);
	}
	closedir(dh);

	dirlist.sort();

	while(dirlist.size() > 0) {
		std::string str = dirlist.front();
		addDir(str.c_str());
		dirlist.pop_front();
	}

	if(dirs.size())
		current_dir = dirs[0];
	else
		current_dir = 0;
}

bool Loader::addDir(const char *d){
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
			rectfill(dbuf, 0, i * 40 + 32, 200, i * 40 + 39 + 32, COLOR_SELECTED_DIRECTORY);
		else
			rectfill(dbuf, 0, i * 40 + 32, 200, i * 40 + 39 + 32, COLOR_DEFAULT_DIRECTORY);

		textprintf_ex(dbuf, font, 10, i * 40 + 32 + 15, makecol(255,255,255), -1, "%s", title); 
		rect(dbuf, 0, i * 40 + 32, 200, i * 40 + 39 + 32, 0);
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

		rectfill(dbuf, x, y, x + 206, y + 40, COLOR_SAMPLE_FILE);
		textprintf_ex(dbuf, font, x + 10, y + 15, makecol(255,255,255), -1, "%s", title); 
		rect(dbuf, x, y, x + 206, y + 40, 0);
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
	if(!dbuf)
		dbuf = create_bitmap(1024, 768);
	scare_mouse();
	clear_to_color(dbuf, 0);
	drawDirectories();
	drawSamples();
	blit(dbuf, screen, 0, 0, 0, 0, 1024, 768);
	unscare_mouse();
}


