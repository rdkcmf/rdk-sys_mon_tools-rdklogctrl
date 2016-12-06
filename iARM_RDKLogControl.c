/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "dynamicLogger.h"


void usage ()
{
    printf ("\nGeneral Usage:\n");
    printf ("\nUsage: 'rdklogctrl [APP NAME] [COMPONENT NAME] [SUB COMPONENT NAME] [LOG LEVEL] [STATUS]'\n");
    printf ("\tCMDs are,\n");
    printf ("\t\t -h                   -> Help\n");
    printf ("\t\t [APP NAME]           -> [STATUS] Application to be notified about the log status\n");
    printf ("\t\t [COMPONENT NAME]     -> Component name\n");
    printf ("\t\t [SUB COMPONENT NAME] -> Sub components under the given component\n");
    printf ("\t\t                         NULL if log need to be enabled for all sub components\n");
    printf ("\t\t [LOG LEVEL]          -> See available options below\n");
    printf ("\t\t [STATUS]             -> ON/OFF to enable/disable Dynamic logging\n");


    printf ("\n\t Available [A]pplications, [C]omponents, [S]ubComponents, [L]og Levels:\\n"); //ACSL
    printf ("\t\t [A]Receiver, [C]ClosedCaptions, [S]NULL,[L] INFO,WARN,LOG,DEBUG,TRACE,TRACE1-TRACE8 \n");
}

/**
 * Application can be used to enable dynamic logging for the modules:
 * closedcaption,hdmicec
 * Ref Ticket: RDK-14892
 */

int main(int argc, char *argv[])
{
    int ret = 0;
    IARM_Result_t retVal = IARM_RESULT_SUCCESS;
    IARM_Bus_DynamicLogger_EventData_t eventData;
    memset(&eventData,0,sizeof(eventData));

    if(6 == argc)
    {
        if(0 == strncmp("ON",argv[5], 2))
        {
            eventData.log_status = LOG_ENABLE;
        }
        else if(0 == strncmp("OFF",argv[5], 3))
        {
            eventData.log_status = LOG_DISABLE;
        }
        else
        {
            printf("Output : FAILED \n Invalid Entry \n");
            ret = 1;
        }

    }
    else if ((2 == argc) && (argv[1][1] == 'h'))
    {
        ret = 1;
    }
    else
    {
        printf("Output : FAILED \n Invalid Entry \n");
        ret = 1;
    }

    if(0 == ret)
    {
        IARM_Bus_Init("IARM_BUS_DYNAMIC_LOGGER_NAME");
        IARM_Bus_Connect();

        strncpy(eventData.appName, argv[1],strlen(argv[1]));
        eventData.appName[strlen(argv[1]) + 1] = '\0';
        strncpy(eventData.moduleName, argv[2], strlen(argv[2]));
        eventData.moduleName[strlen(argv[2]) + 1] = '\0';
        strncpy(eventData.subModuleName, argv[3], strlen(argv[3]));
        eventData.subModuleName[strlen(argv[3]) + 1] = '\0';
        strncpy(eventData.logLevel, argv[4],strlen(argv[4]));
        eventData.logLevel[strlen(argv[4]) + 1] = '\0';

        retVal = IARM_Bus_BroadcastEvent(IARM_BUS_DYNAMIC_LOGGER_NAME,(IARM_EventId_t)IARM_BUS_DYNAMICLOGGER_EVENT_LOG_STATUS,(void *)&eventData, sizeof(eventData));

        IARM_Bus_Disconnect();
        IARM_Bus_Term();

        if(IARM_RESULT_SUCCESS == retVal)
           printf("Output : SUCCESS \n");
        else
           printf("Output : FAILED \n IARM Failure \n");
    }
    else
    {
        usage();
    }
    return ret;
}
