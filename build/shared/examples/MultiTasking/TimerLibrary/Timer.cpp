//
// Timer.cpp 
// Library C++ code
// ----------------------------------
// Developed with embedXcode+ 
// http://embedXcode.weebly.com
//
// Project 		EMT-TimerLibrary
//
// Created by 	Rei Vilo, Jun 17, 2015 09:29
// 				http://embeddedcomputing.weebly.com
//
// Copyright 	(c) Rei Vilo, 2015
// Licence		CC = BY SA NC
//
// See 			Timer.h and ReadMe.txt for references
//


// Library header
#include "Timer.h"

// Code
Timer::Timer()
{
    ;
}

void Timer::begin(void (*timerFunction)(void), uint32_t timerPeriod_ms)
{
    Error_Block eb;
    Error_init(&eb);

    // xdc_UInt TimerId = 3; // OK=3, NOK=2,1,0 MSP432=4 timers, only timer 3 available
    // Timer_ANY to take any available timer
    xdc_UInt TimerId = Timer_ANY;
    
    Timer_Params_init(&timerParams);
    timerParams.periodType = Timer_PeriodType_MICROSECS;
    timerParams.period = timerPeriod_ms * 1000; // 1 ms = 1000 us
    timerParams.startMode = Timer_StartMode_USER; // Timer_start

    TimerHandle = Timer_create(TimerId, (ti_sysbios_interfaces_ITimer_FuncPtr)timerFunction, &timerParams, &eb);

    if (TimerHandle == NULL)
    {
        Serial.println("*** Timer create failed");
        System_abort("Timer create failed");
    }
}

void Timer::start()
{
    Timer_start(TimerHandle);
}

void Timer::stop()
{
    Timer_stop(TimerHandle);
}
