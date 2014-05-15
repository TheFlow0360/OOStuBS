/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                       T A S K 2                                               *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "user/task2.h"

#include "object/kout.h"
#include "object/keyboard.h"

Task2::Task2(){
  kout.setpos(1,31);
  kout << "OOStuBs - Task 2" << endl << endl;
  
  keyboard.plugin();
}

void Task2::action(){
  unsigned short x,y;
  unsigned char i=0;
  
  kout.getpos(x,y);
  while(1){
    kout.setpos(x,y);
    for(unsigned short j=0;j<39;j++){
      kout << "-";
    }
    kout.flush();
    
    switch(i++%4)    {
      case(0): kout << "//";
           break;
      case(1): kout << "--";
           break;
      case(2): kout << "\\\\";
           break;
      case(3): kout << "||";
           break;
    }
    for(unsigned short j=0;j<39;j++){
      kout << "-";
    }
    kout << endl;
  }
}
