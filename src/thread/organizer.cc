#include "thread/organizer.h"
#include "object/lock.h"
#include "locking/scopedLock.h"
#include "locking/semaphore.h"
#include "common/null.h"
#include "object/log.h"

void Organizer::block(Waitingroom& room){
  room.push_back(*active());
  active()->waiting_in(&room);
  log << "Suspending Thread " << active() << endl;
  Scheduler::kill(*active());
  //next();
}
 
void Organizer::wakeup(Customer& customer) {
  customer.waiting_in()->remove(customer);
  Scheduler::reactivate(customer);
  log << "Reactivating Thread " << &customer << endl;
}

bool Organizer::kill(Customer& that){
  that.waiting_in()->remove(that);
  log << "Killing Thread " << &that << endl;
  return Scheduler::kill(that);
}

Customer* Organizer::active() const{
  return static_cast<Customer*>(Scheduler::active());
}
