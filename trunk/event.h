#ifndef INSTIGMATA_EVENTLISTENER_H
#define INSTIGMATA_EVENTLISTENER_H 1

typedef enum eventtype {
	EVENT_SAMPLE_LOAD,
	EVENT_SAMPLE_LOAD_BUTTON,
	EVENT_SAMPLE_TRIGGER,
	EVENT_CHANGE_TRG_COLOR,

	EVENT_CHANGE_VOLUME,
	EVENT_CHANGE_LPF_CUTOFF,
	EVENT_CHANGE_LPF_RESONANCE,
	EVENT_CHANGE_HPF_CUTOFF,
	EVENT_CHANGE_DISTORTION,

	EVENT_CHANGE_LOOP_LENGTH,
	EVENT_CHANGE_LOOP_START
};

class EventListener {
	public:
	virtual void strEvent(eventtype type, char *data) {};
	virtual void emptyEvent(eventtype type) {};
	virtual void intEvent(eventtype type, int data) {};
	virtual void doubleEvent(eventtype type, double data) {};
};
#endif
