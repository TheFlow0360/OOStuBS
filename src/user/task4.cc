#include "user/task4.h"
#include "object/lock.h"
#include "object/kout.h"
#include "object/keyboard.h"
#include "object/scheduler.h"
#include "object/log.h"

Task4::RotCursor::RotCursor(unsigned short x, unsigned short y) : i(0), x(x), y(y), coop(false){}

void Task4::RotCursor::action(){
	while(true)
	{
    lock.lock();
    kout.flush();
    kout.setpos(x, y);
    switch(i++%4)
    {
        case(0):	kout << '|';
                  break;
        case(1):	kout << '/';
                  break;	
        case(2):	kout << '-';
                  break;
        case(3):	kout << '\\';
                  break;
    }
    kout.flush();
    lock.unlock();
    if(coop)
      yield();
	}
}

Task4::Counter::Counter(unsigned short x, unsigned short y) : i(0), x(x), y(y), coop(false){}

void Task4::Counter::action(){
	while(true)
	{
    lock.lock();
    kout.flush();
    kout.setpos(x, y);
    kout << "Counter: " << i++ << endl;
    lock.unlock();
    if(coop)
      yield();
	}
}

Task4::Task4() : rotCursor(rotCursorX, rotCursorY),
                 rotCursor2(0,0),
				         counter1(counter1X, counter1Y),
				         counter2(counter2X, counter2Y){
  log << "Task4 created" << endl;
}

Task4::~Task4(){
  log << "Finished Setup of Task4" << endl;
}

void Task4::action(){
  kout.clear();
	kout.setpos(31,1);
	kout << "OOStuBs - Task 4" << endl << endl;
  log << "Inserting RotatingCursor in Scheduler" << endl;
  scheduler.insert(rotCursor);
  scheduler.insert(rotCursor2);
  log << "Inserting Counter 1 in Scheduler" << endl;
	scheduler.insert(counter1);
  log << "Inserting Counter 2 in Scheduler" << endl;
	scheduler.insert(counter2);
}

void Task4::enableCoop(){
  log << "Switching sub tasks to cooperative scheduling" << endl;
  rotCursor.enableCoop();
  rotCursor2.enableCoop();
  counter1.enableCoop();
  counter2.enableCoop();
}
