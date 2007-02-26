#include "player.h"
#include "colors.h"
#include "looper.h"
#include "soundcore.h"
#include "slider.h"
#include "dualslider.h"

Player::Player(int y, int color) 
	: Box(32, y, 850, 96, color, Box::TYPE_BEVEL)
{
	player = (SoundPlayer *)sound->registerPlayer(this);
	for(int i = 0; i < 4; i++){
		addChild(new Looper(3 + i * (150 + 3), COLOR_DEFAULT_BUTTON, player));
	}
	int fxpos = 615;
	#define addFX(a) addChild(a); fxpos += 33;

	addFX(new DualSlider(fxpos, "LPF", EVENT_CHANGE_LPF_CUTOFF, EVENT_CHANGE_LPF_RESONANCE, this, 
			PLAYER_LPF_DEFAULT_CUTOFF, PLAYER_LPF_DEFAULT_RESONANCE, 0.01, 0.01, true, true));
	addFX(new Slider(fxpos, "HPF", EVENT_CHANGE_HPF_CUTOFF, this, PLAYER_HPF_DEFAULT_CUTOFF, 0.01, SLIDER_LOGARITHMIC));
	addFX(new Slider(fxpos, "DST", EVENT_CHANGE_DISTORTION, this, PLAYER_DEFAULT_DISTORTION, 0.01, SLIDER_ANTILOGARITHMIC));
	addFX(new Slider(fxpos, "Vol", EVENT_CHANGE_VOLUME, this, PLAYER_DEFAULT_VOLUME, 0.01, SLIDER_LOGARITHMIC));
}

void Player::doubleEvent(eventtype et, double data) {
	player->doubleEvent(et, data); // Pass to soundplayer
}

