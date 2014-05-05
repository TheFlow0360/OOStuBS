/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                       K E Y B O A R D                                         * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __keyboard_include__
#define __keyboard_include__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "machine/keyctrl.h"
#include "common/interrupthandler.h"
 
/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */
/** 
 * \~german
 * \brief Treiber für die Tastatur, incl. Interruptunterstützung.
 * 
 * Diese Klasse ist von Gate abgeleitet und implementiert die Interruptroutine der Tastatur.
 * 
 * \~english
 * \brief %Keyboard driver with interrupt support
 *
 * This class is a subclass of Gate and implements the interrupt routine used 
 * for the keyboard.
 */
class Keyboard : public Keyboard_Controller, public InterruptHandler  {
  public:    
    /** 
     * \~german
     * \brief aktiviert den Interruptmechanismus für die Tastatur
     * 
     * Die Methode aktiviert die Keyboard Interrupts. Nach dem Aufruf werden die Interrupts, 
     * welche durch die Tastatur generiert werden, weitergereicht. Die Behandlung ist dann 
     * mit trigger möglich.
     * 
     * \~english
     * \brief enable the interrupt mechanism of the keyboard
     * 
     * Method plugin() enables all keyboard interrupts. After calling plugin()
     * interrupts activated by the keyboard are recognised.
     */
    void plugin ();
    
    /** 
     * \~german
     * \brief einen auftretenden Tastaturinterrupt behandeln
     * 
     * Tritt ein Interrupt für die Tastatur auf, so soll diese Funktion aufgerufen werden.
     *
     * In Aufgabe 2 soll die Funktion das eingegeben Zeichen an der festen
     * Position KEYBOARD_Y, KEYBOARD_X auf dem Bildschirm ausgegeben werden.
     *
     * \~english
     * \brief handle keyboard interrupt
     *
     * On each keyboard interrupt emitting a valid key, the key shall be
     * printed to the display at position KEYBOARD_Y, KEYBOARD_X
     *
     */
    virtual void trigger ();
};

#endif
