CC=gcc -Wall
CLIB=-lgps

dcgps: dcgps.o gps-utils.o gpsprint.c
	$(CC) -o dcgps dcgps.o gps-utils.o gpsprint.o gpsgfx.o $(CLIB)

clean:
	rm -f *.o core.* dcgps

gps-utils.o:
	$(CC) -c gps-utils.c

gpsprint.o:
	$(CC) -c gpsprint.c

dcgps.o:
	$(CC) -c dcgps.c

gpsgfc.o:
	$(CC) -c gpsgfc.c


