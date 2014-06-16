#include "machine/serial.h"
#include "locking/scopedLock.h"
#include "object/lock.h"

Serial::Serial(): transmitPort(address+0),
                  divisorLowPort(address+0),
                  divisorHighPort(address+1),
                  controlPort(address+3),
                  statusPort(address+5){
  
  ControlByte controlByte;
  controlByte.size          = ControlByte::_8Bits;
  controlByte.stopBits      = ControlByte::One;
  controlByte.parity        = ControlByte::none;
  controlByte.breakEnable   = false;
  controlByte.divisorAccess = false;

  control(controlByte);
  baudRate(115200);
}

Serial::~Serial(){
  print("Operating system ended", 22);
}

void Serial::print(const char* string, unsigned int n){
  for(unsigned int i=0;i<n;i++){
    transmit(string[i]);
    while(!status().transmitBufferEmpty);
  }
}

Serial::StatusByte Serial::status(){
  union{
    unsigned char buffer;
    StatusByte statusByte;
  } u;
  u.buffer=statusPort.inb();
  return u.statusByte;
}

void Serial::control(Serial::ControlByte controlByte){
  union{
    unsigned char buffer;
    ControlByte controlByte;
  } u;
  u.controlByte = controlByte;
  controlPort.outb(u.buffer);
}

Serial::ControlByte Serial::control(){
    union{
    unsigned char buffer;
    ControlByte controlByte;
  } u;
  u.buffer = controlPort.inb();
  return u.controlByte;
}

unsigned int Serial::baudRate(){
  ScopedLock sLock(lock);
  union{
    unsigned char buffer[2];
    unsigned short divisor;
  } u;
  ControlByte controlByte=control();
  controlByte.divisorAccess=true;
  control(controlByte);
  u.buffer[0]=divisorLowPort.inb();
  u.buffer[1]=divisorHighPort.inb();
  controlByte.divisorAccess=false;
  control(controlByte);
  return maxBaudRate/u.divisor;
}

unsigned int Serial::baudRate(unsigned int baudRate){
  ScopedLock sLock(lock);
  union{
    unsigned char buffer[2];
    unsigned short divisor;
  } u;
  u.divisor = maxBaudRate / baudRate;
  ControlByte controlByte=control();
  controlByte.divisorAccess=true;
  control(controlByte);
  divisorLowPort.outb(u.buffer[0]);
  divisorLowPort.outb(u.buffer[1]);
  controlByte.divisorAccess=false;
  control(controlByte);
  return maxBaudRate % baudRate;
}

void Serial::transmit(char c){
  union{
    unsigned char buffer;
    char character;
  } u;
  u.character=c;
  transmitPort.outb(u.buffer);
}
