#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <gps.h>
#include "gpsadd.h"

#define MAXCHANNELS   72
#define MAX_POSSIBLE_SATS (MAXCHANNELS - 2)

bool usedflags[MAXCHANNELS];
static enum deg_str_type deg_type = deg_dd;

struct gps_data_t *gpsdata;

int used(bool usedflags){
	if (usedflags)
		return 'Y';
	else
		return 'N';
}

void printSat(struct gps_data_t *gpsdata) {

	for (int i = 0; i < MAXCHANNELS; i++) {
		
		usedflags[i] = false;
		for (int j = 0; j < gpsdata->satellites_used; j++)
			if (gpsdata->used[j] == gpsdata->PRN[i])
				usedflags[i] = true;
		
	}

	if (gpsdata->satellites_visible != 0) {
		
		for (int i = 0; i < MAX_POSSIBLE_SATS; i++) {
			if (i < gpsdata->satellites_visible) {
				fprintf(stdout,"PRN:%03d  Elevation:%02d  Azimuth:%03d  SNR:%02f  Used:%c\n",
				gpsdata->PRN[i],
				gpsdata->elevation[i],
				gpsdata->azimuth[i],
				gpsdata->ss[i],
				used(usedflags[i])
				);
			}
		}
		
	}

	if (gpsdata->fix.mode >= MODE_2D && isnan(gpsdata->fix.latitude)==0) {
		fprintf(stdout, "Latitude: %s %c;", deg_to_str(deg_type, fabs(gpsdata->fix.latitude)),
		(gpsdata->fix.latitude < 0) ? 'S' : 'N');
		fflush(stdout);
		
	}
	else 
		printf("N/A");

	if (gpsdata->fix.mode >= MODE_2D && isnan(gpsdata->fix.longitude)==0) {
		fprintf(stdout, "Longitude: %s %c;", deg_to_str(deg_type, fabs(gpsdata->fix.longitude)),
		(gpsdata->fix.longitude < 0) ? 'W' : 'E');
		fflush(stdout);
		
	}
	else 
		printf("N/A\n");
}