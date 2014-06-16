/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                       C O N T E X T                                           *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __context_include__
#define __context_include__

class Thread;

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */

/** \brief Storage for current context of thread
 *
 *  This class contains all information needed to represent a thread of execution.
 *  It may be used to stop, switch and continue currently running threads.
 *
 **/
class Context{
  private:
    /** \brief Definition of a storage type able to hold CPU register contents. **/
    typedef void* Register;
    
    /** \brief Index enumeration mapping registers to indices of the registers array **/
    enum RegisterIndices{
      ebx = 0, /**< General purpose register **/
      esi = 1, /**< General purpose register **/
      edi = 2, /**< General purpose register **/
      esp = 3, /**< Stack pointer **/
      ebp = 4  /**< Base pointer **/
    };

    /** \brief the non-volatile x86 base registers **/
    Register registers[5];

    /** \brief Local 1K stack of this thread. **/
    Register stack[1024];

  public:
    /** \brief Context creation
     *
     *  On construction of the context the CPU registers will be filled with appropriate information, to start the
     *  thread on its first scheduling
     *
     *  \param thread pointer to thread object
     *
     **/
    Context(Thread* thread);

    /** \brief swaps the currently running context with the specified one
     * 
     *  During the swap process the registers of the currently active context will be updated with the actualk values
     *  contained in the CPU.
     *
     *  \param next the next context to be run by the CPU
     */
    void swap(Context& next);

    /** \brief replaces the currently running context with this one
     * 
     *  This method does not preserve the old context. Therefore the current execution state of the originating thread
     *  is lost.
     **/
    void set();
};

#endif
