#include <user/parser.h>
#include <common/null.h>
#include <object/kout.h>
#include <common/string.h>

Parser::Parser(): mNum(0), mFinished(false){}

void Parser::clear(){
  for(unsigned int i=0;i<BUFFERSIZE;i++)
    mBuffer[i]='\0';
  mNum=0;
  mFinished=false;
}

bool Parser::feed(char c){
  if(c=='\n')
    return mFinished=true;
    
  if(!mFinished && mNum<BUFFERSIZE){
    mBuffer[mNum++]=c;
    return true;
  }else
    return false;
}

void Parser::erase(){
  if(mNum)
    mNum--;
}

bool Parser::finished() const{
  return mFinished;
}

Parser::Commands Parser::result(const char** arg) const{
    *arg=NULL;
    if(!mNum)
      return unknown;
    if(strncmp(mBuffer, "start", mNum)==0){
        *arg=mBuffer+6;
        return start;
    }

    if(strncmp(mBuffer, "kill", mNum)==0){
        *arg=mBuffer+5;
        return kill;
    }

    if(strncmp(mBuffer, "list", mNum)==0)
        return list;

    if(strncmp(mBuffer, "help", mNum)==0)
        return help;

    return unknown;
}

O_Stream& operator<<(O_Stream& o, const Parser& p){
     o << " start <app name> : starts the given application" << endl;
     o << " kill <app name>  : stops the given application" << endl;
     o << " list             : list all available applications" << endl;
     o << " help             : output this help" << endl;
     return o;
}
