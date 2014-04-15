/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                      O _ S T R E A M                                          *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "common/o_stream.h"

/** \brief \todo implement **/
O_Stream::O_Stream() : Stringbuffer(), fgColor(WHITE), bgColor(BLACK), blink(false), base(dec){
  /* ToDo: Insert Your Code Here */
}

/** \brief \todo implement **/
O_Stream::~O_Stream(){
  /* ToDo: Insert Your Code Here */
}

/** \brief \todo implement **/
O_Stream& O_Stream::operator << (char value) {
  /* ToDo: Insert Your Code Here */
  return *this;
}

O_Stream& O_Stream::operator << (unsigned char value) {
  return *this << (char)value;
}

O_Stream& O_Stream::operator << (char* value) {
  return *this << (const char*)value;
}

/** \brief \todo implement **/
O_Stream& O_Stream::operator << (const char* value) {
  /* ToDo: Insert Your Code Here */
  return *this;
}

O_Stream& O_Stream::operator << (short value) {
  return *this << (long)value;
}

O_Stream& O_Stream::operator << (unsigned short value) {
  return *this << (unsigned long)value;
}


O_Stream& O_Stream::operator << (int value) {
  return *this << (long)value;
}


O_Stream& O_Stream::operator << (unsigned int value) {
  return *this << (unsigned long)value;

}

/** \brief \todo implement **/
O_Stream& O_Stream::operator << (long value) {
  /* ToDo: Insert Your Code Here */
  return *this;;
}

/** \brief \todo implement **/
O_Stream& O_Stream::operator << (unsigned long value) {
  /* ToDo: Insert Your Code Here */
  return *this;
}

/** \brief \todo implement **/
O_Stream& O_Stream::operator << (void* value) {
  /* ToDo: Insert Your Code Here */
  return *this;
}

O_Stream& O_Stream::operator << (FGColor color){
  flush();
  fgColor = color.color;
  setAttributes(fgColor, bgColor, blink);
  return *this;
}


O_Stream& O_Stream::operator << (BGColor color){
  flush();
  bgColor = color.color;
  setAttributes(fgColor, bgColor, blink);
  return *this;
}


O_Stream& O_Stream::operator << (Blink blink){
  flush();
  this->blink = blink.blink;
  setAttributes(fgColor, bgColor, this->blink);
  return *this;
}

/** \brief \todo implement **/
O_Stream& endl (O_Stream& os) {
  /* ToDo: Insert Your Code Here */
  return os;
}


O_Stream& bin (O_Stream& os) {
  os.base = O_Stream::bin;
  return os;
}


O_Stream& oct (O_Stream& os) {
  os.base = O_Stream::oct;
  return os;
}


O_Stream& dec (O_Stream& os) {
  os.base = O_Stream::dec;
  return os;
}


O_Stream& hex (O_Stream& os) {
  os.base = O_Stream::hex;
  return os;
}

O_Stream& O_Stream::operator << (O_Stream& (*f) (O_Stream&)) {
  return f(*this);
}
