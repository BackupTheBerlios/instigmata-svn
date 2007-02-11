#include <allegro.h>
#include <stdio.h>
#include <unistd.h>
#include "player.h"
#include "colors.h"
#include "image.h"
#include "loader.h"
#include "soundcore.h"
#include "barcounter.h"

#include <sys/mman.h>
#include <sched.h>

#define NUMBER_PLAYERS 7

Loader *loader = new Loader();
SoundCore *sound = new SoundCore();

int main(int argc, char *argv[]) {
	
	struct sched_param scp;

	scp.sched_priority = 70;

	sched_setscheduler(0, SCHED_FIFO, &scp);
	mlockall(MCL_FUTURE);

	allegro_init();
	set_color_depth(24);
	set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 1024, 768, 0, 0);
	install_keyboard();
	install_mouse();
	
	Box workspace(0, 0, 1024, 768, COLOR_PLAYER, Box::TYPE_FLAT);

	BarCounter bc(900, 16); 

	workspace.addChild(new Image(0, 0, 1024, 32, "header.bmp"));
	workspace.addChild(&bc);

	sound->init(162, &bc); // FIXME changing tempo.
	for(int i = 0; i < NUMBER_PLAYERS; i++){
		workspace.addChild(new Player(96 * i + 32, COLOR_PLAYER));
		sound->update();
	}

	workspace.paint();

	show_mouse(screen);

	bool mbdown = false;
	bool wsneedsredraw = false;

	int dragstart_x = 0;
	int dragstart_y = 0;

	int mickey_x = 0;
	int mickey_y = 0;

	bool taking_screenshot = false;

	while(!(key[KEY_LSHIFT] && key[KEY_LCONTROL] && key[KEY_ESC])){
		sound->update();
		workspace.paintIfNeeded();
		bc.paintIfNeeded();
		// Screenshot
		if(key[KEY_F12] && !taking_screenshot){
			taking_screenshot = true;
			save_bitmap("shot.bmp", screen, 0);
		} else if(taking_screenshot){
			taking_screenshot = false;
		}
	

		if(loader->needsDisplay()){
			wsneedsredraw = true;
			if(key[KEY_ESC])
				loader->cancelDisplay();
		} else if(wsneedsredraw) {
			workspace.paint();
			wsneedsredraw = false;
		}
		
		if((mouse_b) && !mbdown) {
			if(loader->needsDisplay()) {
				loader->mouseEvent(mouse_x, mouse_y, mouse_b);
			} else {
				workspace.mouseEvent(mouse_x, mouse_y, mouse_b);
			}
			mbdown = true;
			dragstart_x = mouse_x;
			dragstart_y = mouse_y;
			show_mouse(0);
			get_mouse_mickeys(&mickey_x, &mickey_y);
		} else if (!mouse_b && mbdown) {
			mbdown = false;
			position_mouse(dragstart_x, dragstart_y);
			show_mouse(screen);
		} else if (mbdown) {
			// Trigger drag events
			get_mouse_mickeys(&mickey_x, &mickey_y);
			if(!loader->needsDisplay()){
				if(mickey_x != 0 || mickey_y != 0)
					workspace.dragEvent(dragstart_x, dragstart_y, mickey_x, mickey_y);
			}
		}
		usleep(100);
	}
	sound->system->release();
	set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
	return 0;
}
END_OF_MAIN()
