#include <allegro.h>
#include <stdio.h>
#include <unistd.h>
#include "player.h"
#include "colors.h"
#include "image.h"
#include "loader.h"
#include "soundcore.h"
#include "barcounter.h"
#include "logger.h"
#include "peakmeter.h"

#include <sys/mman.h>
#include <sched.h>

#define NUMBER_PLAYERS 8

Loader *loader = new Loader();
SoundCore *sound = new SoundCore();
Logger *logg = new Logger("error.log");

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

	font = load_font("font.fnt", NULL, NULL);
	
	BITMAP *wsbuffer = create_bitmap(1024, 768);

	Box workspace(0, 0, 1024, 768, COLOR_PLAYER, Box::TYPE_FLAT);

	BarCounter bc(902, 16); 

	workspace.addChild(new Image(0, 0, 32, 768, "left.bmp"));
	workspace.addChild(new Image(992, 0, 32, 768, "right.bmp"));

	workspace.addChild(&bc);
	workspace.addChild(new PeakMeter(907, 50));

	sound->init(162, &bc); // FIXME changing tempo.
	for(int i = 0; i < NUMBER_PLAYERS; i++){
		workspace.addChild(new Player(96 * i, COLOR_PLAYER));
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
	
		bc.paintIfNeeded();
		// Screenshot
		if(key[KEY_F12] && !taking_screenshot){
			taking_screenshot = true;
			save_bitmap("shot.bmp", screen, 0);
		} else if(taking_screenshot){
			taking_screenshot = false;
		}
	

		if(loader->needsDisplay()){
			if(!wsneedsredraw){
				scare_mouse();
				blit(screen, wsbuffer, 0, 0, 0, 0, 1024, 768);
				workspace.paintIfNeeded();
				unscare_mouse();
				loader->paint();
				wsneedsredraw = true;
			}
			if(key[KEY_ESC])
				loader->cancelDisplay();
		} else if(wsneedsredraw) {
			scare_mouse();
			blit(wsbuffer, screen, 0, 0, 0, 0, 1024, 768);
			bc.paint();
			unscare_mouse();
			wsneedsredraw = false;
		} else {
			workspace.paintIfNeeded();
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
	// sound->system->release();
	delete logg;
	set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
	return 0;
}
END_OF_MAIN()
