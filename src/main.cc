/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                         M A I N                                               *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* INCLUDES */

#include "machine/multiboot.h"
#include "machine/cpu.h"
#include "device/interruptmanager.h"
#include "device/keyboard.h"
#include "device/cgastr.h"
#include "device/watch.h"
#include "device/log.h"
#include "thread/organizer.h"
#include "locking/interruptLock.h"
#include "user/task1.h"
#include "user/task2.h"
#include "user/task3A.h"
#include "user/task3B.h"
#include "user/task4.h"
#include "user/task5.h"
#include "user/task6.h"

/* MACROS */

/// \~english define the task to execute
#define USE_TASK 60

/* GLOBAL OBJECTS */

/** \brief global CPU object **/
CPU cpu;
/** \brief global Lock to prevent interrupt based concurrancy **/
InterruptLock lock;
/** \brief Log for debug output over serial connection **/
Log log;
/** \brief Scheduler of all Threads **/
Organizer scheduler;
/** \brief Display output stream **/
CGA_Stream kout;
/** \brief Interrupt handling unit **/
InterruptManager iManager;
/** \brief Keyboard input facility **/
Keyboard keyboard;
/** \brief Periodic timer used for preemption of Threads **/
Watch watch;

#if USE_TASK == 10
  /**\brief The first student task test application **/
  Task1 task1;
#elif USE_TASK == 20
  /**\brief The second student task test application **/
  Task2 task2;
#elif USE_TASK == 30
  /**\brief The third student task test application for part A**/
  Task3A task3a;
  /**\brief The third student task test application for Part B**/
  Task3B task3b;
#elif USE_TASK == 40
  /**\brief The fourth student task test application **/
  Task4 task4;
#elif USE_TASK == 50
  /**\brief The fifth student task test application **/
  Task5 task5;
#elif USE_TASK == 60
  /**\brief The fifth student task test application **/
  Task6 task6;
#endif

/* METHODS  */
/** \brief Wait for user input via keyboard to select sub task
 *
 *  \param minSubTask minimum task character
 *  \param maxSubTask maximum task character
 *
 *  \return character of the choosen sub task
 **/
bool getSubTask(char minSubTask, char maxSubTask){
  kout << "Please choose subtask [" << minSubTask << ", " << maxSubTask << "]" << endl;
  Key k;
  do{
      k=keyboard.key_hit();
  }while(!k.valid() || k.ascii()<minSubTask || k.ascii()>maxSubTask);
  return k.ascii();
}

extern "C" void kernel(uint32_t magic, const Multiboot_Info* info);

/** \brief kernel entry point
 *
 * \param magic bootloader magic value
 * \param info address of multiboot info structure
 *
 * This is the entry point of the operating system.  If this function returns
 * all interrupts will be disabled and the cpu will be halted.
 * 
 **/
void kernel(uint32_t magic, const Multiboot_Info* info){
  
  keyboard.plugin();
  watch.windup(10000);
  
#if USE_TASK == 10
  task1.setup(magic, info);
  scheduler.insert(task1);
#elif USE_TASK == 20
  scheduler.insert(task2);
  cpu.enable_int();
#elif USE_TASK == 30
  if(getSubTask('A', 'B')=='A'){
    scheduler.insert(task3a);
    cpu.enable_int();
  }
  else
    scheduler.insert(task3b);
#elif USE_TASK == 40
  if(getSubTask('A', 'B')=='A')
    task4.enableCoop();
  scheduler.insert(task4);
  cpu.enable_int();
#elif USE_TASK == 50
  scheduler.insert(task5);
  cpu.enable_int();
#elif USE_TASK == 60
  scheduler.insert(task6);
  cpu.enable_int();
#endif
  
  scheduler.start();
}
