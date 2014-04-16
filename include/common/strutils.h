/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                     S T R - U T I L S                                         *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __strUtils_include__
#define __strUtils_include

/** \brief String Utils
 *
 * Strutils contains classes to simplify work with strings.
 */
class StrUtils {
  public:

  /**
   * @brief get the length of a string
   *
   * The string must end with \0 !!!
   * @param string the string
   * @return the length of the string
   */
  static int length(const char* string);
};


#endif
