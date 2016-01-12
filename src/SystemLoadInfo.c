/*********************************************************************
* File         SystemLoadInfo.c
* Authors      Priya Chandanshive, Varun Vijaykumar
* Description  To calculate and display system load of the system
* Date         06 January 2016
**********************************************************************/

#include "SystemLoadInfo.h"

bool readProcFile(FILE *procFile,struct cpuInfo *cpuStat)
{
    char proc_data[PROC_STAT_LINE+1]; // Read buffer .. flush evry call ! !

    // push the values to the buffer that we have declared !
    if (fgets (proc_data, PROC_STAT_LINE, procFile) != NULL)
    {

 #ifdef LOAD_READ_DEBUG
        printf("SUCCESS reading from file \n");
        puts(proc_data);
 #endif
    }
    else
    {
        printf("Reading from the file failed ! Setting return as failure !\n");
        return false;
    }

    // lets yank data from the first line alone and push it to the Structure
    int retval = sscanf(proc_data,
                        "cpu  %Lu %Lu %Lu %Lu %Lu %Lu %Lu %Lu %Lu %Lu",
                        &cpuStat->user_time,
                        &cpuStat->nice_time,
                        &cpuStat->system_time,
                        &cpuStat->idle_time,
                        &cpuStat->iowait_time,
                        &cpuStat->irq_time,
                        &cpuStat->softirq_time,
                        &cpuStat->steal_time,
                        &cpuStat->guest_time,
                        &cpuStat->guest_nice_time);

    if (retval < 4)
    {
        printf("We need atleast 4 fields ! \n");
        return false;
    }

    return true;
}

double calculateSystemLoad(struct cpuInfo *previousCPUStat,
                           struct cpuInfo *presentCPUStat)
{
    // Total times
    unsigned long long int previoustotal_time =previousCPUStat->user_time+
                                               previousCPUStat->nice_time+
                                               previousCPUStat->system_time+
                                               previousCPUStat->idle_time+
                                               previousCPUStat->iowait_time+
                                               previousCPUStat->irq_time+
                                               previousCPUStat->softirq_time+
                                               previousCPUStat->steal_time+
                                               previousCPUStat->guest_time+
                                               previousCPUStat->guest_nice_time;

    unsigned long long int presenttotal_time =presentCPUStat->user_time+
                                              presentCPUStat->nice_time+
                                              presentCPUStat->system_time+
                                              presentCPUStat->idle_time+
                                              presentCPUStat->iowait_time+
                                              presentCPUStat->irq_time+
                                              presentCPUStat->softirq_time+
                                              presentCPUStat->steal_time+
                                              presentCPUStat->guest_time+
                                              presentCPUStat->guest_nice_time;

    // We got total time calculation from BOOT , we need specific total time
    unsigned long long int totalDiff = presenttotal_time - previoustotal_time;
    unsigned long long int idleDiff  = (presentCPUStat->idle_time + presentCPUStat->iowait_time) -
                                       (previousCPUStat->idle_time + previousCPUStat->iowait_time);

    // percentage calculation
    double systemLoad = ((totalDiff -idleDiff)/(double) totalDiff) * 100;

    return systemLoad;
}

void setPinModes()
{
    pinMode(8,OUTPUT);  //Raspberry GPIO 2  GP 0
    pinMode(9,OUTPUT);  //Raspberry GPIO 3  GP 1
    pinMode(7,OUTPUT);  //Raspberry GPIO 4  GP 4
    pinMode(11,OUTPUT); //Raspberry GPIO 7  GP 7
    pinMode(10,OUTPUT); //Raspberry GPIO 8  GP 8
    pinMode(13,OUTPUT); //Raspberry GPIO 9  GP 9
    pinMode(12,OUTPUT); //Raspberry GPIO 10 GP 10
    pinMode(14,OUTPUT); //Raspberry GPIO 11 GP 11
    pinMode(15,OUTPUT); //Raspberry GPIO 14 GP 14
    pinMode(16,OUTPUT); //Raspberry GPIO 15 GP 15

    // Input pins
    pinMode(5,INPUT); // Raspberry GPIO 24 GP 24
    pullUpDnControl(5,PUD_UP); // Set as pull up
    pinMode(6,INPUT); // Raspberry GPIO 25 GP 25
    pullUpDnControl(6,PUD_UP); // Set as pull up
}

void displayCPUpercentage(int systemLoad)
{
    if ((systemLoad > 0) && (systemLoad < 9))
    {
        // NO LED  .. switch all off
        digitalWrite(8,LOW);
        digitalWrite(9,LOW);
        digitalWrite(7,LOW);
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(13,LOW);
        digitalWrite(12,LOW);
        digitalWrite(14,LOW);
        digitalWrite(15,LOW);
        digitalWrite(16,LOW);
    }
    else if ((systemLoad >= 10) && (systemLoad < 20))
    {
        // Only one LED
        digitalWrite(8,LOW);
        digitalWrite(8,LOW);
        digitalWrite(9,LOW);
        digitalWrite(7,LOW);
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(13,LOW);
        digitalWrite(12,LOW);
        digitalWrite(14,LOW);
        digitalWrite(15,LOW);
        digitalWrite(16,HIGH);

    }
    else if ((systemLoad >= 20) && (systemLoad < 30))
    {
        digitalWrite(8,LOW);
        digitalWrite(9,LOW);
        digitalWrite(7,LOW);
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(13,LOW);
        digitalWrite(12,LOW);
        digitalWrite(14,LOW);
        digitalWrite(15,HIGH);
        digitalWrite(16,HIGH);

    }
    else if ((systemLoad >= 30) && (systemLoad < 40))
    {
        digitalWrite(8,LOW);
        digitalWrite(9,LOW);
        digitalWrite(7,LOW);
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(13,LOW);
        digitalWrite(12,LOW);
        digitalWrite(14,HIGH);
        digitalWrite(15,HIGH);
        digitalWrite(16,HIGH);

    }
    else if ((systemLoad >= 40) && (systemLoad < 50))
    {
        digitalWrite(8,LOW);
        digitalWrite(9,LOW);
        digitalWrite(7,LOW);
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(13,LOW);
        digitalWrite(12,HIGH);
        digitalWrite(14,HIGH);
        digitalWrite(15,HIGH);
        digitalWrite(16,HIGH);
    }
    else if ((systemLoad >= 50) && (systemLoad < 60))
    {
        digitalWrite(8,LOW);
        digitalWrite(9,LOW);
        digitalWrite(7,LOW);
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(13,HIGH);
        digitalWrite(12,HIGH);
        digitalWrite(14,HIGH);
        digitalWrite(15,HIGH);
        digitalWrite(16,HIGH);

    }
    else if ((systemLoad >= 60) && (systemLoad < 70))
    {
        digitalWrite(8,LOW);
        digitalWrite(9,LOW);
        digitalWrite(7,LOW);
        digitalWrite(11,LOW);
        digitalWrite(10,HIGH);
        digitalWrite(13,HIGH);
        digitalWrite(12,HIGH);
        digitalWrite(14,HIGH);
        digitalWrite(15,HIGH);
        digitalWrite(16,HIGH);

    }
    else if ((systemLoad >= 70) && (systemLoad < 80))
    {
        digitalWrite(8,LOW);
        digitalWrite(9,LOW);
        digitalWrite(7,LOW);
        digitalWrite(11,HIGH);
        digitalWrite(10,HIGH);
        digitalWrite(13,HIGH);
        digitalWrite(12,HIGH);
        digitalWrite(14,HIGH);
        digitalWrite(15,HIGH);
        digitalWrite(16,HIGH);

    }
    else if ((systemLoad >= 80) && (systemLoad < 90))
    {
        digitalWrite(8,LOW);
        digitalWrite(9,LOW);
        digitalWrite(7,HIGH);
        digitalWrite(11,HIGH);
        digitalWrite(10,HIGH);
        digitalWrite(13,HIGH);
        digitalWrite(12,HIGH);
        digitalWrite(14,HIGH);
        digitalWrite(15,HIGH);
        digitalWrite(16,HIGH);
    }
    else if ((systemLoad >= 90) && (systemLoad < 100))
    {
        digitalWrite(8,LOW);
        digitalWrite(9,HIGH);
        digitalWrite(7,HIGH);
        digitalWrite(11,HIGH);
        digitalWrite(10,HIGH);
        digitalWrite(13,HIGH);
        digitalWrite(12,HIGH);
        digitalWrite(14,HIGH);
        digitalWrite(15,HIGH);
        digitalWrite(16,HIGH);
    }
    else if (systemLoad == 100)
    {
        // All Lit !
        digitalWrite(8,HIGH);
        digitalWrite(9,HIGH);
        digitalWrite(7,HIGH);
        digitalWrite(11,HIGH);
        digitalWrite(10,HIGH);
        digitalWrite(13,HIGH);
        digitalWrite(12,HIGH);
        digitalWrite(14,HIGH);
        digitalWrite(15,HIGH);
        digitalWrite(16,HIGH);
    }
    else
    {
        // for 0
        digitalWrite(8,LOW);
        digitalWrite(9,LOW);
        digitalWrite(7,LOW);
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(13,LOW);
        digitalWrite(12,LOW);
        digitalWrite(14,LOW);
        digitalWrite(15,LOW);
        digitalWrite(16,LOW);
    }
}

void pollButtonsAndRun(void)
{
    while(1)
    {
        printf("In while loop ... running \n");

        if ((digitalRead(5) == LOW) && (digitalRead(6) == HIGH))
        {
	  printf("24 has been pressed ! \n ");
	  if (!highRate)
	  {
	    highRate = true;
	  }
        }
        else if ((digitalRead(6) == LOW) && (digitalRead(5) == HIGH))
        {
	  printf("25 has been pressed ! \n ");
	  if (highRate)
	  {
	    highRate = false; // Normal read
	  }
        }

        if (highRate)
	{
	  getandDisplayCPUpercentage(FAST_MODE);
	}
	else
	{
	  getandDisplayCPUpercentage(NORMAL_MODE);
	}
    }
}

void getandDisplayCPUpercentage(int mode)
{
    struct cpuInfo nowCPUStat;
    double loadPercentage;

    FILE *procFile = fopen("/proc/stat","r");
    if (!procFile)
    {
        perror("fopen failed procFile");
        exit(1);
    }

    bool firstReadStatus = readProcFile(procFile,&nowCPUStat);
    if (!firstReadStatus)
    {
        printf("First read of /proc/stat failed ! \n" );
        exit(1);
    }

 #ifdef LOAD_READ_DEBUG
        printf(" --- Structure obtained in for previous cpuStat is -----\n");
        printf("usertime:%llu \n",previousCPUStat.user_time);
        printf("nicetime:%llu \n",previousCPUStat.nice_time);
        printf("system_time:%llu \n",previousCPUStat.system_time);
        printf("idle_time:%llu \n",previousCPUStat.idle_time);
        printf("------------------------------------------ \n" );
 #endif

    previousCPUStat = nowCPUStat;

    if (mode == FAST_MODE)
    {
        usleep(20000);
    }
    else
    {
        sleep(1);
    }

    fseek(procFile,0,SEEK_SET);
    fflush(procFile);

    bool readFileStatus = readProcFile(procFile,&nowCPUStat);
    if (!readFileStatus)
    {
        printf("File read failed !! \n");
    }

 #if LOAD_READ_DEBUG
    printf(" --- Structure obtained in for now cpuStat is -----\n");
    printf("usertime:%llu \n",previousCPUStat.user_time);
    printf("nicetime:%llu \n",previousCPUStat.nice_time);
    printf("system_time:%llu \n",previousCPUStat.system_time);
    printf("idle_time:%llu \n",previousCPUStat.idle_time);
    printf("------------------------------------------ \n" );
 #endif

    loadPercentage = calculateSystemLoad(&previousCPUStat,&nowCPUStat);

    int sysLoad = (int) (loadPercentage >= 0) ? (int)(loadPercentage + 0.5):
                                                (int)(loadPercentage - 0.5);

    printf("System Load calculated :%3.2lf%% \n",loadPercentage );

    if ((sysLoad >= 0) && (sysLoad < 101))
    {
        displayCPUpercentage(sysLoad);
    }
    else
    {
        printf("Percentage calculated is invalid !!"
                " , Received Percentage: %d%%\n",sysLoad );
    }
}
