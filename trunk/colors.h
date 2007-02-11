#ifndef INSTIGMATA_COLORS_H
#define INSTIGMATA_COLORS_H
#include <allegro.h>

#define COLOR_PLAYER makecol(61, 23, 104)
#define COLOR_DEFAULT_BUTTON makecol(71, 33, 114)
#define COLOR_DEFAULT_BUTTON_DOWN makecol(51, 24, 94)
#define COLOR_SAMPLE_FILE makecol(100, 100, 100)
#define COLOR_DEFAULT_DIRECTORY COLOR_DEFAULT_BUTTON
#define COLOR_SELECTED_DIRECTORY makecol(150, 50, 50)
#define COLOR_DEFAULT_BUTTONTEXT makecol(255,255,255)
#define COLOR_DEFAULT_BUTTONTEXT_SHADOW makecol(0,0,0)

#define COLOR_SLIDER	makecol(0, 255, 0)
#define COLOR_SLIDER2   makecol(0, 0, 255)

// Trigger colors
#define COLOR_TRG_NOTLOADED makecol(50, 50, 50)
#define COLOR_TRG_IDLE      makecol(100, 100, 100)
#define COLOR_TRG_QUEUED    makecol(255, 255, 0)
#define COLOR_TRG_PLAYING   makecol(0, 255, 0)
#define COLOR_TRG_STOPPING  makecol(255, 0, 0)

// Barcounter
#define COLOR_BAR_PASSED    makecol(255, 0, 0)
#define COLOR_BAR_DUE       makecol(155, 0, 0)

#endif
