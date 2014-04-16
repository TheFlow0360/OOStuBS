/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                 S T R I N G B U F F E R                                       *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "common/strbuf.h"

Stringbuffer::Stringbuffer(){
  this->pos = buffer;
}

Stringbuffer::~Stringbuffer(){
}

void Stringbuffer::put (char c) {
  if(pos >= buffer + BUFFER_SIZE){
    this->flush();
    pos = buffer;
  }
  *pos = c;
  ++pos;
}
