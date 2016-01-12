/*********************************************************************
* File         SystemLoadInfo.h
* Authors      Priya Chandanshive, Varun Vijaykumar
* Description  To calculate and display system load of the system and switch
*              between fast and slow mode.
* Date         06 January 2016
**********************************************************************/
#ifndef __SYS_LOAD_INFO_H__
#define __SYS_LOAD_INFO_H__

#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <wiringPi.h>

#define PROC_STAT_LINE 512

// Read modes for file
#define FAST_MODE 2
# define NORMAL_MODE 3

// Enable for debug
//#define LOAD_READ_DEBUG

struct cpuInfo
{
    unsigned long long int user_time;
    unsigned long long int nice_time;
    unsigned long long int system_time;
    unsigned long long int idle_time;
    unsigned long long int iowait_time;
    unsigned long long int irq_time;
    unsigned long long int softirq_time;
    unsigned long long int steal_time;
    unsigned long long int guest_time;
    unsigned long long int guest_nice_time;
};

struct cpuInfo previousCPUStat;

bool highRate;

// methods

///////////////////////////////////////////////////////////////////////////////
// function to yank out data from /proc/stat file periodically.
///////////////////////////////////////////////////////////////////////////////
bool readProcFile(FILE *procFile, struct cpuInfo *cpuStat);

///////////////////////////////////////////////////////////////////////////////
// function to calculate system load from the details obtained.
///////////////////////////////////////////////////////////////////////////////
double calculateSystemLoad(struct cpuInfo *previousCPUStat,
                           struct cpuInfo *presentCPUStat);

///////////////////////////////////////////////////////////////////////////////
// function to poll the GPO 24 and 25 buttons
///////////////////////////////////////////////////////////////////////////////
void pollButtonsAndRun();

///////////////////////////////////////////////////////////////////////////////
// function to set all the wiringPi Pin Modes to OUTPUT
///////////////////////////////////////////////////////////////////////////////
void setPinModes();

///////////////////////////////////////////////////////////////////////////////
// function to Display percentage on Gertboard.
///////////////////////////////////////////////////////////////////////////////
void displayCPUpercentage(int systemLoad);

///////////////////////////////////////////////////////////////////////////////
// function to perform the overall procedure. Interface to main.
///////////////////////////////////////////////////////////////////////////////
void getandDisplayCPUpercentage(int mode);

#endif /*__SYS_LOAD_INFO_H__*/
