/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                          P A N I C                                            * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __panic_include__
#define __panic_include__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include <common/interrupthandler.h>

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */
/** 
 * \~german
 * \brief Standardinterruptbehandlungsroutine
 * 
 * Diese Klasse, als Unterklasse von Gate, implementiert eine Standardroutine zur 
 * Behandlung von Interrupts. Sie soll immer dann genommen werden, wenn ein 
 * unbekannter oder nicht-registrierter Interrupt aufgetreten ist.
 * 
 * \~english
 * \brief Default interrupt handler
 *
 * This class is a subclass of Gate and implements a standard interrupt routine
 * used as default for unknown/registered interrupts.
 */
class Panic  : public InterruptHandler {
  private:
    int interruptNr = -1;

  public:
    /**  
     * \~german
     * \brief handelt unbekannte oder nicht-registrierte Interrupts
     * 
     * Zum Debuggen sollte die Nummer des Interrupts ausgegeben werden und die %CPU 
     * für immer angehalten werden.
     * 
     * \~english
     * \brief handle unknown/unregistered interrupt 
     *
     * For debug purposes the cpu will be halted if an unknown interrupt
     * occurs. Additionally the number of the interrupt shall be printed.
     **/
    virtual void trigger();
    
    /**
     * \brief Sets the currently handled interrupt
     * \brief param iNum the currently handled interrupt's number
     **/
    void currentInterrupt(int iNum);
};

#endif
