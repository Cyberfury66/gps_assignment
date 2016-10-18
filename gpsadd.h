#ifndef GPSADD_H
#define GPSADD_H

#define LOCAL_HOST  "127.0.0.1"
#define DEFAULT_PORT "2947"
#define GPS_TIMEOUT -1
#define GPS_EXIT    -2
#define GPS_GONE    -3
#define GPS_ERROR   -4
#define MAXCHANNELS 72
#define MAX_POSSIBLE_SATS (MAXCHANNELS - 2) 

typedef struct fixsource_t {
	char *spec;
	char *server;
	char *port;
	char *device;
}fixsource;

#endif
