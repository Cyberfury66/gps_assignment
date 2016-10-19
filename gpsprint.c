/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: gpsprint.c - contains the print function to print the satellite information.
--
-- PROGRAM: dcgps
--
-- FUNCTIONS:
-- void printSat(struct gps_data_t *gpsdata)
-- void utcTime(struct gps_data_t *gpsdata)
--
-- DATE: October 19, 2016
--
-- DESIGNER: Yi Hsiang (Mark) Chen
--
-- PROGRAMMER: Yi Hsiang (Mark) Chen, Michael Goll
--
-- NOTES:
-- This contains the function to print following information about each satellite:
-- - Timestamp (UTC)
-- - PRN
-- - Elevation
-- - Azimuth
-- - SNR 
-- - Whether or not it is used
-- The additional function utcTime is used to convert the GPS timestamp to UTC time.
-- As well, the function will also print out the latitude and longitude of the device.
----------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <errno.h>
#include <math.h>
#include <gps.h>
#include <time.h>
#include "gpsadd.h"
#include "gpsdclient.h"

bool usedflags[MAXCHANNELS];
struct gps_data_t *gpsdata;
char *deg_to_str(enum deg_str_type type, double f); 
void utcTime(struct gps_data_t *gpsdata);

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: printSat
--
-- DATE: October 19, 2016
--
-- DESIGNER: Yi Hsiang (Mark) Chen
--
-- PROGRAMMER: Yi Hsiang (Mark) Chen, Michael Goll
--
-- INTERFACE: printSat(struct gps_data_t *gpsdata)
--
-- RETURNS: void.
--
-- NOTES:
-- This contains the function to print following information about each satellite:
-- - Timestamp (UTC)
-- - PRN
-- - Elevation
-- - Azimuth
-- - SNR 
-- - Whether or not it is used
-- As well, the function will also print out the latitude and longitude of the device.
----------------------------------------------------------------------------------------------------------------------*/

void printSat(struct gps_data_t *gpsdata) {
	static enum deg_str_type deg_type = deg_dd;
	int i, j;
	
	for (i = 0; i < satellites_visible; i++) {
		usedflags[i] = false;
		for (j = 0; j < gpsdata->satellites_used; j++)
			if (gpsdata->used[j] == gpsdata->PRN[i])
				usedflags[i] = true;
	}

	if (gpsdata->satellites_visible != 0) {
		for (i = 0; i < gpsdata->satellites_visible; i++) {
			fprintf(stdout,"\nPRN:%03d | Elevation:%02d | Azimuth:%03d | SNR:%02f | Used:%c\n",
			gpsdata->PRN[i],
			gpsdata->elevation[i],
			gpsdata->azimuth[i],
			gpsdata->ss[i],
			(usedflags[i]) ? 'Y' : 'N'
			);
		}
	}

	void utcTime(gpsdata);
	
	if (gpsdata->fix.mode >= MODE_2D && isnan(gpsdata->fix.latitude)==0) {
		fprintf(stdout, "\nLatitude: %s %c;", deg_to_str(deg_type, fabs(gpsdata->fix.latitude)),
		(gpsdata->fix.latitude < 0) ? 'S' : 'N');
		fflush(stdout);
	}
	else 
		printf("N/A (Latitude not found)\n");

	if (gpsdata->fix.mode >= MODE_2D && isnan(gpsdata->fix.longitude)==0) {
		fprintf(stdout, "\nLongitude: %s %c;", deg_to_str(deg_type, fabs(gpsdata->fix.longitude)),
		(gpsdata->fix.longitude < 0) ? 'W' : 'E');
		fflush(stdout);
	}
	else 
		printf("N/A (Longitude not found)\n");
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: utcTime
--
-- DATE: October 19, 2016
--
-- DESIGNER: Yi Hsiang (Mark) Chen
--
-- PROGRAMMER: Yi Hsiang (Mark) Chen
--
-- INTERFACE: utcTime(struct gps_data_t *gpsdata)
--
-- RETURNS: void.
--
-- NOTES:
-- This function converts the timestamp from the GPS to UTC time.
----------------------------------------------------------------------------------------------------------------------*/

void utcTime(struct gps_data_t *gpsdata){
	
	time_t gpsTime;
	struct tm *utcTime;
	
	if (gpsdata->fix.mode >= MODE_2D && isnan(gpsdata->fix.time)==0) {
		gpsTime = (time_t)gpsTime->fix.time;
		
		utcTime = gmtime(&gpsTime);
		
		fprintf(stdout, "\nTimestamp : %4d-%02d-%2d %2d:%2d:%02d"", (utcTime->tm_year) + 1900, 
		(utcTime->tm_mon), (utcTime->tm_mday),(utcTime->tm_hour)%24, (utcTime->tm_min), (utcTime->tm_sec))
		}
	else 
		printf("N/A (Timestamp not available)\n");
}
