#include <math.h>
#include "logconv.h"

double logToLin(double v) {
	v = 1 - v; // Reverse
	v = pow(10, v); // Power
	v = (v - 1) / 9.0; // Scale
	v = 1 - v; // Reverse again
	return v;
}

double antiLogToLin(double v) {
	v = pow(10, v); // Power
	v = (v - 1) / 9.0; // Scale
	return v;
}

double linToLog(double v) {
	return 1 - log10((1 - v) * 9.0 + 1.0);
}

double linToAntiLog(double v) {
	return log10(v * 9.0 + 1.0);
}
