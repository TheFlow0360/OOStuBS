/*---------------------------------------------------------------------------*
 * Technical Computer Science II                                             *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                         T A S K 5                                         *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#ifndef __task5_header__
#define __task5_header__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */

#include "user/task4.h"

#include "user/jobManager.h"
#include "user/parser.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */

/** \brief Fifth test Application 
 *
 * This application shows the usage of blocking system calls to synchornize
 * I/O-operations with individual threads.
 *
 **/
class Task5 : public Task4{
  private:
    JobManager jobs;
    Parser     cmdLine;
  public:
  /** \brief Default Constructor **/
	  Task5();
  /** \brief Functionality of the fifth test application
   *
   * Registers the 3 applications inherited from Task4: Counter1, Counter2 and RotatingCursor and starts the shell
   * 
   **/
	  virtual void action();
};

#endif
