#include "thread/waitingroom.h"

#include "object/lock.h"
#include "locking/scopedLock.h"
#include "object/scheduler.h"

Waitingroom::~Waitingroom(){
  ScopedLock scopedLock(lock);
	while(!empty())
		scheduler.wakeup(*static_cast<Customer*>(pop_front()));
}
