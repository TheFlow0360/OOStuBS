#include "machine/context.h"
#include "thread/thread.h"

Context::Context(Thread* thread){
  Register* tos  = stack+sizeof(stack)/sizeof(Register);
  tos[-1]        = thread;
  tos[-3]        = reinterpret_cast<void*>(&Thread::kickoff);
  registers[esp] = tos-4;
}

void Context::set(){
  asm("mov   (%0), %%ebx\n\t"
      "mov  4(%0), %%esi\n\t"
      "mov  8(%0), %%edi\n\t"
      "mov 12(%0), %%esp\n\t"
      "mov 16(%0), %%ebp\n\t"
      :
      : "r"(registers)
  );
}

void Context::swap(Context& next){
  asm("mov %%ebx,   (%0)\n\t"
      "mov %%esi,  4(%0)\n\t"
      "mov %%edi,  8(%0)\n\t"
      "mov %%esp, 12(%0)\n\t"
      "mov %%ebp, 16(%0)\n\t"
      "mov   (%1), %%ebx\n\t"
      "mov  4(%1), %%esi\n\t"
      "mov  8(%1), %%edi\n\t"
      "mov 12(%1), %%esp\n\t"
      "mov 16(%1), %%ebp\n\t"
      :
      : "r"(registers), "r"(&next.registers)
  );
}
