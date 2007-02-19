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

extern Logger *log; 

#define LOG(msg) log->log(msg)

#endif
