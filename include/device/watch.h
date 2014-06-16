/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                          W A T C H                                            * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __watch_include__
#define __watch_include__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "common/interrupthandler.h"
#include "machine/pit.h"


/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * \~english
 * \brief Handler for periodic timer interrupts
 * 
 * This class is a subclass of Gate and implements the interrupt routine used 
 * for the clock.
 */
class Watch : public PIT, public InterruptHandler {
public:
  /**
   * \~english
   * \brief Enable the clock interrupt and its handling
   *
   * \param us interval between interrupts caused by the time-interrupt in 
   *           microsecounds
   *
   * Method windup() is used to enable the clock interrupt. After calling 
   * windup() the clock interrupt is triggered in the defined interval.
   */
  void windup(unsigned int us);

  /**
   * \~english
   * \brief Handling method of the clock interrupt
   *
   * Handles incoming clock interrupts. Issues a preemtion of the currently
   * running thread and schedules the next one.
   *
   **/
  virtual void trigger();
};

#endif
