#include "locking/semaphore.h"
#include "object/scheduler.h"
#include "object/lock.h"
#include "object/log.h"
#include "locking/scopedLock.h"

Semaphore::Semaphore(unsigned int value) : value(value){
}

void Semaphore::p(){
  ScopedLock scopedLock(lock);
  log << "Semaphore is going to wait" << endl;
  if (value <= 0)
    scheduler.block(*this);
  else
    value--;
}

void Semaphore::v(){
  //ScopedLock scopedLock(lock);
  value++;
  scheduler.wakeup(*((Customer*)this->peek_front()));
  log << "Semaphore received signal" << endl;
}

void  Semaphore::interrupt_signal(){
  signal();
}
