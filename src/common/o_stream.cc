/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                      O _ S T R E A M                                          *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "common/o_stream.h"
#include "common/strutils.h"

O_Stream::O_Stream() : Stringbuffer(), fgColor(LIGHTGREEN), bgColor(BLACK), blink(false), base(dec){}

O_Stream::~O_Stream(){}

O_Stream& O_Stream::operator << (char value) {
  this->put(value);
  return *this;
}

O_Stream& O_Stream::operator << (unsigned char value) {
  return *this << (char)value;
}

O_Stream& O_Stream::operator << (char* value) {
  return *this << (const char*)value;
}

O_Stream& O_Stream::operator << (const char* value) {
  int i = 0;
  char tmp = value[i];
  while (tmp != '\0') {
    this->put(tmp);
    i++;
    tmp = value[i];
  }
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

O_Stream& O_Stream::operator << (long value) {
  return (*this << StrUtils::longToString(value, this->base));
}

O_Stream& O_Stream::operator << (unsigned long value) {
  return (*this << StrUtils::ulongToString(value, this->base));
}

O_Stream& O_Stream::operator << (void* value) {
  // return as Hex output
  Base tmp = this->base;
  this->base = O_Stream::hex;
  *this << ((unsigned long)value);
  // switch back to original base
  this->base = tmp;
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

O_Stream& endl (O_Stream& os) {
  os.put('\n');
  os.flush();
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
