/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    C G A _ S C R E E N                                        *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#include "machine/cgascr.h"

CGA_Screen::CGA_Screen() :  screen((ScreenChar(*)[80])memoryBase), 
                            index_port(CGA_Screen::indexPortNum), 
                            data_port(CGA_Screen::dataPortNum),
                            attribute(0x7){
  
  clear();
}

CGA_Screen::~CGA_Screen(){
  
}

void CGA_Screen::setpos (unsigned short x, unsigned short y) {
  unsigned short pos;
  unsigned short high, low;
  
  if (x >= COLUMNS || y > ROWS) return;
  
  pos  = y * COLUMNS + x;
  low  = pos & 0xff;
  high = (pos >> 8 ) & 0xff;
  
  /* Indexregister 14 (Cursor high) an Port INDEX_PORT ausgeben */
  index_port.outb (14);
  /* Datenregister an Port DATA_PORT schreiben */
  data_port.outb (high);
  /* Indexregister 15 (Cursor low) an Port INDEX_PORT ausgeben */
  index_port.outb (15);
  /* Datenregister an Port DATA_PORT schreiben */
  data_port.outb (low);
}

void CGA_Screen::getpos (unsigned short& x, unsigned short& y) const{
  unsigned short pos;
  unsigned char high, low;
  
  /* Indexregister 14 (Cursor high) an Port INDEX_PORT ausgeben */
  index_port.outb (14);
  /* Datenregister an Port DATA_PORT auslesen */
  high = data_port.inb ();
  /* Indexregister 15 (Cursor low) an Port INDEX_PORT ausgeben */
  index_port.outb (15);
  /* Datenregister an Port DATA_PORT auslesen */
  low = data_port.inb ();
  
  pos = ((unsigned short)high) << 8 | low;
  x   = pos % COLUMNS;
  y   = pos / COLUMNS;
}

void CGA_Screen::show (unsigned short x, unsigned short y, char character, unsigned char attrib) {
  
  if (x >= COLUMNS || y > ROWS) return;
  
  screen[y][x].c   = character;
  screen[y][x].attrib = attrib;
}

void CGA_Screen::print (const char* string, unsigned int n) {
  unsigned short x, y;
  getpos (x, y);
  
  while (n) {
    switch (*string) {
      case '\n':
        x = 0;
        y++;
      break;
      
      default:
        show(x,y,*string, attribute);
        x++;
        if (x >= COLUMNS) {
          x = 0;
          y++;
        }
      break;
    }
    
    string++;
    if (y >= ROWS) {
      scrollup ();
      y--;
    }
    n--;
  }
  setpos (x, y);
}

void CGA_Screen::scrollup () {
  
  for(unsigned short y=1;y<ROWS;y++){
     for(unsigned short x=0;x<COLUMNS;x++){
      show(x,y-1,screen[y][x].c, screen[y][x].attrib);
    }
  }
  
  for(unsigned short x=0;x<COLUMNS;x++){
    show(x,ROWS-1,' ', attribute);
  }
}



void CGA_Screen::setAttributes(int fgColor, int bgColor, bool blink){
  attribute = ((bgColor & 0x7) << 4) | (fgColor & 0xF);
  if(blink)
    attribute |= 0x80;
  else
    attribute &= ~0x80;
}

void CGA_Screen::clear(){
  for(unsigned short x=0; x<COLUMNS; x++){
    for(unsigned short y=0; y<=ROWS; y++){
      show(x, y, ' ', attribute);
    }
  }
  setpos(0,0);
}
