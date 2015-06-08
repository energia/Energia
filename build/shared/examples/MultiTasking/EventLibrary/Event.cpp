//
// Event.cpp
// Code file
// ----------------------------------
//
// Project EventLibrary for Energia MT 0101E0016
//

#include "Event.h"

Event::Event()
{
    ;
}

void Event::begin()
{
    Error_Block eb;
    Error_init(&eb);
    eventHandle = Event_create(NULL, &eb);
}

uint32_t Event::waitFor(xdc_UInt ANDeventId_number, xdc_UInt OReventId_number)
{
    return Event_pend(eventHandle,
               ANDeventId_number,
               OReventId_number,
               BIOS_WAIT_FOREVER);
}

void Event::send(xdc_UInt eventId_number)
{
    Event_post(eventHandle, eventId_number);
}
