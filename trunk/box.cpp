/* A box container */
#include "box.h"
#include "soundcore.h"

Box::Box(int x, int y, int w, int h, int color, int type) {
	this->x = x;
	this->y = y;
	this->w = w - 1;
	this->h = h - 1;
	this->color = color;
	this->type = type;
	this->needspaint = false;
}

void Box::addChild(Box *child) {
	// Fix screen offset
	child->fixOffset(x, y);
	children.push_back(child);
}

void Box::fixOffset(int x, int y) {
	this->x += x;
	this->y += y;
	// Fix children offsets
	for(int i = 0; i < children.size(); i++){
		children[i]->fixOffset(x, y);
	}
};

int Box::modifyColorComponent(int q, int con) {
	switch(type){
		case TYPE_BEVEL:
			break;
		case TYPE_GRAVE:
			con = -con;
			break;
		case TYPE_FLAT:
			con = 0;
	}
	
	q = q + con;

	if(q < 0)
		q = 0;
	else if(q  > 255)
		q = 255;
	
	return q;
}

int Box::modifyColor(int col, int con) {
	return makecol(
		modifyColorComponent(getr(col), con), 
		modifyColorComponent(getg(col), con), 
		modifyColorComponent(getb(col), con)
		);
}

void Box::paint() {
	sound->update();
	scare_mouse();
	rectfill(screen, x, y, x+w, y+h, color);
	line(screen, x, y, x+w, y, modifyColor(color, CONTRAST));
	line(screen, x, y, x, y+h, modifyColor(color, CONTRAST));
	line(screen, x, y+h, x+w, y+h, modifyColor(color, -CONTRAST));
	line(screen, x+w, y, x+w, y+h, modifyColor(color, -CONTRAST));
	for(int i = 0; i < children.size(); i++)
		children[i]->paint();
	unscare_mouse();
	sound->update();
}

// Don't override this! Override handleMouseEvent instead
bool Box::mouseEvent(int x, int y, int b) {
	// In my territory?
	if(x > this->x + this->w || x < this->x ||
		   y > this->y + this->h || y < this->y)
		return false; // Nope

	if(handleMouseEvent(x, y, b))
		return true;

	for(int i = 0; i < children.size(); i++){
		if(children[i]->mouseEvent(x, y, b)){
			childHandledMouseEvent(x, y, b, children[i]);
			return true;
		}
	}
	return false;
}

bool Box::dragEvent(int x, int y, int mx, int my){
	if(x > this->x + this->w || x < this->x ||
		   y > this->y + this->h || y < this->y)
		return false; // Nope

	if(handleDragEvent(x, y, mx, my))
		return true;

	for(int i = 0; i < children.size(); i++){
		if(children[i]->dragEvent(x, y, mx, my)){
			childHandledDragEvent(x, y, mx, my, children[i]);
			return true;
		}
	}
	return false;
}

void Box::changeColor(int c){
	this->color = c;
}

void Box::quePaint(){
	needspaint = true;
}

void Box::paintIfNeeded() {
	if(needspaint) {
		paint();
		needspaint = false;
	}
	for(int i = 0; i < children.size(); i++){
		children[i]->paintIfNeeded();
	}
}
