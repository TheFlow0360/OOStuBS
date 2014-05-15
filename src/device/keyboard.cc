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

    //kout.show( KEYBOARD_X, KEYBOARD_Y, k.ascii(), 10);
    kout<<k.ascii()<<endl;
    iManager.ack( InterruptManager::keyboard );
}
