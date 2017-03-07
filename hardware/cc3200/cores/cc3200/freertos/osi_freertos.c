//*****************************************************************************
// osi_freertos.c
//
// Interface APIs for free-rtos function calls
//
// Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/ 
// 
// 
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//    Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the 
//    documentation and/or other materials provided with the   
//    distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "portmacro.h"
#include "osi.h"

portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
//Local function definition
static void vSimpleLinkSpawnTask( void *pvParameters );
//Queue Handler
xQueueHandle xSimpleLinkSpawnQueue;
xTaskHandle xSimpleLinkSpawnTaskHndl;
// Queue size 
#define slQUEUE_SIZE				( 3 )

extern void IntRegister(unsigned long ulInterrupt, void (*pfnHandler)(void));
extern void IntEnable(unsigned long ulInterrupt);
extern void IntUnregister(unsigned long ulInterrupt);
extern void IntDisable(unsigned long ulInterrupt);
extern void IntPrioritySet(unsigned long ulInterrupt, unsigned char ucPriority);

/*!
	\brief 	This function registers an interrupt in NVIC table

	The sync object is used for synchronization between different thread or ISR and
	a thread.

	\param	iIntrNum	-	Interrupt number to register
	\param	pEntry	    -	Pointer to the interrupt handler
	\param	ucPriority	-	priority of the interrupt

	\return upon successful creation the function should return 0
			Otherwise, a negative value indicating the error code shall be returned
	\note
	\warning
*/
int osi_InterruptRegister(int iIntrNum,P_OSI_INTR_ENTRY pEntry,unsigned char ucPriority)
{
	IntRegister(iIntrNum,(void(*)(void))pEntry);
	IntPrioritySet(iIntrNum, ucPriority);
	IntEnable(iIntrNum);
	return OSI_OK;
}

/*!
	\brief 	This function De registers an interrupt in NVIC table


	\param	iIntrNum	-	Interrupt number to De register

	\return 	none
	\note
	\warning
*/

void osi_InterruptDeRegister(int iIntrNum)
{
	IntDisable(iIntrNum);
	IntUnregister(iIntrNum);
}

/*!
	\brief 	This function creates a sync object

	The sync object is used for synchronization between different thread or ISR and
	a thread.

	\param	pSyncObj	-	pointer to the sync object control block

	\return upon successful creation the function should return 0
			Otherwise, a negative value indicating the error code shall be returned
	\note
	\warning
*/
int osi_SyncObjCreate(OsiSyncObj_t* pSyncObj)           
{
	xSemaphoreHandle *pl_SyncObj = (xSemaphoreHandle *)pSyncObj;

	vSemaphoreCreateBinary((*pl_SyncObj));

	//pSyncObj = (OsiSyncObj_t*)(pl_SyncObj);
    if((xSemaphoreHandle)(*pSyncObj) != NULL)
    {
        osi_SyncObjClear(pSyncObj);
        return OSI_OK; //success is 0
    }
    else
    {
        return OSI_FAILURE;
    }
}

/*!
	\brief 	This function deletes a sync object

	\param	pSyncObj	-	pointer to the sync object control block

	\return upon successful deletion the function should return 0
			Otherwise, a negative value indicating the error code shall be returned
	\note
	\warning
*/
int osi_SyncObjDelete(OsiSyncObj_t* pSyncObj)
{
    vSemaphoreDelete(*pSyncObj );
    return OSI_OK;
}

/*!
	\brief 		This function generates a sync signal for the object.

	All suspended threads waiting on this sync object are resumed

	\param		pSyncObj	-	pointer to the sync object control block

	\return 	upon successful signaling the function should return 0
				Otherwise, a negative value indicating the error code shall be returned
	\note		the function could be called from ISR context
	\warning
*/
int osi_SyncObjSignal(OsiSyncObj_t* pSyncObj)
{
    xSemaphoreGive( *pSyncObj );	//not sure about this
    return OSI_OK;
}
/*!
	\brief 		This function generates a sync signal for the object
				from ISR context.

	All suspended threads waiting on this sync object are resumed

	\param		pSyncObj	-	pointer to the sync object control block

	\return 	upon successful signalling the function should return 0
				Otherwise, a negative value indicating the error code shall be returned
	\note		the function is called from ISR context
	\warning
*/
int osi_SyncObjSignalFromISR(OsiSyncObj_t* pSyncObj)
{
	xHigherPriorityTaskWoken = pdFALSE;
	xSemaphoreGiveFromISR( *pSyncObj, &xHigherPriorityTaskWoken );

	if( xHigherPriorityTaskWoken )
	{
		taskYIELD ();
	}
    return OSI_OK;
}

/*!
	\brief 	This function waits for a sync signal of the specific sync object

	\param	pSyncObj	-	pointer to the sync object control block
	\param	Timeout		-	numeric value specifies the maximum number of mSec to
							stay suspended while waiting for the sync signal
							Currently, the simple link driver uses only two values:
								- OSI_WAIT_FOREVER
								- OSI_NO_WAIT

	\return upon successful reception of the signal within the timeout window return 0
			Otherwise, a negative value indicating the error code shall be returned
	\note
	\warning
*/
int osi_SyncObjWait(OsiSyncObj_t* pSyncObj , OsiTime_t Timeout)
{
    if(xSemaphoreTake( (xSemaphoreHandle)*pSyncObj, ( portTickType )(Timeout/portTICK_RATE_MS) ) == pdTRUE)	 //not sure about this
    {
        return OSI_OK;
    }
    else
    {
        return OSI_FAILURE; 
    }
}

/*!
	\brief 	This function clears a sync object

	\param	pSyncObj	-	pointer to the sync object control block

	\return upon successful clearing the function should return 0
			Otherwise, a negative value indicating the error code shall be returned
	\note
	\warning
*/
int osi_SyncObjClear(OsiSyncObj_t* pSyncObj)
{
    if (osi_SyncObjWait(pSyncObj,0) == OSI_OK )
    {
        return OSI_OK;
    }
    else
    {
        return OSI_FAILURE;
    }
}

/*!
	\brief 	This function creates a locking object.

	The locking object is used for protecting a shared resources between different
	threads.

	\param	pLockObj	-	pointer to the locking object control block

	\return upon successful creation the function should return 0
			Otherwise, a negative value indicating the error code shall be returned
	\note
	\warning
*/
int osi_LockObjCreate(OsiLockObj_t* pLockObj) 
{
	*pLockObj = (OsiLockObj_t)xSemaphoreCreateMutex();
    if(pLockObj != NULL)
    {  
        return OSI_OK;
    }
    else
    {
        return OSI_FAILURE;
    }
}

/*!
	\brief 	This function creates a Task.

	Creates a new Task and add it to the last of tasks that are ready to run

	\param	pEntry	-	pointer to the Task Function
	\param	pcName	-	Task Name String
	\param	usStackDepth	-	Stack Size in bytes
	\param	pvParameters	-	pointer to structure to be passed to the Task Function
	\param	uxPriority	-	Task Priority

	\return upon successful creation the function should return 1
			Otherwise, 0 or a negative value indicating the error code shall be returned
	\note
	\warning
*/
int osi_TaskCreate(P_OSI_TASK_ENTRY pEntry,const signed char * const pcName,unsigned short usStackDepth,
void *pvParameters,unsigned long uxPriority,OsiTaskHandle* pTaskHandle)
{
   	long xReturn;
	xReturn = xTaskCreate( pEntry, pcName,(usStackDepth/(sizeof( portSTACK_TYPE ))), pvParameters, (unsigned portBASE_TYPE)uxPriority, (xTaskHandle*)pTaskHandle );
	if(xReturn==pdPASS)
	{
		return OSI_OK;
	}

	return OSI_OPERATION_FAILED;	
}


/*!
	\brief 	This function Deletes a Task.

	Deletes a  Task and remove it from list of running task

	\param	pTaskHandle	-	Task Handle

	\note
	\warning
*/
void osi_TaskDelete(OsiTaskHandle* pTaskHandle)
{
	vTaskDelete((xTaskHandle)*pTaskHandle);
}



/*!
	\brief 	This function deletes a locking object.

	\param	pLockObj	-	pointer to the locking object control block

	\return upon successful deletion the function should return 0
			Otherwise, a negative value indicating the error code shall be returned
	\note
	\warning
*/
int osi_LockObjDelete(OsiLockObj_t* pLockObj)
{
    vSemaphoreDelete((xSemaphoreHandle)*pLockObj );
    return OSI_OK;
}

/*!
	\brief 	This function locks a locking object.

	All other threads that call this function before this thread calls
	the osi_LockObjUnlock would be suspended

	\param	pLockObj	-	pointer to the locking object control block
	\param	Timeout		-	numeric value specifies the maximum number of mSec to
							stay suspended while waiting for the locking object
							Currently, the simple link driver uses only two values:
								- OSI_WAIT_FOREVER
								- OSI_NO_WAIT


	\return upon successful reception of the locking object the function should return 0
			Otherwise, a negative value indicating the error code shall be returned
	\note
	\warning
*/
int osi_LockObjLock(OsiLockObj_t* pLockObj , OsiTime_t Timeout)
{
    if( xSemaphoreTake( *pLockObj, ( portTickType ) (Timeout/portTICK_RATE_MS) ) == pdTRUE)
    {
        return OSI_OK;
    }
    else
    {
        return OSI_FAILURE;
    }
}

/*!
	\brief 	This function unlock a locking object.

	\param	pLockObj	-	pointer to the locking object control block

	\return upon successful unlocking the function should return 0
			Otherwise, a negative value indicating the error code shall be returned
	\note
	\warning
*/
int osi_LockObjUnlock(OsiLockObj_t* pLockObj)
{
    xSemaphoreGive( *pLockObj );	
    return OSI_OK;
}



#if 0
int osi_Spawn(P_OSI_SPAWN_ENTRY pEntry , void* pValue , unsigned long flags)
{

    xTaskCreate( pEntry, ( signed portCHAR * ) "SIMPLELINK", configMINIMAL_STACK_SIZE, pValue, tskIDLE_PRIORITY+1, NULL );
    return 0;
}

#endif

/*!
	\brief 	This function call the pEntry callback from a different context

	\param	pEntry		-	pointer to the entry callback function

	\param	pValue		- 	pointer to any type of memory structure that would be
							passed to pEntry callback from the execution thread.

	\param	flags		- 	execution flags - reserved for future usage

	\return upon successful registration of the spawn the function should return 0
			(the function is not blocked till the end of the execution of the function
			and could be returned before the execution is actually completed)
			Otherwise, a negative value indicating the error code shall be returned
	\note
	\warning
*/

int osi_Spawn(P_OSI_SPAWN_ENTRY pEntry , void* pValue , unsigned long flags)
{

        tSimpleLinkSpawnMsg Msg; 
        Msg.pEntry = pEntry;
        Msg.pValue = pValue;
        xHigherPriorityTaskWoken = pdFALSE;

	xQueueSendFromISR( xSimpleLinkSpawnQueue, &Msg, &xHigherPriorityTaskWoken );

	if( xHigherPriorityTaskWoken )
	{
		taskYIELD ();
	}

    return 0;
}


/*!
	\brief 	This is the simplelink spawn task to call SL callback from a different context 

	\param	pvParameters		-	pointer to the task parameter

	\return void
	\note
	\warning
*/
void vSimpleLinkSpawnTask(void *pvParameters)
{
        tSimpleLinkSpawnMsg Msg; 
        portBASE_TYPE ret=pdFAIL;
            
        for(;;)
        {
            ret = xQueueReceive( xSimpleLinkSpawnQueue, &Msg, portMAX_DELAY );
            if(ret == pdPASS)
            {
                    Msg.pEntry(Msg.pValue);
            }
        }
}

/*!
	\brief 	This is the API to create SL spawn task and create the SL queue

	\param	uxPriority		-	task priority

	\return void
	\note
	\warning
*/
void VStartSimpleLinkSpawnTask(unsigned portBASE_TYPE uxPriority)
{
    xSimpleLinkSpawnQueue = xQueueCreate( slQUEUE_SIZE, sizeof( tSimpleLinkSpawnMsg ) );
    xTaskCreate( vSimpleLinkSpawnTask, ( signed portCHAR * ) "SLSPAWN",\
    					 (2048/sizeof( portSTACK_TYPE )), NULL, uxPriority, &xSimpleLinkSpawnTaskHndl );
}

/*!
	\brief 	This is the API to delete SL spawn task and delete the SL queue

	\param	none

	\return void
	\note
	\warning
*/
void VDeleteSimpleLinkSpawnTask( void )
{
    vTaskDelete( xSimpleLinkSpawnTaskHndl );
    vQueueDelete( xSimpleLinkSpawnQueue );
}

/*!
	\brief 	This function is used to create the MsgQ

	\param	pMsgQ	-	pointer to the message queue
	\param	pMsgQName	-	msg queue name
	\param	MsgSize	-	size of message on the queue
	\param	MaxMsgs	-	max. number of msgs that the queue can hold

	\return - OsiReturnVal_e
	\note
	\warning
*/
OsiReturnVal_e osi_MsgQCreate(OsiMsgQ_t* 		pMsgQ , 
			      char*			pMsgQName,
			      unsigned long 		MsgSize,
			      unsigned long		MaxMsgs)
{
        xQueueHandle handle =0;
        handle = xQueueCreate( MaxMsgs, MsgSize );
        if (handle==0)
        {
            return OSI_OPERATION_FAILED;
        }
        *pMsgQ = (OsiMsgQ_t)handle;
        return OSI_OK;
}
/*!
	\brief 	This function is used to delete the MsgQ

	\param	pMsgQ	-	pointer to the message queue

	\return - OsiReturnVal_e
	\note
	\warning
*/
OsiReturnVal_e osi_MsgQDelete(OsiMsgQ_t* pMsgQ)
{
	vQueueDelete((xQueueHandle) *pMsgQ );
        return OSI_OK;
}
/*!
	\brief 	This function is used to write data to the MsgQ

	\param	pMsgQ	-	pointer to the message queue
	\param	pMsg	-	pointer to the Msg strut to read into
	\param	Timeout	-	timeout to wait for the Msg to be available

	\return - OsiReturnVal_e
	\note
	\warning
*/

OsiReturnVal_e osi_MsgQWrite(OsiMsgQ_t* pMsgQ, void* pMsg , OsiTime_t Timeout)
{
        if(pdPASS == xQueueSendFromISR((xQueueHandle) *pMsgQ, pMsg, &xHigherPriorityTaskWoken ))
        {
           taskYIELD ();          
           return OSI_OK;
        }
	else
	{
	  return OSI_OPERATION_FAILED;
	}
}
/*!
	\brief 	This function is used to read data from the MsgQ

	\param	pMsgQ	-	pointer to the message queue
	\param	pMsg	-	pointer to the Msg strut to read into
	\param	Timeout	-	timeout to wait for the Msg to be available

	\return - OsiReturnVal_e
	\note
	\warning
*/

OsiReturnVal_e osi_MsgQRead(OsiMsgQ_t* pMsgQ, void* pMsg , OsiTime_t Timeout)
{
  if ( Timeout == OSI_WAIT_FOREVER )
    {
      Timeout = portMAX_DELAY ;
    }
  if( pdTRUE  == xQueueReceive((xQueueHandle)*pMsgQ,pMsg,Timeout) )
  {
     return OSI_OK;
  }
  else
  {
     return OSI_OPERATION_FAILED;
  }
}

/*!
	\brief 	This function to call the memory de-allocation function of the FREERTOS

	\param	Size	-	size of memory to alloc in bytes

	\return - void *
	\note
	\warning
*/

void * mem_Malloc(unsigned long Size)
{
  
    return ( void * ) pvPortMalloc( (size_t)Size );
}

/*!
	\brief 	This function to call the memory de-allocation function of the FREERTOS

	\param	pMem		-	pointer to the memory which needs to be freed
	
	\return - void 
	\note
	\warning
*/
void mem_Free(void *pMem)
{
    vPortFree( pMem );
}

/*!
	\brief 	This function call the memset function
	\param	pBuf		-	pointer to the memory to be fill
    \param Val          -   Value to be fill
    \param Size         -   Size of the memory which needs to be fill
	
	\return - void 
	\note
	\warning
*/

void  mem_set(void *pBuf,int Val,size_t Size)
{
    memset( pBuf,Val,Size);
  
}

/*!
	\brief 	This function call the memcopy function
	\param	pDst	-	pointer to the destination
    \param pSrc     -   pointer to the source
    \param Size     -   Size of the memory which needs to be copy
	
	\return - void 
	\note
	\warning
*/
void  mem_copy(void *pDst, void *pSrc,size_t Size)
{
    memcpy(pDst,pSrc,Size);
}


/*!
	\brief 	This function use to entering into critical section
	\param	void		
	\return - void 
	\note
	\warning
*/

unsigned long osi_EnterCritical(void)
{
    vPortEnterCritical();
    return 0;
}

/*!
	\brief 	This function use to exit critical section
	\param	void		
	\return - void 
	\note
	\warning
*/

void osi_ExitCritical(unsigned long ulKey)
{
    vPortExitCritical();
}
/*!
	\brief 	This function used to start the scheduler
	\param	void
	\return - void
	\note
	\warning
*/
void osi_start()
{

    vTaskStartScheduler();
}
/*!
	\brief 	This function used to suspend the task for the specified number of milli secs
	\param	MilliSecs	-	Time in millisecs to suspend the task
	\return - void
	\note
	\warning
*/
void osi_Sleep(unsigned int MilliSecs)
{
	portTickType xDelay = MilliSecs / portTICK_RATE_MS;
	vTaskDelay(xDelay);
}


/*!
	\brief 	This function used to disable the tasks
	\param	- void
	\return - Key with the suspended tasks
	\note
	\warning
*/
unsigned long osi_TaskDisable(void)
{
   vTaskSuspendAll();

   return 0;
}


/*!
	\brief 	This function used to resume all the tasks
	\param	key	-	returned from suspend tasks
	\return - void
	\note
	\warning
*/
void osi_TaskEnable(unsigned long key)
{
   xTaskResumeAll();
}

/*!
	\brief 	This function used to save the OS context before sleep
	\param	void
	\return - void
	\note
	\warning
*/
void osi_ContextSave()
{

}
/*!
	\brief 	This function used to restore the OS context after sleep
	\param	void
	\return - void
	\note
	\warning
*/
void osi_ContextRestore()
{

}

/* TBD*/

void SimpleLinkGeneralEventHandler(void *pArgs)
{}





/* TBD*/
void SimpleLinkSockEventHandler(void *pArgs){}





