#include <user/job.h>
#include <user/appl.h>
#include <common/null.h>
#include <object/scheduler.h>

Job::Job() : mState(stopped), mName(NULL), mApp(NULL){

}

Job::Job(Application& app, const char* name) : mState(stopped), mName(name), mApp(&app){
  
}

Job& Job::operator=(const Job& j){
  mApp = j.mApp;
  mState = j.mState;
  mName = j.mName;

  return *this;
}

bool Job::start(){
  if(mApp && mState==stopped){
    scheduler.insert(*mApp);
    mState=running;
    return true;
  }
  return false;
}

bool Job::stop(){
  if(mApp && mState==running){
    mState=stopped;
    scheduler.kill(*mApp);
    return true;
  }
  return false;
}

Job::States Job::state() const{
  return mState;
}

const char* Job::name() const{
  return mName;
}

Application& Job::app() const{
  return *mApp;
}

O_Stream& operator<<(O_Stream& o, const Job& j){
  o << j.name() << ": ";
  switch(j.state()){
    case(Job::stopped): return o << "stopped";
    case(Job::running): return o << "running";
    default           : return o << "unknown";
  }
}
