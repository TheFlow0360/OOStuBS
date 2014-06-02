/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                      T A S K 3 A                                              * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "user/task3A.h"

#include "object/kout.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                   FUNCTIONS                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
Task3A::Task3A() : Application(){
  kout.setpos(31,1);
  kout << "OOStuBs - Task 3A" << endl << endl;
}

Task3A::~Task3A(){}


/** \brief first part of task 3
 * 
 * <hr>
 * <h2>Ausgabenstellung</h2> 
 * 
 * In dieser Teil-Aufgabe geht es um die Analyse eines Prozedurestacks für eine Hardware-Exception.
 * Diese funktion produziert einen Fehler. Ausgehend davon die Funktion \ref exception aufgerufen. Sie dient der Analyse.
 * 
 * Welcher Fehler ist aufgetreten?
 * In welcher cc-Datei, in welcher Zeile ist der Fehler aufgetreten? Der GDB-Befehl 
 * "l *[Adresse]" könnte sich dafür als nützlich erweisen.
 * Woran könnte es liegen, dass dieser Fehler aufgetreten ist?
 * 
 * Wie ist der Stack bei einer x86 CPU-Exception normalerweise aufgebaut? 
 * Welche Daten befinden sich auf diesem in welcher Reihenfolge?
 * Was sind traps, faults und was aborts? Worin unterscheiden sie sich?
 * 
 * <hr>
 * 
 */
void Task3A::action(){
  asm("ud2");
  unsigned int i=20;
  while(i){
    kout << "now: "  << 1000/--i << endl;
  }
}
