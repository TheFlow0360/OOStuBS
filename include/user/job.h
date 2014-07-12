#ifndef __job_header__
#define __job_header__

#include <common/o_stream.h>

struct Application;

class Job{
  public:
  enum States{
    stopped,
    running,
  };
  
  private:
    States mState;
    const char* mName;
    Application* mApp;

  public:
    Job();
    Job(Application& app, const char* name);
    Job& operator=(const Job& j);

    bool start();
    bool stop();

    States state() const;
    const char* name() const;
    Application& app() const;
};

O_Stream& operator<<(O_Stream& o, const Job& j);

#endif
