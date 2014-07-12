/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                            P I C                                              * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "machine/pic.h"
#include "machine/io_port.h"
#include "object/cpu.h"


/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */

PIC::PIC() : ctrl_1(0x20), ctrl_2(0xa0), mask_1(0x21), mask_2(0xa1){
  
  ctrl_1.outb(0x11); //Initialisierung + ICW4 kommt
  ctrl_2.outb(0x11);
  
  mask_1.outb(32);  //Start Interrupt Nummer (IRC 0)
  mask_2.outb(40);
  
  mask_1.outb(4);   //IRQs, auf denen Slave gemappt sind; Bitmaske
  mask_2.outb(2);   //IRQ, an dem Slave an Master geht; Zahl
  
  mask_1.outb(3);   //0.Bit -> "für PC"; 1. Bit automatisches Ack
  mask_2.outb(3);
  
  mask_1.outb(0xFB);  // Bitmaske, alle aus, außer IRQ2 (Slave)
  mask_2.outb(0xFF);

}

PIC::~PIC(){
  mask_1.outb(0xFF);
  mask_2.outb(0xFF);
}

void PIC::allow(Interrupts interrupt){
  if(interrupt>=timer && interrupt<=parallelport && interrupt!=pic2){
    //von PIC1 Maske holen
    unsigned char mask1 = mask_1.inb();
    //Bit aendern
    mask1 &= ~(1 << (interrupt-timer));
    //zurückschreiben
    mask_1.outb(mask1);
  }

  if(interrupt>=rtc && interrupt<=ata2){
    //von PIC2 Maske holen
    unsigned char mask2 = mask_2.inb();
    //Bit aendern
    mask2 &= ~(1 << (interrupt-rtc));
    //zurückschreiben
    mask_2.outb(mask2);
  }
}

void PIC::forbid(Interrupts interrupt){
  if(interrupt>=timer && interrupt<=parallelport && interrupt!=pic2){
    //von PIC1 Maske holen
    unsigned char mask1 = mask_1.inb();
    //Bit aendern
    mask1 |= 1 << (interrupt-timer);
    //zurückschreiben
    mask_1.outb(mask1);
  }

  if(interrupt>=rtc && interrupt<=ata2){
    //von PIC2 Maske holen
    unsigned char mask2 = mask_2.inb();
    //Bit aendern
    mask2 |= 1 << (interrupt-rtc);
    //zurückschreiben
    mask_2.outb(mask2);
  }
}

void PIC::ack(Interrupts interrupt){
  //falls PIC2 dann beide
  if(interrupt>=rtc && interrupt<=ata2){
    ctrl_2.outb(0x20);
    ctrl_1.outb(0x20);
  }
  if(interrupt>=timer && interrupt<=parallelport && interrupt!=pic2)
    ctrl_1.outb(0x20);
}
