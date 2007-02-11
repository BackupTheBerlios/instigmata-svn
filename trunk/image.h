#ifndef INSTIGMATA_IMAGE_H
#define INSTIGMATA_IMAGE_H 1
#include "box.h"

class Image : public Box {
	private:
	BITMAP *image;
	public:
	Image(int x, int y, int w, int h, char *image);
	void paint();
};

#endif /* INSTIGMATA_IMAGE_H */
