#include "image.h"
#include "colors.h"
#include "looper.h"


Image::Image(int x, int y, int w, int h, char *img) 
	: Box(x, y, w, h, color, Box::TYPE_FLAT)
{
	image = load_bitmap(img, NULL);
}

void Image::paint(){
	blit(image, screen, 0, 0, x, y, w + 1, h + 1);
}


