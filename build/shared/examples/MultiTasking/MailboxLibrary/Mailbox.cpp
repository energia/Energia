////
//// Mailbox.cpp
//// Code file
//// ----------------------------------
////
//// Project MailboxLibrary for Energia MT 0101E0016
////
//
// @warning    Header and code for tempalte class need to be on the same unique file.
//             I guess it isn't a bug, but a feature :/
// @see        http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2003/n1426.pdf
//
//
//#include "Mailbox.h"
//
//
//template <typename mailboxType> Mailbox<mailboxType>::Mailbox()
//{
//    ;
//}
//
//template <typename mailboxType> void Mailbox<mailboxType>::begin(uint16_t number)
//{
//    Error_Block eb;
//    Error_init(&eb);
//    
//    myEvent = Event_create(NULL, &eb);
//    if (myEvent == NULL)
//    {
//        System_abort("Event create failed");
//    }
//    
//    MailboxHandle = Mailbox_create(sizeof(mailboxType), number, NULL, &eb);
//    if (MailboxHandle == NULL)
//    {
//        System_abort("Mailbox create failed");
//    }
//}
//
//template <typename mailboxType> void Mailbox<mailboxType>::waitFor(mailboxType &message)
//{
//    Mailbox_pend(MailboxHandle, &message, BIOS_WAIT_FOREVER);}
//
//template <typename mailboxType> void Mailbox<mailboxType>::post(mailboxType &message)
//{
//    Mailbox_post(MailboxHandle, &message, BIOS_NO_WAIT);
//}
//
