#include <stdio.h>
#include <errno.h>
#include <gps.h>

void printSat(struct gps_data_t*);

void gps_read_info(struct gps_data_t* gpsdata) {
	
	while(1) {
		if (!gps_waiting(gpsdata, 50000000)) {
			error_check(GPS_TIMEOUT);
		} else {
			errno = 0;

			error_check(gpsdata);

			if (gps_read(gpsdata) == -1) {
				fprintf(stderr, "agps:socket error 4\n");
				error_check(errno == 0 ? GPS_GONE : GPS_ERROR);
			} else {
				printSat(gpsdata);
			}
		}
	}
}

void error_check(int n) {
    switch(n) {
        case GPS_EXIT:
            break;
        case GPS_TIMEOUT:
            printf("%s", "GPS timed out\n");
            break;
        case GPS_ERROR:
            printf("%s", "Read error");
            break;
        case GPS_GONE:
            printf("%s", "GPS lost");
            break;
    }
    refresh();
}
