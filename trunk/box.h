#ifndef INSTIGMATA_BOX_H
#define INSTIGMATA_BOX_H 1

#include <allegro.h>
#include <vector>

#define CONTRAST 20

class Box {
	private:

	int modifyColor(int, int);
	int modifyColorComponent(int, int);
	bool needspaint;

	protected:

	std::vector<Box *> children;

	int type;
	int x;
	int y;
	int w;
	int h;
	int color;
	virtual bool handleMouseEvent(int x, int y, int b) { return false; }
	virtual bool handleDragEvent(int x, int y, int mx, int my) { return false; }
	virtual void childHandledMouseEvent(int x, int y, int b, Box *child) { return; }
	virtual void childHandledDragEvent(int x, int y, int mx, int my, Box *child) { return; }

	public:

	typedef enum BoxType {
		TYPE_BEVEL,
		TYPE_GRAVE,
		TYPE_FLAT
	};

	Box(int x, int y, int w, int h, int color, int type);

	void addChild(Box *child);
	
	virtual void paint();
	
	void quePaint();
	void paintIfNeeded();

	bool mouseEvent(int x, int y, int b);
	bool dragEvent(int x, int y, int mx, int my);

	void fixOffset(int x, int y);
	
	void changeColor(int c);
};

#endif /* INSTIGMATA_BOX_H */
