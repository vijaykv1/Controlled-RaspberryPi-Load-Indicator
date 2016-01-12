/*********************************************************************
* File         main.c
* Authors      Priya Chandanshive, Varun Vijaykumar
* Description  main file to initiate all calls
* Date         06 January 2016
**********************************************************************/
# include "SystemLoadInfo.h"

int main(void)
{
    // We write a polling function for continously checking for GPIO 24 & GPIO 25
    wiringPiSetup () ;
    setPinModes();
    pollButtonsAndRun();
    return 0 ;
}
