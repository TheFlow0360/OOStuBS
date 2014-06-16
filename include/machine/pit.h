/*---------------------------------------------------------------------------*
 * Operating Systems I                                                       *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                                  P I T                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#ifndef __pit_include__
#define __pit_include__

#include "stdint.h"
#include "machine/io_port.h"

/** 
 * Class PIT implements the 'Programmable Interval Timer' used to programm the
 * timer interrupt.
 */
class PIT { 
private:
	enum Parameters
	{
		timestep = 838, 				/**< time of one tick in nanoseconds **/
		maxUS = 0xFFFFUL*timestep/1000	/**< max timer interval in microseconds **/
	};

	enum Ports{
		counter0Port=0x40,
		counter1Port=0x41,
		counter2Port=0x42,
		ctrl0Port=0x43,
		counter3Port=0x48,
		counter4Port=0x49,
		counter5Port=0x4A,
		ctrl1Port=0x4B
	};

	enum CountTypes
	{
		binary,
		bcd
	};

	enum CountModes
	{
		intOnTerminal,
		hwOneShot,
		rateGen,
		squareWave,
		swStrobe,
		hwStrobe
	};

	enum RWTypes
	{
		latch,
		lowOnly,
		highOnly,
		lowThenHigh
	};

	enum Counters
	{
		counter0,
		counter1,
		counter2
	};

	union PitControlByte
	{
		struct 
		{
			CountTypes countType : 1;
			CountModes mode : 3;
			RWTypes rwType : 2;
			Counters counter : 2;
		};
		uint8_t ctrlByte;
	} pcb;

	unsigned short currIntervall;

public:
  /**
   * Default constructor initialiseing the timer interval.
   */
  PIT();

  /**
   * Default constructor initialiseing the timer interval.
   */
  virtual ~PIT();
  
  /**
   * Method 'interval()' returns the timer interval of the PIT.
   *
   * @return the timer interval of the PIT as int value.
   */
  unsigned short interval ();
  
  /**
   * Method 'interval()' implements the programming of the timer interrupt using
   * IO_Ports.
   * 
   * @param us timer interval (int)
   */
  void interval(unsigned short us); 
};

#endif
