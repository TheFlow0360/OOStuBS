/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                               I N T E R R U P T _ M A N A G E R                               * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __interrupt_manager_include__
#define __interrupt_manager_include__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include <common/interruptstorage.h>
#include <machine/pic.h>

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */
/** 
 * \~german
 * \brief Administrationseinheit für die Interruptweitergabe
 * 
 * Diese Klasse abstrahiert die Verwaltung und Ausführung von Interrupts. Sie ermöglicht dem
 * System für jeden Hardware- und jeden Softwareinterrupt eine entsprechende 
 * Behandlungsroutine zu vergeben und auszuführen.
 * 
 * \~english
 * \brief Interrupt forwarding administration unit
 *
 * This class is an abstraction of the administration and exeuction of interrupts. It
 * enables the system to define an appropriate handling routine for every hard
 * and software interrupt and execute it.
 **/
 class InterruptManager : public InterruptStorage, public PIC{
  public:
    /** \brief Assign a handler to an interrupt
     *  
     *  This method assign a handler object to an interrupt and activates the interrupt.
     *
     *  \param iNum the interrupt's number
     *  \param handler a reference to the Handler object
     **/
    void assign(int iNum, InterruptHandler& handler);
 };

#endif
