/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                          L O C K                                              * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __lock_header__
#define __lock_header__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */

class Lock{
  protected:
    bool state;
  public:
    Lock() : state(false){}
    virtual void lock() = 0;
    virtual void unlock() = 0;
};

#endif
