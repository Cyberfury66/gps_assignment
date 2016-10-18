/* -----------------------------------------------------------------------------------------------------
-- SOURCE FILE: gps-utils.c - A utility file for the dcgps program. It handles reading of information
--                            and error detection.
--
-- PROGRAM: dcgps
--
-- FUNCTIONS:
--      void gps_read_info(struct gps_data_t*)
--      void error_check(int)
-- 
-- DATE: October 12, 2016
-- 
-- DESIGNER:   Michael Goll
--
-- PROGRAMMER: Michael Goll
-- 
-- NOTES:
-- This file features two functions that are involved with the checking of errors during run-time and
-- the handing of valid data to the print function.
--
------------------------------------------------------------------------------------------------------ */

#include <stdio.h>
#include <errno.h>
#include <gps.h>
#include "gpsadd.h"

void printSat(struct gps_data_t*);
void error_check(int n);
void gps_read_info(struct gps_data_t* gpsdata);


/* ------------------------------------------------------------------------------------------------------
-- FUNCTION: gps_read_info
--
-- DATE: October 12, 2016
--
-- DESIGNER:   Michael Goll
--
-- PROGRAMMER: Michael Goll
--
-- RETURNS: void
--
-- PARAMETERS: struct gps_data_t*
--
-- NOTES:
-- This starts an infinite loop that receives data from the GPS dongle and checks for errors. If no errors
-- are detected, then the data is passed to the printSat() function.
------------------------------------------------------------------------------------------------------- */
void gps_read_info(struct gps_data_t* gpsdata) {
	
	while(1) {
		if (!gps_waiting(gpsdata, 50000000)) {
			error_check(GPS_TIMEOUT);
			break;
		} else {
			errno = 0;

			if (gps_read(gpsdata) == -1) {
				fprintf(stderr, "agps:socket error 4\n");
				error_check(errno == 0 ? GPS_GONE : GPS_ERROR);
			} else {
				printSat(gpsdata);
			}
		}
	}
}

/* ------------------------------------------------------------------------------------------------------
-- FUNCTION: error_check
--
-- DATE: October 12, 2016
--
-- DESIGNER:   Michael Goll
--
-- PROGRAMMER: Michael Goll
--
-- RETURNS: void
--
-- PARAMETERS: int message
--
-- NOTES:
-- This handles errors that are handed to it from gps_read_info. It prints out an error message that 
-- corresponds with the error that was detected.
------------------------------------------------------------------------------------------------------- */



void error_check(int message) {
    switch(message) {
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
 
}
