/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                       K E Y B O A R D                                         * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "device/keyboard.h"
#include "device/interruptmanager.h"
#include "device/cgastr.h"
#include "object/cpu.h"

extern InterruptManager iManager;
extern CGA_Stream kout;

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */

void Keyboard::plugin()
{
    iManager.assign( InterruptManager::keyboard, *this );
}


void Keyboard::trigger()
{
    Key k = key_hit();
    if( !k.valid() )
        return;

    // Ctrl + Alt + Del
    if (k.ctrl() && k.alt() && ((int)k.scancode() == 83))
      Keyboard::reboot();

    //kout.show( KEYBOARD_X, KEYBOARD_Y, k.ascii(), 10);    <-- this would solve artifact problems
    kout<<k.ascii()<<endl;
    iManager.ack( InterruptManager::keyboard );
}
