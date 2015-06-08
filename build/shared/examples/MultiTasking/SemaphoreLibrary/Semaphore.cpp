//
// Semaphore.cpp 
// Library C++ code
// ----------------------------------
// Developed with embedXcode+ 
// http://embedXcode.weebly.com
//
// Project 		EMT-Semaphore
//
// Created by 	Rei Vilo, Jun 08, 2015 09:53
// 				http://embeddedcomputing.weebly.com
//
// Copyright 	(c) Rei Vilo, 2015
// Licence		CC = BY SA NC
//
// See 			Semaphore.h and ReadMe.txt for references
//


// Library header
#include "Semaphore.h"

// Code
Semaphore::Semaphore()
{
    ;
}

void Semaphore::begin(uint8_t count)
{
    Error_Block eb;
    Error_init(&eb);
    SemaphoreHandle = Semaphore_create(count, NULL, &eb);
}

void Semaphore::waitFor()
{
    Semaphore_pend(SemaphoreHandle, BIOS_WAIT_FOREVER);
}

void Semaphore::post()
{
    Semaphore_post(SemaphoreHandle);
}
