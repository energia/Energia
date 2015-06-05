///
/// @file		Event.h
/// @brief		Library header
/// @details	  RTOS event as C++ object
/// @n
/// @n @b	 Project EventLibrary for Energia MT 0101E0016
///


// Include application, user and local libraries
#include <Energia.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/BIOS.h>

#ifndef Event_h
#define Event_h

///
/// @brief      RTOS event as object
/// @details    The RTOS event is encapsulated as a C++ object for easier use
///
class Event {

  private:
    Event_Handle eventHandle;
    static xdc_UInt eventId;
    xdc_UInt event_Id_number;
  public:
    ///
    /// @brief      Define the event
    /// @param      eventId_number even unique identifier Event_Id_00..Event_Id_31
    /// @warning    Reuse of the same event ID is not checked
    ///
    Event(xdc_UInt eventId_number);

    ///
    /// @brief      Create the event
    ///
    void begin();

    ///
    /// @brief      Raise the event
    ///
    void send();

    ///
    /// @brief      Wait for the event
    ///
    void waitFor();

};

#endif
