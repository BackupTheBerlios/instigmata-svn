#ifndef INSTIGMATA_PLAYER_H
#define INSTIGMATA_PLAYER_H 1
#include "box.h"
#include "event.h"
#include "soundplayer.h"

class Player : public Box, public EventListener {
	private:
	SoundPlayer *player;

	public:
	Player(int y, int c);
	void doubleEvent(eventtype et, double data);
};

#endif /* INSTIGMATA_PLAYER_H */
