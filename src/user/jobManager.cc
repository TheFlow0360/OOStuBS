#include <user/jobManager.h>
#include <common/string.h>
#include <object/kout.h>

JobManager::JobManager() : mNum(0){

}

bool JobManager::registerJob(Application& app, const char* name){
    if(find(name)<0){
      mJobStorage[mNum++]=Job(app, name);
      return true;
    }else
      return false;
}

bool JobManager::unregisterJob(const char* name){
    int index = find(name);
    if(index>=0)
        mJobStorage[index]=mJobStorage[mNum--];
    return index>=0;
}

int JobManager::find(const char* name) const{
  for(unsigned int i=0;i<mNum;i++)
    if(strcmp(name, mJobStorage[i].name())==0)
      return i;
  return -1;
}

bool JobManager::start(const char* name){
  int index = find(name);
  if(index>=0)
    return mJobStorage[index].start();
  else
    return false;
}

bool JobManager::stop(const char* name){
  int index = find(name);
  if(index>=0)
    return mJobStorage[index].stop();
  else
    return false;
}

O_Stream& operator<<(O_Stream& o, const JobManager& jm){
  for(unsigned int i=0;i<jm.mNum;i++)
    o << " " << jm.mJobStorage[i] << endl;
  return o;
}
