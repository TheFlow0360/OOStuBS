#include "user/task5.h"

#include "object/keyboard.h"
#include "object/kout.h"
#include "object/lock.h"
#include "object/log.h"
#include "locking/scopedLock.h"

Task5::Task5(){
}

void Task5::action(){
  jobs.registerJob(counter1, "Counter-1");
  jobs.registerJob(counter2, "Counter-2");
  jobs.registerJob(rotCursor, "Rotating-Cursor");

  while(true){
    unsigned short x,y;
    lock.lock();
    kout.clear();
	  kout.setpos(31,1);
	  kout << "OOStuBs - Task 5" << endl;
    kout.setpos(CMD_X, CMD_Y);
    kout << "oostubs:$ ";
    kout.flush();
    kout.getpos(x,y);
    cmdLine.clear();
    lock.unlock();
    while(!cmdLine.finished()){
      Key k = keyboard.getkey();
      ScopedLock scopedLock(lock);
      if(k.scancode() == Key::scan::del){
        kout.setpos(x-1,y);
        kout << " ";
        kout.flush();
        kout.setpos(x-1,y);
        cmdLine.erase();
      }
      kout.setpos(x,y);
      kout << k.ascii();
      log << k.ascii() << endl;
      kout.flush();
      kout.getpos(x,y);
      cmdLine.feed(k.ascii());
    }
    const char* arg;
    switch(cmdLine.result(&arg)){
      case(Parser::start):   jobs.start(arg);
                             break;
      case(Parser::kill):    jobs.stop(arg);
                             break;
      case(Parser::list):    {
                               ScopedLock scopedLock(lock);
                               kout << "jobs: " << endl << jobs;
                             }
                             break;
      case(Parser::help):
      case(Parser::unknown): {
                               ScopedLock scopedLock(lock);
                               kout << "commands: " << endl << cmdLine;
                             }
                             break;
    };
    keyboard.getkey();
  }
}
