/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                        T A S K 1                                              *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "user/task1.h"
#include "device/cgastr.h"
#include "machine/keyctrl.h"

extern CGA_Stream kout;
extern Keyboard_Controller keyboard;

void Task1::setup(uint32_t magic, const ::Multiboot_Info* mbi){
 this->magic=magic;
 this->mbi=reinterpret_cast<const Multiboot_Info*>(mbi);
}

bool Task1::checkFlag(Flags flag){
  return (mbi->flags&flag);
}

void Task1::parseAndPrint(){
  //Var init
  unsigned long long ullTmp;
  
  if( magic != MULTIBOOT_BOOTLOADER_MAGIC ){
    kout << "Not booted by multiboot compliant loader" << endl;
    return;
  }
  
  kout << "flags= " << bin << mbi->flags << dec << endl;
  
  if (checkFlag(memSize))
    kout << "mem_lower = " << mbi->mem_lower
         << "KB, mem_upper = " << mbi->mem_upper 
         << "KB" << endl;
  
  if (checkFlag(bootDev))
    kout << "boot_device = " << hex << mbi->boot_device << endl;
  
  if (checkFlag(cmdLine))
    kout << "cmdline = " << (const char*)mbi->cmdline << endl;
  
  if (checkFlag(modules)) {
    kout << "mods_count = " << dec << mbi->mods_count 
         << ", mods_addr = " << hex << mbi->mods_addr << endl;
    
    Module *mod=reinterpret_cast<Module*>(mbi->mods_addr);
    for(uint32_t i=0;i < mbi->mods_count; i++) {
      kout << " mod_start = " << mod->mod_start
           << ", mod_end = " << mod->mod_end 
           << ", string = " << mod->string << endl;
      mod++;
    }
  }
  
  if (checkFlag(aOut) && checkFlag(elf)) {
    kout << "Both bits 4 and 5 are set." << endl;
    return;
  }
  
  if (checkFlag(aOut)) {
    const AOut_Symbol_Table *aout_sym = &(mbi->executable_info.aout);
    
    kout << "aout_symbol_table: tabsize = " 
         << dec << aout_sym->tabsize << endl
         << "strsize = " << aout_sym->strsize
         << ", addr = " << hex << aout_sym->addr << endl;
  }
  
  if (checkFlag(elf)) {
    const ELF_Section_Header_Table *elf_sec = &(mbi->executable_info.elf);
    
    kout << "elf_sec: num = "<< dec << elf_sec->num 
         << ", size = " << elf_sec->size << endl
        << " " << (char)192 << (char)196  << "addr = " << hex << elf_sec->addr
         << ", shndx = " << elf_sec->shndx << endl;
  }
  
  if (checkFlag(memMap)) {
    
    kout << "mmap_addr = " << hex << mbi->mmap_addr
       << ", mmap_length = " << dec << mbi->mmap_length << endl;
    
    for( const char* curr = (const char*)mbi->mmap_addr;
      curr < (const char*)mbi->mmap_addr + mbi->mmap_length ;
      curr+= ((const Memory_Map*)curr)->size + sizeof(((const Memory_Map*)curr)->size) ) {
      const Memory_Map* currEntry=reinterpret_cast<const Memory_Map*>(curr);
      
      //Symbol des "aufgeklappten Menues"
      if( (curr+((const Memory_Map*)curr)->size + sizeof(((const Memory_Map*)curr)->size))
           < ((const char*)mbi->mmap_addr + mbi->mmap_length) ){
        
        kout << " " << (char)195 << (char)196;
      }else{
        kout << " " << (char)192 << (char)196;
      }
      kout << "base_addr = " << hex << currEntry->base_addr_low;
      ullTmp = currEntry->length_low + (((unsigned long long)currEntry->length_high)<<32);
      if(ullTmp<1024)
           kout << ", length = " << dec << (unsigned long)(currEntry->length_low) << "B";
      else if(ullTmp<1024*1024)
         kout << ", length = " << dec << (unsigned long)(ullTmp/1024) << "KiB"; //zwar kB, aber KiB!
      else if(ullTmp<1024*1024*1024)
         kout << ", length = " << dec << (unsigned long)(ullTmp/(1024*1024)) << "MiB";
      else if(ullTmp<1024LL*1024*1024*1024)
         kout << ", length = " << dec << (unsigned long)(ullTmp/(1024*1024*1024)) << "GiB";
      else
         kout << ", length = " << dec << (unsigned long)(ullTmp/(1024LL*1024*1024*1024)) << "TiB";
      
      kout << ", type = " 
         << ((currEntry->type==0x1)?"ram":"reserved") << endl;
    }
  }
}

void Task1::testKout(){
  //Var init
  unsigned short x,y;
  unsigned int i;
  Colors col;
  const char acText[] = "DAS_Farbenwunder";
  
  kout << endl << "kout test:" << endl;
  kout.getpos(x,y);
  for(i=0;i<18;i++){
    if(i%6==0){
      kout.flush();
      kout.setpos(0,y+1+i/6);
    }
    kout << dec << "(" << i << ", " << hex << i << ") ";
  }
  kout << endl;
  
  //Farben ausgeben
  kout << BGColor(LIGHTGREY);
  for(i=0; i<sizeof(acText); i++){
    kout << FGColor((Colors)i) << acText[i];
    if(i==1){
      kout << BGColor(BLACK);
    }
  }
  kout << FGColor(RED) << Blink(true) << "--> DELUX <--" << Blink(false);
  for(col=BLACK; col<=WHITE; col=(Colors)(col+1)){
    if(col==DARKGREY){
      kout << Blink(true);
    }
    kout << BGColor(col) << ' ';
  }
  
  kout << FGColor(LIGHTGREY) << Blink(false) << BGColor(BLACK) << endl << endl;
}

void Task1::testKeyboard(){
  unsigned short x,y;
  kout << endl << "Keyboard test: ";
  kout.flush();
  kout.getpos(x,y);
  
  while(true){
    Key k=keyboard.key_hit();
    if(k.valid()){
      kout.setpos(x,y);
      kout << k.ascii() << " (" << (unsigned int)k.scancode() << ")   ";
      kout.flush();
      kout.setpos(x+1,y);
    }
  }
}

void Task1::action(){
  kout.clear();
/*
  kout.print("\n\n\nDas ist ein Test.");
  kout.setpos(5, 17);
  kout.print("Writing somewhere else...");
  kout.setpos(25, 3);
  kout.print("Ich schreibe munter vor mich hin,\nlalala,\nlalala");
  kout.setpos(5,10);
 // kout.print("Test");
 // kout.print(" direkt dahinter");
 // kout.setpos(0,0);
*/
  //kout << -12382;

  //kout << "OOStuBs - Task 1" << endl;

  testKout();
  
  parseAndPrint();
  
  //testKeyboard();

  kout << "Den Anfang macht die Aufgabe Task3A. Hier wird eine Methode Task3A::action() aufgerufen. Offenbar tritt dabei allerdings ein Fehler auf, denn das Programm wird mit der Ausgabe von 3 Parametern abgebrochen. Entwickeln Sie eine Strategie, wie Sie mit Hilfe des gdb die Programmzeile finden, in der der Fehler auftritt, welcher Fehlertyp generiert wird und welche Inhalte sich beim Auslösen der Exception auf dem Stack befinden."<< endl;
  kout << "Die zweite Aufgabe Task3B führt die Berechnung einer Fibunachi-Folge durch runFib(). Machen Sie sich zunächst mit der Aufrufhierarchie der Methode vertraut. Mit dem Starten des Programms wird an signifikanten Punkten die Funktion printStack() aufgerufen. Diese gibt in 32-Bit-Worten die Stackstruktur zu je vier Einheiten pro Zeile in hexadezimaler Darstellung aus." << endl;
  kout << "Es ist nun an Ihnen diesen Ausgaben entsprechende Bedeutungen zu geben. Achten Sie dabei insbesondere auf die verschiedenen Formen der Parameterübergaben zwischen den Funktionen. Insbesondere für die rekursiven Aufrufe ergibt sich ein deutliches Muster. Sie können gern den gdb hinzuziehen, um weitere Informationen zu erlangen." << endl << endl;

  kout << "Text nach dem doppeltem Zeilenumbruch..." << endl;

}
