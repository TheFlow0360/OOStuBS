/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                      T A S K 3 B                                              * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "user/task3B.h"
#include "user/analyse.h"

#include "object/kout.h"
#include "object/cpu.h"
#include "object/keyboard.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                GLOBAL VARIABLES                 #
\* * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    FUNCTIONS                    #
\* * * * * * * * * * * * * * * * * * * * * * * * */
Task3B::Task3B() : Application(){
  kout.setpos(31,1);
  kout << "OOStuBs - Task 3B" << endl << endl;
}

Task3B::~Task3B(){}

void printStack(const char* func){
  void** esp;
  asm("lea 8(%%ebp), %0"
      :"=r"(esp));
  analyseProcedureStack(esp, func);
  Key k;
  do{
    k=keyboard.key_hit();
  }while(!k.valid() && k.ascii() != ' ');
}

unsigned int runFib(unsigned int fib_1, unsigned int fib_2, unsigned int n){
  printStack(__PRETTY_FUNCTION__);
  if(n)
    return runFib(fib_1+fib_2, fib_1, n-1);
  else 
    return fib_1;
}

unsigned int fib(unsigned int n){
  printStack(__PRETTY_FUNCTION__);
  unsigned int value = runFib(1,0,n-1);
  printStack(__PRETTY_FUNCTION__);
  return value;
}

void doTask3BAction(unsigned int* ende){
  
  printStack(__PRETTY_FUNCTION__);
  unsigned int n=5*(ende[1]/0x11111111); //damit keine "unused variable ende"-Warnung kommt
  
  kout << "Fibonacci(" << n << "): " << fib(n) << endl;
}

void Task3B::action(){
  //Var init
  unsigned int ende[]={0xEEEEEEEE, 0x11111111, 0xDDDDDDDD, 0xEEEEEEEE};
  
  doTask3BAction(ende);
}
