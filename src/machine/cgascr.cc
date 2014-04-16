/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    C G A _ S C R E E N                                        *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#include "machine/cgascr.h"
#include "machine/io_port.h"
#include "common/o_stream.h"
#include "common/strutils.h"

int CGA_Screen::computeAddress(unsigned short x, unsigned short y)
{
  return 0xB8000 + 160 * x + 2 * y;
}

CGA_Screen::CGA_Screen(){
  this->clear();

  // standard font color: light green
  this->attr.set.fgColor = LIGHTGREEN;
  // standard background-color: black
  this->attr.set.bgColor = BLACK;
  // no blink
  this->attr.set.blink = 0;

  char* text = "System Starting\nInitializing OOStuBS...\0";
  this->print(text, StrUtils::length(text));
}

CGA_Screen::~CGA_Screen(){
  char* text = "System will now halt...\0";
  this->print(text, StrUtils::length(text));
}

void CGA_Screen::setpos (unsigned short x, unsigned short y) {
  IO_Port index(INDEX_REG);
  IO_Port data(DATA_REG);

  CGA_Cursor cursor;
  cursor.position = (x + 80*y);
  index.outb(CURSOR_HIGH);
  data.outb(cursor.bytes.high);
  index.outb(CURSOR_LOW);
  data.outb(cursor.bytes.low);
}

void CGA_Screen::getpos (unsigned short& x, unsigned short& y) const{
  IO_Port index(INDEX_REG);
  IO_Port data(DATA_REG);

  CGA_Cursor cursor;
  index.outb(CURSOR_HIGH);
  cursor.bytes.high = data.inb();
  index.outb(CURSOR_LOW);
  cursor.bytes.low = data.inb();

  unsigned short offset = cursor.position;
  x = offset % 80;
  y = offset / 80;
}

void CGA_Screen::show (unsigned short x, unsigned short y, char character, unsigned char attribute) {
  int adr = this->computeAddress(x, y);
  *(char *)(adr) = character;
  *(char *)(adr + 1) = attribute;
}

void CGA_Screen::show(unsigned short x, unsigned short y, CGA_Screen::CGA_Char c)
{
  this->show(x, y, c.character, c.attr.byte);
}

void CGA_Screen::print (const char* string, unsigned int n) {
  unsigned int x = 0;
  unsigned int y = 0;
  for (unsigned int i = 0; i < n; i++) {
    if (string[i] == '\n') {
      x++;
      y = 0;
      continue;
    }
    this->show(x, y, string[i], attr.byte);
    y++;
    if (y > 80) {
      y = 0;
      x++;
    }
  }
  this->setpos(x, y);
}

/** \todo implement **/
void CGA_Screen::scrollup () {
  /* ToDo: Insert Your Code Here */
}

void CGA_Screen::clear () {
  for (unsigned int i = 0; i < 25; i++) {
    for (unsigned int j = 0; j < 80; j++) {
      this->show(i, j, ' ', 0);
    }
  }
}

void CGA_Screen::setAttributes(int fgColor, int bgColor, bool blink){
  this->attr.set.fgColor = fgColor;
  this->attr.set.bgColor = bgColor;
  this->attr.set.blink = blink;
}
