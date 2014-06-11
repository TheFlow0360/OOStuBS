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

CGA_Screen::CGA_Screen(){
  this->clear();

  // standard font color: light green
  this->attr.set.fgColor = LIGHTGREEN;
  // standard background-color: black
  this->attr.set.bgColor = BLACK;
  // no blink
  this->attr.set.blink = false;

  const char* text = "System Starting\nInitializing OOStuBS...\n\n";
  this->print(text, StrUtils::length(text));
}

CGA_Screen::~CGA_Screen(){
  const char* text = "\nSystem will now halt...";
  this->print(text, StrUtils::length(text));
}

void CGA_Screen::setpos (unsigned short x, unsigned short y) {
  IO_Port index(INDEX_REG);
  IO_Port data(DATA_REG);

  unsigned short pos = y + (CHARS_PER_ROW * x);

  index.outb(CURSOR_HIGH);
  data.outb((pos >> 8) & 0xff);
  index.outb(CURSOR_LOW);
  data.outb(pos & 0xff);
}

void CGA_Screen::getpos (unsigned short& x, unsigned short& y) const {
  IO_Port index(INDEX_REG);
  IO_Port data(DATA_REG);

  index.outb(CURSOR_LOW);
  unsigned char low = data.inb();
  index.outb(CURSOR_HIGH);
  unsigned char high = data.inb();

  unsigned short pos = (high << 8) + low;
  y = pos % CHARS_PER_ROW;
  x = pos / CHARS_PER_ROW;
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
  unsigned short x, y;
  this->getpos(x, y);
  for (unsigned int i = 0; i < n; i++) {
    if (string[i] == '\n') {
      x++;
      y = 0;
      continue;
    }
    if (x >= ROW_COUNT) {
      this->scrollup();
      x--;
    }
    this->show(x, y, string[i], attr.byte);
    y++;
    if (y >= CHARS_PER_ROW) {
      y = 0;
      x++;
    }
  }
  if (x >= ROW_COUNT) {
    this->scrollup();
    x--;
  }
  this->setpos(x, y);
}

void CGA_Screen::print(const char* string)
{
  this->print(string, StrUtils::length(string));
}

void CGA_Screen::scrollup () {
  // copy all lines one line back
  int dest = MEMORY_START;
  int count = 2 *                 // 2 bytes per character
      CHARS_PER_ROW;              // 80 bytes per line
  int source = dest + count;      // copy from one line further
  count *= ROW_COUNT - 1;         // 24 lines of 25 I want to copy back

  for (int i = 0; i < count; i++)
  {
    *((char*)dest+i) = *((char*)source+i);
    *((char*)dest+i+1) = *((char*)source+i+1);
  }

  // fill last line with spaces
  for (int i = 0; i < CHARS_PER_ROW; i++)
    this->show(ROW_COUNT - 1, i, ' ', this->attr.byte);
}

void CGA_Screen::clear () {
  for (unsigned int i = 0; i < ROW_COUNT; i++) {
    for (unsigned int j = 0; j < CHARS_PER_ROW; j++) {
      this->show(i, j, ' ', this->attr.byte);
    }
  }
  this->setpos(0,0);
}

void CGA_Screen::setAttributes(int fgColor, int bgColor, bool blink){
  this->attr.set.fgColor = fgColor;
  this->attr.set.bgColor = bgColor;
  this->attr.set.blink = blink;
}
