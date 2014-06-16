/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    S E R I A L                                                *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __serial_include__
#define __serial_include__

/* INCLUDES */

#include <machine/io_port.h>

/* CLASSES */

class Serial{
  private:
    static const unsigned short address = 0x3F8;
    static const unsigned int maxBaudRate = 115200;

    struct ControlByte{
      enum WordSize{
        _5Bits = 0,
        _6Bits = 1,
        _7Bits = 2,
        _8Bits = 3
      } size : 2;
      enum StopBits{
        One = 0,
        Two = 1
      } stopBits : 1;
      enum Parity{
        none = 0,
        odd = 1,
        even = 2,
        mark = 3,
        space = 4
      } parity : 3;
      bool breakEnable : 1;
      bool divisorAccess : 1;
    };

    struct StatusByte{
      bool dataReady : 1;
      bool overrunError : 1;
      bool parityError : 1;
      bool framingError : 1;
      bool breakInterrupt : 1;
      bool transmitBufferEmpty : 1;
      bool dataEmpty : 1;
      bool FIFOError : 1;
    };

    IO_Port transmitPort;
    IO_Port divisorLowPort;
    IO_Port divisorHighPort;
    IO_Port controlPort;
    IO_Port statusPort;

    StatusByte status();
    void control(ControlByte controlByte);
    ControlByte control();
    unsigned int baudRate(unsigned int divisor);
    unsigned int baudRate();
    void transmit(char c);

  public:
    /** 
     * \brief Constructor
     */
    Serial();
    
    /** 
     * \brief Destructor 
     */
    ~Serial();

    /** 
     * \~german
     * \brief gibt eine Zeichenkette an der aktuellen Position aus
     * 
     * Als Attribute werden die hinterlegten, aktuellen, Standardwerte verwendet.
     * 
     * @param string 
     *    Zeichenkette, die ausgegeben werden soll
     * @param n 
     *    Anzahl an Zeichen, die von \c string ausgegeben werden soll
     * 
     * 
     * \~english
     * \brief print a string to the current position
     * 
     * @param string 
     *    string of characters to be displayed
     * @param n 
     *    number auf characters in string
     */
    void print(const char* string, unsigned int n);
};

#endif
