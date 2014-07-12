/*---------------------------------------------------------------------------*
 * Technical Computer Science II                                             *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                         W A I T I N G R O O M                             *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#ifndef __waitingroom_header__
#define __waitingroom_header__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */

#include "common/queue.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */

/** \brief A waitingroom Customers can wait in.
 *
 *  The waitingroom consists of a queue the customers wait in until they can be
 *  serviced.  On destruction of a waitingroom all waiting customers need to be
 *  released. In this case the result of the operation the customers waited for 
 *  depends on the implementation of the service the customers waited for.
 *
 *  \see Semaphore
 **/
class Waitingroom : public Queue
{
	public:
    /** \brief Destructor reactivating waiting customers
     *
     *  The waiting customers need to be reactivated on destrcution of the
     *  waitingroom since otherwise they will never be scheduled to run
     *  again.
     *
     **/
		virtual ~Waitingroom();
};

#endif
