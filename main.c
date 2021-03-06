#include <xc.h>
#include "config.h"
#include "Std_Types.h"
#include "COMMON_private.h"
#include "DIO_interface.h"
#include "INTERRUPTS_interface.h"
#include "TIMER0_interface.h"
#include "SCHEDULER_interface.h"
#include "EEPROM_interface.h"
#include "APP_interface.h"

Task_Type taskUpdateDisp;
Task_Type taskGetTemperature;
Task_Type taskContMode;
Task_Type taskLED;
void main(void) {
    
    APP_vidInit();
    
    /*Task initialization*/
    taskUpdateDisp.ptrfun = APP_vidUpdateSevenSeg;
    taskUpdateDisp.u16FirstDelay = 0;
    taskUpdateDisp.u16Periodicity = 1;
    taskUpdateDisp.u8State = SCHEDULER_TASKSTATE_RUNNING;
    
    taskGetTemperature.ptrfun = APP_vidGetTemperature;
    taskGetTemperature.u16FirstDelay = 0;
    taskGetTemperature.u16Periodicity = 15; /*0.1 Second*/
    taskGetTemperature.u8State = SCHEDULER_TASKSTATE_RUNNING;
    
    
    taskContMode.ptrfun = APP_vidContMode;
    taskContMode.u16FirstDelay = 0;
    taskContMode.u16Periodicity = 780; /*5 Seconds*/
    taskContMode.u8State = SCHEDULER_TASKSTATE_RUNNING;
    
    taskLED.ptrfun = APP_vidContLED;
    taskLED.u16FirstDelay = 0;
    taskLED.u16Periodicity = 156; /*1 Second*/
    taskLED.u8State = SCHEDULER_TASKSTATE_RUNNING;
    
  
    SCHEDULER_vidInit(SCHEDULER_GLOBALINTERRUPT_RAISED);

    SCHEDULER_vidCreateTask(_SCHEDULER_GETID(taskUpdateDisp),SCHEDULER_TASK0);
    SCHEDULER_vidCreateTask(_SCHEDULER_GETID(taskGetTemperature),SCHEDULER_TASK1);
    SCHEDULER_vidCreateTask(_SCHEDULER_GETID(taskContMode),SCHEDULER_TASK2);
    SCHEDULER_vidCreateTask(_SCHEDULER_GETID(taskLED),SCHEDULER_TASK3);
    
    while(1)
    {
  
    }
}