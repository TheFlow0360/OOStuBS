/*---------------------------------------------------------------------------*
 * Operating Systems I                                                       *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                                  P I T                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#include "machine/pit.h"

PIT::PIT(){
	pcb.countType=binary;
	pcb.mode=rateGen;
	pcb.rwType=lowThenHigh;
	pcb.counter=counter0;
}

PIT::~PIT(){

}

void PIT::interval(unsigned short us){
	IO_Port value(counter0Port);
	IO_Port ctrl(ctrl0Port);
	if(us>maxUS)
		us=maxUS;

	unsigned long temp = us * 1000;
	temp/=timestep;

	ctrl.outb(pcb.ctrlByte);
	value.outb(temp&0xFF);
	value.outb((temp>>8)&0xFF);

	currIntervall=us;
}

unsigned short PIT::interval(){
	return currIntervall;
}
