/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                           Q U E U E                                           * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __queue_include__
#define __queue_include__

class Queue{
  public:

    class Element{
      private:
        Element* next;
      public:
        Element();
      friend class Queue;
    };

  private:
    Element* mHead;
    Element* mTail;

  public:
    Queue();
    virtual ~Queue(){}
    void push_back(Element& e);
    Element* pop_front();
    Element* peek_front() const;
    bool remove(Element& e);
    bool empty() const;
};

#endif
