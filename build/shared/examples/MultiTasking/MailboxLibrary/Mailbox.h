///
/// @file		Mailbox.h
/// @brief		Library header
/// @details	RTOS mailbox as C++ object for Energia MT
/// @n
/// @n @b		Project Energia MT 0101E0016
///
/// @author		Energia, base
/// @author		Rei Vilo, enhancements
///
/// @date		Jun 14, 2015 09:53
/// @version	101
///
/// @see        SYS/BIOS (TI-RTOS Kernel) v6.41 User's Guide (spruex3o)
///             http://www.ti.com/lit/pdf/spruex3
///

// Include application, user and local libraries
#include <Energia.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/knl/Mailbox.h>
#include <ti/sysbios/BIOS.h>

#ifndef Mailbox_h
#define Mailbox_h

///
/// @warning    Header and code for tempalte class need to be on the same unique file.
///             I guess it isn't a bug, but a feature :/
/// @see        http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2003/n1426.pdf
///

///
/// @brief      RTOS mailbox as an object
/// @details    The RTOS mailbox is encapsulated as a C++ object for easier use
/// @warning    NOTE: Only a single Task can pend on an Mailbox object at a time.
///
template <typename mailboxType> class Mailbox
{
private:
    Mailbox_Handle MailboxHandle;
    Mailbox_Params mboxParams;
    
    Event_Handle myEvent;
    static xdc_UInt MailboxId;
    xdc_UInt Mailbox_Id_number;
    
public:
    ///
    /// @brief      Define the mailbox
    /// @warning    Specify typename between brackets in declaration
    /// @code       Mailbox<typename> myMailbox;
    /// @endcode
    ///
    Mailbox();
    
    ///
    /// @brief      Create the mailbox
    /// @param		number number of messages of the mailbox, default = 16
    ///
    void begin(uint16_t number =16);

    
    ///
    /// @brief      Post a message to the mailbox
    /// @param      message message of type to be posted on the mailbox
    /// @warning    Message must be of type typename
    ///
    void post(mailboxType &message);
    
    ///
    /// @brief      Wait for a message from the mailbox
    /// @param      message message read from mailbox when available
    /// @warning    Message must be of type typename
    ///
    void waitFor(mailboxType &message);
};


template <typename mailboxType> Mailbox<mailboxType>::Mailbox()
{
    ;
}

template <typename mailboxType> void Mailbox<mailboxType>::begin(uint16_t number)
{
    Error_Block eb;
    Error_init(&eb);
    
    myEvent = Event_create(NULL, &eb);
    if (myEvent == NULL)
    {
        System_abort("Event create failed");
    }
    
    MailboxHandle = Mailbox_create(sizeof(mailboxType), number, NULL, &eb);
    if (MailboxHandle == NULL)
    {
        System_abort("Mailbox create failed");
    }
}

template <typename mailboxType> void Mailbox<mailboxType>::waitFor(mailboxType &message)
{
    Mailbox_pend(MailboxHandle, &message, BIOS_WAIT_FOREVER);}

template <typename mailboxType> void Mailbox<mailboxType>::post(mailboxType &message)
{
     Mailbox_post(MailboxHandle, &message, BIOS_NO_WAIT);
}

#endif
