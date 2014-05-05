/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                        C O N F I G                                            *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* Deactivate include guard for assembler files */
#ifndef __config_header__
#define __config_header__

/* MACROS */

/**\brief 
 * \~german  Größe für den Stack, die der Bootcode anlegen und nutzen soll
 * \~english Size of the stack created by the assembly bootup code 
 **/
#define BOOT_STACK_SIZE 4096

/** \brief 
 * \~german  Größe des Zeichenpuffers
 * \~english Size of string buffer 
 **/
#define BUFFERSIZE 80

#define MAX_INTERRUPT_NUMBER 255
#define MIN_INTERRUPT_NUMBER 32
#define DEBUG_X 0
#define DEBUG_Y 0
#define KEYBOARD_X 10
#define KEYBOARD_Y 10
#endif
