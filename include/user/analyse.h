#ifndef __OOSTUBS_USER_ANALYSE__
#define __OOSTUBS_USER_ANALYSE__

/** \brief 
 *    \~english analyse function for procedure stack
 *    \~german  Diese Funktion dient der Analyse des Prozedurstacks.
 * 
 * \~english
 * The functions prints the first 60 32 bit words of the stack, 
 * four of them in one line, each.
 * \~german 
 * Es werden die ersten 60 32-Bit-Worte vom Stack ausgegeben. Dabei 
 * erscheinen je vier der Worte in einer Zeile.
 * 
 * \~
 * \param[in] esp
 *   \~english
 *   This is a pointer to the top of the stack from the investigated function. 
 *   The analysis function call of 
 *    \ref printStack is not visible in this situation.
 *   \~german
 *   Dis ist ein Zeiger auf den Anfang des Stacks. Der Frame der Funktion \ref printStack
 *   ist nicht sichtbar.
 * 
 * \~
 *  * \~
 * \param[in] func
 *   \~english
 *   Name of the responsible function.
 *   \~german
 *   Name der aufrufenden Funktion
 * 
 * \~
 */
void analyseProcedureStack(void** esp, const char* func);

#endif
