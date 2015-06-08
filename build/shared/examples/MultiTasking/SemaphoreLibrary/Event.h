///
/// @file		Event.h
/// @brief		Library header
/// @details	RTOS event as C++ object
/// @n
/// @n @b		Project Energia MT 0101E0016
///
/// @author		Energia, base
/// @author		Rei Vilo, enhancements 
///
/// @date		Jun 08, 2015 09:53
/// @version	103
///
/// @see        SYS/BIOS (TI-RTOS Kernel) v6.41 User's Guide (spruex3o)
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
/// @warning    NOTE: Only a single Task can pend on an Event object at a time.
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
    Event();

    ///
    /// @brief      Create the event
    ///
    void begin();

    ///
    /// @brief      Raise the event
    ///
    void send(xdc_UInt eventId_number);

    ///
    /// @brief      Wait for the event
    /// @param      ANDeventId_number AND condition, default=Event_Id_NONE
    /// @param      OReventId_number  OR  condition, default=Event_Id_NONE
    /// @return     events ID numbers as bit, 32-bit
    /// @example    0b=1100 = Event_Id_03 + Event_Id_02
    ///
    uint32_t waitFor(xdc_UInt ANDeventId_number=Event_Id_NONE, xdc_UInt OReventId_number=Event_Id_NONE);



};

#endif