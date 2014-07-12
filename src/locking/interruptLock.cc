#include "locking/interruptLock.h"

#include "object/log.h"
#include "object/cpu.h"

void InterruptLock::enter(){
  interruptState=true;
  state=true;
}

void InterruptLock::leave(){
  state=false;
}

void InterruptLock::lock(){
    interruptState=cpu.disable_int();
    if(state)
        log << "Lock(" << this << "): double lock" << endl;
    state=true;
}

void InterruptLock::unlock(){
    if(!state)
        log << "Lock(" << this << "): double unlock" << endl;
    state=false;
    if(interruptState)
        cpu.enable_int();
}

InterruptLock::~InterruptLock(){
  if(state)
    unlock();
}
