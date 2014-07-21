#ifndef __job_manager_header__
#define __job_manager_header__

#include <user/job.h>
#include <config.h>

class JobManager{
  private:
    Job mJobStorage[MAX_JOB_NUM];
    unsigned int mNum;
    int find(const char* name) const;
  public:
    JobManager();
    bool registerJob(Application& app, const char* name);
    bool unregisterJob(const char* name);
    bool start(const char* name);
    bool stop(const char* name);

    friend O_Stream& operator<<(O_Stream& o, const JobManager& jm);
};

O_Stream& operator<<(O_Stream& o, const JobManager& jm);

#endif
