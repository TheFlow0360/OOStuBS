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


/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */

bool InterruptStorage::iNum2Index(int iNum, unsigned int& index){
  int temp = iNum-mMinINum;
  if(temp >= 0 && temp < mMaxINum-mMinINum){
    index=temp;
    return true;
  }else
    return false;
}

InterruptStorage::InterruptStorage(){
  for(unsigned int i=0;i<mMaxINum-mMinINum;i++)
    mHandler[i] = &panic;
}

void InterruptStorage::assign(int iNum, InterruptHandler& handler){
  unsigned int index;
  if(iNum2Index(iNum, index))
      mHandler[index] = &handler;
}

void InterruptStorage::handle(int iNum){
  unsigned int index;

  panic.currentInterrupt(iNum);

  if(iNum2Index(iNum, index))
    mHandler[index]->trigger();
  else
    panic.trigger();
}
