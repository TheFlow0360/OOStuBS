/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                       M E M O R Y                                             *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "machine/mem.h"

bool Memory::initialized = false;

bool Memory::isByteReserved(int pos)
{
  return _flags[pos / 8] & ( 1u << (pos % 8));
}

/** \todo speed up via block search */
bool Memory::isReserved(int start, int size)
{
  bool reserved = false;
  for (int i = start; i < start + size; i++) {
    if (isByteReserved(i))
      return false;
  }
  return reserved;
}

void Memory::doReserve(int start, int size)
{
  doReserve(start, size, false);
}

void Memory::doReserve(int start, int size, bool free)
{
  for (int i = start; i < start + size; i++) {
    if (!free)
      _flags[i / 8] |= 1u << (i % 8);          // set true
    else
      _flags[i / 8] &= ~( 1u << (i % 8));     // set false
  }
}

void Memory::initialize()
{
  for (int i = 0; i < FLAG_AMOUNT; i++) {
    _flags[i] = 0;
    //for (int j = 1; j <= 8; j++) {
    //  _heap[i*j] = 0;
    //}
  }
  Memory::initialized = true;
}

void* Memory::alloc(int size)
{
  if (!initialized)
    Memory::initialize();
  void* res;
  int start = 0;
  bool enoughSpace = false;
  do {
    while (isByteReserved(start)) {
      start++;
      if (start >= MEMORY_SIZE)
        return nullptr;
    }
    enoughSpace = !isReserved(start, size);
  } while (!enoughSpace);
  doReserve(start, size);
  res = (void*) &_heap[start];
  return res;
}

void Memory::free(void* mem, int size)
{
  int pos = (unsigned int)mem - (unsigned int)_heap;
  doReserve(pos, size, true);
}

/** \todo implement */
int Memory::allocatedMemory()
{
  if (!initialized)
    Memory::initialize();
  return 0;
}

/** \todo implement */
int Memory::availableMemory()
{
  if (!initialized)
    Memory::initialize();
  return 0;
}

/** \todo implement */
int Memory::totalAvailableMemory()
{
  if (!initialized)
    Memory::initialize();
  return 0;
}
