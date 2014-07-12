#include "common/queue.h"
#include "common/null.h"

Queue::Element::Element() : next(NULL){}

Queue::Queue() : mHead(NULL), mTail(NULL){}

void Queue::push_back(Element& e){
  if(!mHead){
    mHead=&e;
    mTail=&e;
  }else{
    mTail->next=&e;
    mTail=&e;
  }
}

Queue::Element* Queue::pop_front(){
  if(!mHead)
    return NULL;
  Element* temp=mHead;
  mHead=temp->next;
  temp->next=NULL;
  return temp;
}

Queue::Element* Queue::peek_front() const{
  return mHead;
}

bool Queue::remove(Queue::Element& e){
  Element* curr=mHead;
  Element* preCurr=NULL;
  while(curr){
    if(curr==&e){
      if(preCurr)
        preCurr->next=curr->next;
      else
        mHead=curr->next;
      curr->next=NULL;
      return true;
    }else{
      preCurr=curr;
      curr=curr->next;
    }
  }
  return false;
}

bool Queue::empty() const{
  return !mHead;
}
