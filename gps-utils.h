/* --------------------------------------------------------------------------------
-- SOURCE FILE: gps-utils.c - This is a GPS utility file that houses a function that
--                            reads the GPS information as well as a function that 
--                            checks for errors during runtime.
--
-- PROGRAM:     gps
--
-- FUNCTIONS:   void gps_read_info(struct gps_data_t*)
--              void error_check(struct gps_data_t*)
--
-- DATE:        OCTOBER 13th, 2016
--
-- DESIGNER:    Michael Goll
-- PROGRAMMER:  Michael Goll
--
-- NOTES:
-- 
-------------------------------------------------------------------------------- */

void gps_read_info(struct gps_data_t*);
void error_check(struct gps_data_t*);