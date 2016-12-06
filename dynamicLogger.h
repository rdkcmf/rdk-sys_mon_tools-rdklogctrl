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

#ifndef _DYNAMIC_LOGGER_H_
#define _DYNAMIC_LOGGER_H_

#include "libIBus.h"

#define IARM_BUS_DYNAMIC_LOGGER_NAME "iARMDynamicLogger_tool"

/*IARM event published by dynamic logger module*/
typedef enum _DynamicLogger_EventId_t {
    IARM_BUS_DYNAMICLOGGER_EVENT_LOG_STATUS=0,
    IARM_BUS_DYNAMICLOGGER_EVENT_MAX
}IARM_Bus_DynamicLogger_EventId_t;

typedef enum _LogStatus_t {
    LOG_DISABLE = 0,
    LOG_ENABLE,
    LOG_MAX
}LogStatus_t;

/*Event data published by dynamic logger module*/
typedef struct _DynamicLogger_EventData_t {
  char appName[15];
  char moduleName[15];
  char subModuleName[15];
  char logLevel[10];
  LogStatus_t log_status;
}IARM_Bus_DynamicLogger_EventData_t;

#endif
