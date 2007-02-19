#include "logger.h"
#include <time.h>

Logger::Logger(char *logfile) {
	fh = fopen(logfile, "a");
	log("## SESSION STARTED ##");
}

void Logger::log(char *txt) {
	char tme[256];
    time_t t;
    struct tm *tmp;

 	t = time(0);
	tmp = localtime(&t);

	strftime(tme, 256, "%c ", tmp);

	fputs(tme, fh);
	fputs(txt, fh);
	fputc('\n', fh);
}

Logger::~Logger() {
	log("## SESSION CLOSED ##");
	fclose(fh);
}
