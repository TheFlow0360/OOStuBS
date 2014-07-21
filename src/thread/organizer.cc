#include "thread/organizer.h"
#include "object/lock.h"
#include "locking/scopedLock.h"
#include "common/null.h"
#include "object/log.h"

void Organizer::block(Waitingroom& room){
    room.push_back(*active());
    active()->waiting_in(&room);
    log << "Suspending Thread " << active() << endl;
    next();
}
 
void Organizer::wakeup(Customer& customer){
   // ergänzen //
  
   log << "Reactivating Thread " << &customer << endl;
}
// 
bool Organizer::kill(Customer& that){
   //    ergänzen //
   
   return true;  //<-- Platzhalter
}

Customer* Organizer::active() const{
    return static_cast<Customer*>(Scheduler::active());
}
