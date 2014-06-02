#include "user/analyse.h"
#include "common/o_stream.h"
#include "object/kout.h"

O_Stream& printFormatted(void* value){
  unsigned long test=(unsigned long)value;
  int toFill=2*sizeof(void*);
  if(!test)toFill--;
  while(test){
    toFill--;
    test>>=4;
  }
  while(toFill){
    kout << ' ';
    toFill--;
  }
  return kout << hex << value;
}

void analyseException(unsigned short slot, void** esp){
  //Ausgabe, was passiert ist
  kout << endl;
  kout << "analyseException(" << slot << ", " << esp << ") called" << endl;
}

void analyseProcedureStack(void** esp, const char* function){
  //Ausgabe, was passiert ist
  kout << endl;
  kout << function << "(" << esp << ") called" << endl;
  
  /* * * * * * * * * * * * * * * * * * *\
  # Start ToDo-Bereich                  #
  \* * * * * * * * * * * * * * * * * * */
  //TODO Analyse-Ausgaben hier hin
  int i, k;
  bool bGoOn;
  
  kout << "Stack:" << endl;
  bGoOn         = true;
  for(i=0; bGoOn && i<20; i++){
    kout << (int*)(esp)+ i*4;
    kout << "  ";
    for(k=0; k<4 && bGoOn; k++){
      //Abbruchbedingung
      bGoOn = (esp[i*4+k]!=(void*)0xEEEEEEEE);
      
      //falls kein Abbruch, weiter
      if(bGoOn){
        printFormatted(esp[i*4+k]) << " ";
      }
    }
    if(k==4){
      kout << endl;
    }
  }
  //Ende ausgeben
  if(!bGoOn){
    //zu weite Zaehlung korrigieren
    i--;
    k--;
    //ausgeben
    if(k!=0){
      kout << "  ";
    }
    printFormatted(esp[i*4+k])   << " ";
    printFormatted(esp[i*4+k+1]) << " ";
    printFormatted(esp[i*4+k+2]) << " ";
    printFormatted(esp[i*4+k+3]) << endl;
  }
  kout.flush();
  kout << dec;
  
  /* * * * * * * * * * * * * * * * * * *\
  #  Ende ToDo-Bereich                  #
  \* * * * * * * * * * * * * * * * * * */
} 
