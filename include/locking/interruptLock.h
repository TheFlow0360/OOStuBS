/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                   I N T E R R U P T - L O C K                                 * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __interrupt_lock_header__
#define __interrupt_lock_header__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "locking/lock.h"

extern "C" void exception(unsigned short, void**);

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * \~english
 * \brief Global interrupt lock
 *
 * This class represent a global interrupt lock to synchronize critical sections. It disables all interrupts on creation until it is destroyed or the asymmetricUnlock function is called. The asymmetricUnlock function is a bypass for specific situations in which a created lock will never be destroyed because the scope it was defined in never ends. Therefore this method may only be called by the kickoff function of Thread.
 **/
class InterruptLock : public Lock
{
    private:
        /**
         * \~english
         * \brief Interrupt state on entry
         *
         * The original state on lock entry needs to be saved to restore it on
         * destruction of the lock.
         *
         **/
        bool interruptState;

        /** \brief enter an interrupt context **/
        void enter();

        /** \brief leave an interrupt context **/
        void leave();
            
    public:
        /** \brief Unlock and destroy **/
        ~InterruptLock();

        /**
         * \~english
         * \brief Locks the execution of interrupts
         *
         * This method disables the handling of interrupts. The current interrupt activation state is saved and restored
         * on unlock.
         **/
        virtual void lock();

        /**
         * \~english
         * \brief %Unlock interrupt handling globally
         *
         * This method restores the previous interrupt handling state before this Lock was locked.
         **/
        virtual void unlock();

        friend void exception(unsigned short,void**);
};

#endif
