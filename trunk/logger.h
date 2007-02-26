#ifndef INSTIGMATA_LOGGER_H
#define INSTIGMATA_LOGGER_H 1

#include <stdio.h>

class Logger {
	private:
	FILE *fh;
	public:
	Logger(char *logfile);
	void log(char *txt);
	~Logger();
};

extern Logger *logg; 

#define LOG(msg) logg->log(msg)

#endif
