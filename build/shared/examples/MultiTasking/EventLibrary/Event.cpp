//
// Event.cpp
// Code file
// ----------------------------------
//
// Project EventLibrary for Energia MT 0101E0016
//

#include "Event.h"

Event::Event(xdc_UInt eventId_number)
{
  event_Id_number = eventId_number;
}

void Event::begin()
{
  Error_Block eb;
  Error_init(&eb);
  eventHandle = Event_create(NULL, &eb);
}

void Event::waitFor()
{
  Event_pend(eventHandle, Event_Id_NONE,
    event_Id_number, BIOS_WAIT_FOREVER);    
}

void Event::send()
{
  Event_post(eventHandle, event_Id_number);  
}
