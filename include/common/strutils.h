/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                     S T R - U T I L S                                         *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __strUtils_include__
#define __strUtils_include

/// digits for value to string conversion
static const char digits[] = "0123456789abcdef";

/** \brief String Utils
 *
 * Strutils contains classes to simplify work with strings.
 */
class StrUtils {
  private:

  static char* processLong(long value, short base);

  public:

  /**
   * @brief get the length of a string
   *
   * The string must end with \0 !!!
   * @param string the string
   * @return the length of the string
   */
  static int length(const char* string);

  /**
   * @brief reverse a string
   * @param string the string
   * @return the reversed string
   */
  static char* reverse(const char* string);

  /**
   * @brief longToString
   * @param value
   * @return value as string
   */
  static char* longToString(long value);

  /**
   * @brief longToString
   * @param value
   * @param base base of the number
   * @return value as string
   */
  static char* longToString(long value, short base);

  /**
   * @brief unsigned longToString
   * @param value
   * @return value as string
   */
  static char* ulongToString(unsigned long value);

  /**
   * @brief unsigned longToString
   * @param value
   * @param base base of the number
   * @return value as string
   */
  static char* ulongToString(unsigned long value, short base);

};


#endif
