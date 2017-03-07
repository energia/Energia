
// Required by RTOS
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

void vApplicationIdleHook( void )
{
    // put low power sleep code here
}

void vApplicationMallocFailedHook( void )
{
    while(1)
  {
    // Infinite loop;
  }
}

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed portCHAR *pcTaskName )
{
    ( void ) pxTask;
    ( void ) pcTaskName;

    for( ;; );
}

