/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                 S T R I N G B U F F E R                                       *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "common/strbuf.h"
#include "machine/mem.h"

Stringbuffer::Stringbuffer(){
  //increasing buffer size by 2 for /0 and (if needed) /n
  buffer = (char *)Memory::alloc(BUFFER_SIZE + 2);
  pos = buffer;
}

Stringbuffer::~Stringbuffer(){
  Memory::free(buffer, BUFFER_SIZE);
}

void Stringbuffer::put (char c) {
  if (pos >= buffer + BUFFER_SIZE) {
    // flush when buffer overflow imminent
    this->flush();
    pos = buffer;   // reset position-counter
  }
  *pos = c; // add character at free space in buffer
  ++pos; // increase the position-counter
}
