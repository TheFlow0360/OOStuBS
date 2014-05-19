/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                               I N T E R R U P T _ S T O R A G E                               * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "common/interruptstorage.h"
#include "machine/mem.h"
#include "config.h"


/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */

InterruptStorage::InterruptStorage() {
  // allocate Memory for the mapping-array
  handlers = (InterruptHandler**) Memory::alloc(MAX_INTERRUPT_NUMBER - MIN_INTERRUPT_NUMBER);
  // initialize all interruptHandlers with Panic
  for (int i = 0; i < MAX_INTERRUPT_NUMBER - MIN_INTERRUPT_NUMBER; i++) {
    handlers[i] = &panic;
  }
}


void InterruptStorage::assign(int iNum, InterruptHandler& handler) {
  handlers[iNum - MIN_INTERRUPT_NUMBER] = &handler;
}

void InterruptStorage::handle(int iNum) {
  int index = iNum - MIN_INTERRUPT_NUMBER;
  panic.currentInterrupt(iNum);
  handlers[index]->trigger();
  panic.currentInterrupt(-1);
}

bool InterruptStorage::currentInterrupt(int &iNum)
{
  int tmp = panic.getCurrentInterrupt();
  if (tmp >= 0) {
    iNum = tmp;
    return true;
  }
  return false;
}
