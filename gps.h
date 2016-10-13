#ifndef GPS_H
#define GPS_H

typedef struct fixsource_t {
	char *spec;
	char *server;
	char *port;
	char *device;
};

#endif