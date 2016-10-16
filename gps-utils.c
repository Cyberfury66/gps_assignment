#include <pthread.h>
#include <stdio.h>

/* Threading? */
void init_thread() {
	pthread_t thread;
}

void gps_read_info(struct gps_data_t* gpsdata) {
	
	while(1) {
		if (!gps_waiting(gps_ptr, 50000000)) {
			Cleanup(GPS_TIMEOUT);
		} else {
			errno = 0;

			error_check(gpsdata);

			if (gps_read(gps_ptr) == -1) {
				fprintf(stderr, "sgps: socket error 4\n");
				Cleanup(errno == 0 ? GPS_GONE : GPS_ERROR);
			} else {
				printSat(gpsdata);
			}
		}
	}
}

void error_check(struct gps_data_t* gpsdata) {
	if (gpsdata -> satellites_used == 0) {
		fprintf(stderr, "ERROR: No satellites used.");
	}
}