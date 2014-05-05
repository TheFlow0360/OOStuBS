/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                I N T E R R U P T _ H A N D L E                                * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __interrupt_handler_include__
#define __interrupt_handler_include__

/** 
 * \~german
 * \brief Basisklasse für die Interruptbehandlung
 * 
 * Mit Hilfe dieser abstrakten Basisklasse können sich Geräte beim I_Man für die Behandlung von spezifischen Interrupts registrieren. Jede Unterklasse muss die Funktion \ref trigger() mit den jeweiligen, gewünschten 
 * Verhalten implementieren.
 * 
 * \~english
 * \brief Interrupt handling base class
 *
 * Superclass of for registration with I_Man to handle interrupts. Every
 * subclass has to implement method trigger() with appropriated behavior.
 **/
class InterruptHandler {
  public:
    /** 
     * \~german
     * \brief abstrakte Funktion zur Interruptbehandlung
     * 
     * Tritt ein bestimmter Interrupt auf, so wird diese Funktion der entsprechenden 
     * Unterklasse aufgerufen. Die Ausführung ist asynchron zu den anderen Anweisungen 
     * des Betriebssystem.
     * Da es verschiedene Interrupts gibt, die auch unterschiedliches Verhalten erfordern, 
     * müssen mehrere Unterklassen angelegt werden, je eine pro gewünschten Interrupt. Alle 
     * anderen Interrupts können auf eine einzige, weitere Unterklasse gelegt werden.
     * 
     * \param slot Die Nummer der Interrupts, der gerade behandelt wird.
     *
     * \~english
     * \brief interrupt handling method
     *
     * This method is called after an interrupt occured. It is executed 
     * asynchronous to other activities of the operation system. To enable 
     * different behavior according to the occured interrupt this method has to 
     * be implemented in a subclasses of Gate.
     **/
    virtual void trigger() = 0;
};

#endif
