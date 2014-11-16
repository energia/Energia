#include <Energia.h>
#include "inc/hw_gpio.h"
#include "driverlib/rom_map.h"
#include "driverlib/prcm.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include <driverlib/utils.h>
#include "inc/hw_hib1p2.h"
#include "inc/hw_hib3p3.h"

extern void (* const g_pfnVectors[])(void);

#ifdef __cplusplus
extern "C" {
#endif

// RTOS framework
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/osi.h"

void vTaskDefault( void *pvParameters ){
	for (;;) {
      loop();
	  if (serialEventRun) serialEventRun();
	}
}

#ifdef __cplusplus
} /* extern "C" */
#endif


int main(void)
{
	IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);

	MAP_PRCMPeripheralClkEnable(PRCM_GPIOA0, PRCM_RUN_MODE_CLK);
	MAP_PRCMPeripheralClkEnable(PRCM_GPIOA1, PRCM_RUN_MODE_CLK);
	MAP_PRCMPeripheralClkEnable(PRCM_GPIOA2, PRCM_RUN_MODE_CLK);
	MAP_PRCMPeripheralClkEnable(PRCM_GPIOA3, PRCM_RUN_MODE_CLK);

	MAP_IntMasterEnable();
	PRCMCC3200MCUInit();
	MAP_SysTickIntEnable();
	MAP_SysTickPeriodSet(F_CPU / 1000);
	MAP_SysTickEnable();

	// do legacy setup function and create new task if needed
	setup();

	// create a task to run legacy loop function 
    osi_TaskCreate( vTaskDefault, ( signed portCHAR * ) "Default", OSI_DEFAULT_STACK_SIZE, NULL, 1, NULL );
	
	//RTOS start
	osi_start();

}
