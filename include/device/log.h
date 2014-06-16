/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                          L O G                                                *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __log_include__
#define __log_include__

#include "common/o_stream.h"
#include "machine/serial.h"

/** 
 * \brief Logging facility for debug messages
 *
 * Logs passed data to serial output, iof available.
 */
class Log : public O_Stream, public Serial {
  public:
    /** 
     * \brief flush the content of the internal buffer
     *
     * It is called automaticaly as soon as the buffer is full or if a newline is
     * encountered.
     **/
    virtual void flush();
    
    /**
     * \brief does nothing, since coloring is not available over the serial console
     */
    virtual void setAttributes(int fgColor, int bgColor, bool blink);
    
};

#endif
