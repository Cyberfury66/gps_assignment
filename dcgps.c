/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: dcgps.c - A simple console gps program that includes images of coordinates of user on a basic map that 
-- is created using ascii characters.
--
-- PROGRAM: dcgps
--
-- FUNCTIONS:
-- int main();
--
-- DATE: October 19th, 2016
--
-- DESIGNER: Yi Hsiang (Mark) Chen
--
-- PROGRAMMER: Yi Hsiang (Mark) Chen, Michael Goll
--
-- NOTES:
-- A gps application that returns information about satellites that contribute to triangulation.
-- The information about the satellites includes their longitude, latitude, its PRN, elevation, azimuth, SNR, and a used
-- flag.
----------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <gps.h>
#include "gpsadd.h"
#include "gpsdclient.h"

void gps_read_info(struct gps_data_t* gpsdata);

static struct gps_data_t *gpsdata;
static struct fixsource_t source;

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: main
--
-- DATE: October 19th, 2016
--
-- DESIGNER: Yi Hsiang (Mark) Chen
--
-- PROGRAMMER: Yi Hsiang (Mark) Chen, Michael Goll
--
-- RETURNS: int.
--
-- NOTES:
-- This guns mallocs the appropriate memory for the gps_data_t structure that will contain information about the satellites,
-- open the stream to gpsd, and start the stream.
----------------------------------------------------------------------------------------------------------------------*/

int main() {
	
	unsigned int flags = WATCH_ENABLE;

	source.server = LOCAL_HOST;
	source.port   = DEFAULT_PORT;
	
	gpsdata = malloc(sizeof(struct gps_data_t));
	
	/* Checking for errors on opening gps */
	if (gps_open(source.server, source.port, gpsdata) != 0) {
		fprintf(stderr, "An error has occurred: %d %s\n", errno, gps_errstr(errno));
	}
	
	if (source.device != NULL) {
		flags |= WATCH_DEVICE;
	}
	
	/* Opening the GPS stream */
	if (gps_stream(gpsdata, flags, source.device) != 0) {
	    fprintf(stderr, "GPSD not running: %d, %s\n", errno, gps_errstr(errno));
        return -1;
    }
	
	
	/* Reads the GPS data and checks for errors. */
	gps_read_info(gpsdata);
	
	/* Disabling the WATCH as well as closing the gps stream, ending the session. */
	gps_stream(gpsdata, WATCH_DISABLE, NULL);
	free(gpsdata);
	(void)gps_close(gpsdata);
        return 0;
}
