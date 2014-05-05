/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                            P I C                                              * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __pic_include__
#define __pic_include__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "machine/io_port.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */
/** 
 * \~german
 * \brief Treiber für den %PIC (Programmable Interrupt Controller)
 * 
 * Der %PIC (programmierbarer Interruptkontroller) ermöglicht es dem System bestimmte Interrupts 
 * bzw. unterbrechungen zu erlauben oder zu verbieten. Wurden die Interrupts global aktiviert,
 * so legt der PIC fest, welche Interrupts weitergreicht werden um vom System behandelt zu werden. 
 * Es ist wichtig,d ass Interrupts nur behandelt werden, falls der entsprechende Interrupt erlaubt 
 * wurde und die Behandlung im allgemeinen aktiviert ist - siehe dazu die Klasse \ref CPU.
 * 
 * Der %PIC basiert auf Intels 8259 Chip und besteht aus einem Master-Slave %PIC-System.
 * Heutzutage werden sie meist nur "emuliert". Verwendet wird mittlerweile APIC, welcher für 
 * ein Mehrkernbetrieb notwendig ist.
 *
 * \~english 
 * \brief Driver for Programmable Interrupt Controller
 *
 * The %PIC or Programmable Interrupt Controller enables the system to
 * allow/forbid interrupts. The %PIC keeps track of currently active as well as
 * allowed interrupts of the system. It is important that interrupts will only
 * be handled if the interrupt has been allowed and if the handling of
 * interrupts is enabled (see class \ref CPU). 
 *
 */

class PIC{
  public:
    /** 
     * \~german
     * \brief externe Interruptquellen
     * 
     * Die folgende Liste gibt die oft genutze Liste der Interrupts an. Sie ist nicht für alle
     * Computer gleich, da sie sich danach richtet, welche Hardware an den entsprechenden 
     * Interrupteingang vom PIC angeschlossen ist.
     * 
     * Die ersten acht Einträge stammen vom ersten PIC (Master), 
     * die letzten acht vom zweiten PIC (Slave).
     * 
     * \~english
     * \brief External interrupt sources
     */
    enum Interrupts{
      timer         = 32,  ///< \~german Intervallzähler (PIT) \~english timer (PIT)
      keyboard      = 33,  ///< \~german Tastaturkontroller \~english keyboard controller
      pic2          = 34,  ///< \~german Anschluss von Slave-PIC \~english second PIC
      serial2       = 35,  ///< \~german RS-232 Port 2 und 4 \~english RS-232 port 2 and 4
      serial1       = 36,  ///< \~german RS-232 Port 1 und 3 \~english RS-232 port 1 and 3
      soundcard     = 37,  ///< \~german Soundkarte oder LPT 2 \~english sound card or LPT 2
      floppy        = 38,  ///< \~german Diskettenkontroller \~english floppy disc controller
      parallelport  = 39,  ///< \~german LPT 1 und unechter Interrupt \~english LPT 1
      rtc           = 40,  ///< \~german Echtzeituhr vom CMOS (RTC) \~english real time clock
      misc          = 41,  ///< \~german verschiedene \~english miscellaneous
      ata4          = 42, ///< \~german vierter ATA(PI)/IDE \~english fourth ATA(PI)/IDE
      ata3          = 43, ///< \~german dritter ATA(PI)/IDE \~english third ATA(PI)/IDE
      secondps2     = 44, ///< \~german zweiter Tastaturkontrolleranschluss \~english second keyboard controller port
      fpu           = 45, ///< \~german Gleitkommazahleneinheit \~english floating point unit
      ata1          = 46, ///< \~german erster ATA(PI)/IDE \~english first ATA(PI)/IDE
      ata2          = 47  ///< \~german zweiter ATA(PI)/IDE und unechter Interrupt\~english second ATA(PI)/IDE
    };
    
    /** 
     * \~german
     * \brief Standardkonstruktor
     * 
     * Er initialisiert den PIC und maskiert alle einkommenden Interrupt, damit wird keiner  an
     * die %CPU durchgereicht. Danach aktiviert er die globale Interruptverarbeitung der CPU und ermöglicht das auftreten und ausgeben von Exceptions.
     * 
     * \~english
     * \brief Default Constructor
     *
     * Setting up the PIC and masking all incoming interrupt channels. Afterwards activates the global interrupt handling of the CPU enabling the occurence and printing of exceptions.
     */
    PIC();

    /** \brief Destructor globally disabling interrupts **/
    ~PIC();
  
    /** 
     * \~german
     * \brief Erlaubt einen speziellen Interrupt von einem Peripheriegerät
     * 
     * \~english
     * \brief allow a specific hardware interrupt of a peripheral device
     *
     * \param interrupt 
     *   interrupt to be allowed
     */
    void allow(Interrupts interrupt);
    
    /** 
     * \~german
     * \brief verbietet einen speziellen Interrupt eines Peripheriegerätes
     * 
     * \~english
     * \brief forbid a specific hardware of a peripheral device
     *
     * \param interrupt 
     *   The interrupt to be deactivated
     */
    void forbid(Interrupts interrupt); 
    
    /**
     * \~german
     * \brief sendet ein "Acknowledgement" eines ausstehenden Interrupts
     * 
     * Die Funktion bestätigt die Behandlung eines aufgetretenen Interrupts. Dies sagt dem 
     * PIC, dass der letzte gemeldete Interrupt abgearbeitet wurde
     * 
     * \~english
     * \brief acknowledge the handling of a pending interrupt
     *
     * Acknowledge an occured interrupt. This tells the PIC that his last
     * interrupt has been handled. This Method has to be called before the cpu is
     * allowed to handle any new interrupts. If an interrupt is not acknowledged
     * the same interrupt is called again and again.
     * 
     * If an interrupt accures at the slave %PIC than also the first one has to be acknowledged.
     * 
     * \param interrupt
     *   The interrupt to acknowledge
     */
    void ack(Interrupts interrupt);
};

#endif
