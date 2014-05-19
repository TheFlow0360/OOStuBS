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
#include "config.h"


/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */

void PIC::updateMask()
{
  IO_Port  mask_1(MasterMask), mask_2(SlaveMask);
  mask_1.outb((unsigned char) interruptMask);
  mask_2.outb((unsigned char) (interruptMask >> 8));
}

PIC::PIC() {
  IO_Port ctrl_1(MasterCmd), ctrl_2(SlaveCmd), mask_1(MasterMask), mask_2(SlaveMask);

  interruptMask = ~0u;

  ctrl_1.outb(0x11);
  ctrl_2.outb(0x11);
  
  mask_1.outb(32);
  mask_2.outb(40);
  
  mask_1.outb(4);
  mask_2.outb(2);
  
  mask_1.outb(3);
  mask_2.outb(3);
  
  mask_1.outb(0xFB);
  mask_2.outb(0xFF);

  cpu.enable_int();
}

PIC::~PIC(){
  cpu.disable_int();
}

void PIC::allow(Interrupts interrupt){
  interruptMask &= ~(1u << ((unsigned int)interrupt - MIN_INTERRUPT_NUMBER));     // remove corresponding bit
  updateMask();
}

void PIC::forbid(Interrupts interrupt){
  interruptMask |= 1u << ((unsigned int)interrupt - MIN_INTERRUPT_NUMBER);        // set corresponding bit
  updateMask();
}

void PIC::ack(Interrupts interrupt){
  IO_Port ctrl_1(MasterCmd), ctrl_2(SlaveCmd);

  // notify that interrupt was handled
  ctrl_1.outb(NOTIFYINTERRUPTHANDLED);
  // notfiy slave too, if needed
  if (interrupt > 7)
    ctrl_2.outb(NOTIFYINTERRUPTHANDLED);
}
