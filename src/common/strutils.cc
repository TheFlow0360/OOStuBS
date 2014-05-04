/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                     S T R - U T I L S                                         *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "common/strutils.h"
#include "machine/mem.h"


char*StrUtils::processLong(long value, short base)
{
  char* res = (char*) Memory::alloc(16);
  int i = 0;
  do
  {
    res[i] = digits[value % base];
    value /= base;
    i++;
  } while (value > 0);

  if (base == 16) {
    res[i] = 'x';
    i++;
  }
  if (base == 8 or base == 16) {
    res[i] = '0';
    i++;
  }
  if (base == 2)
    res[i] = 'b';
  return res;
}

int StrUtils::length(const char* string)
{
  int length = 0;
  while (string[length] != '\0')
    length++;
  return length;
}

char* StrUtils::reverse(const char* string)
{
  int l = StrUtils::length(string);
  char* res = (char*) Memory::alloc(l + 1);
  for (int i = 1; i <= l; i++)
    res[l-i] = string[i-1];
  res[l] = '\0';
  return res;
}

char* StrUtils::longToString(long value)
{
  // default base is decimal
  return StrUtils::longToString(value, 10);
}

char* StrUtils::longToString(long value, short base)
{
  char* res = (char*) Memory::alloc(16);
  if (value >= 0) {
    res = processLong(value, base);
  } else {
    res = processLong(-1 * value, base);
    res[StrUtils::length(res)] = '-';
  }
  return StrUtils::reverse(res);
}

char* StrUtils::ulongToString(unsigned long value)
{
  return StrUtils::ulongToString(value, 10);
}

char*StrUtils::ulongToString(unsigned long value, short base)
{
  return StrUtils::reverse(processLong(value, base));
}
