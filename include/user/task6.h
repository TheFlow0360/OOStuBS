/*---------------------------------------------------------------------------*
 * Technical Computer Science II                                             *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                         T A S K 5                                         *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#ifndef __task6_header__
#define __task6_header__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */

#include "user/task4.h"

#include "user/jobManager.h"
#include "user/parser.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */

/** \brief Sixth test Application 
 *
 * This application shows the usage of blocking system calls to synchornize
 * I/O-operations with individual threads.
 *
 **/
class Task6 : public Task4{
  private:
    JobManager jobs;
    Parser     cmdLine;
  public:
  /** \brief Default Constructor **/
	  Task6();
  /** \brief Functionality of the fifth test application
   *
   * Registers the 3 applications inherited from Task4: Counter1, Counter2 and RotatingCursor and starts the shell
   * 
   **/
	  virtual void action();
	  
/** \brief %Moving symbol application
 *
 * This application creates a symbol moving from left to right and backwards
 **/
class Kitt : public Application
{
	private:
		/**\brief internal state to save current symbol **/
		unsigned char i;
		unsigned short x, y;
        bool coop;
        
        void enableCoop(){coop=true;}
	public:
		/** \brief Default constructor
		 *
		 * Setting the start symbol
		 **/
		Kitt(unsigned short x, unsigned short y);

		/** \brief start outputting the symbol
		 *
		 * This method implementes the Kitt-application
		 **/
		virtual void action();
    friend class Task6;
};
	  	/** \brief Application for a oscilating  **/
		Kitt kitt;  
};
#endif
