###########################################################################
#Description  Makefile to create a Gertboard Application in RaspberryPI
#Authors      Priya Chandanshive , Varun Vijaykumar
#Date         24 Nov 2015
###########################################################################
RaspCC = arm-linux-gnueabihf-gcc
SOURCES=./src/main.c ./src/SystemLoadInfo.c
LDIR = -L ./Thirdparty/wiringPi/lib
IDIR = -I ./Thirdparty/wiringPi/include -I ./include
CFLAGS = $(IDIR) $(LDIR) -l wiringPi -l wiringPiDev -o
BIN = cpuload

$(BIN) : $(SOURCES)
	$(RaspCC) $^ $(CFLAGS) $@

clean:
	rm -vrf $(BIN)
