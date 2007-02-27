#ifndef INSTIGMATA_EVENTLISTENER_H
#define INSTIGMATA_EVENTLISTENER_H 1

typedef enum eventtype {
	EVENT_SAMPLE_LOAD,
	EVENT_SAMPLE_LOAD_BUTTON,
	EVENT_SAMPLE_TRIGGER,
	EVENT_CHANGE_TRG_COLOR,

	EVENT_CHANGE_VOLUME,
	EVENT_CHANGE_POST_VOLUME,
	EVENT_CHANGE_LPF_CUTOFF,
	EVENT_CHANGE_LPF_RESONANCE,
	EVENT_CHANGE_HPF_CUTOFF,
	EVENT_CHANGE_DISTORTION,

	EVENT_CHANGE_LOOP_LENGTH,
	EVENT_CHANGE_LOOP_START,

	EVENT_PEAKMETER_RIGHT_CHANNEL,
	EVENT_PEAKMETER_LEFT_CHANNEL,

	EVENT_COMPRESSOR_THRESHOLD,
	EVENT_COMPRESSOR_ATTACK,
	EVENT_COMPRESSOR_RELEASE,
	
	EVENT_CHANGE_EQ1_CENTER,
	EVENT_CHANGE_EQ1_GAIN,

	EVENT_TOGGLE_SLICER,
	EVENT_TOGGLE_ECHO,
	EVENT_TOGGLE_REVERB

};

class EventListener {
	public:
	virtual void strEvent(eventtype type, char *data) {};
	virtual void emptyEvent(eventtype type) {};
	virtual void intEvent(eventtype type, int data) {};
	virtual void doubleEvent(eventtype type, double data) {};
	virtual void voidEvent(eventtype type, void *data) {};
	virtual void boolEvent(eventtype type, bool data) {};
};
#endif
