/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                          P A N I C                                            * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include <common/panic.h>

#include <object/kout.h>
#include <object/cpu.h>
#include <config.h>


/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */

void Panic::trigger(){
  kout.flush();
  kout.setpos(DEBUG_Y, DEBUG_X);
  kout << "PANIC(" << mINum << ")!" << endl;
  cpu.halt();
}

void Panic::currentInterrupt(int iNum){
  mINum=iNum;
}
