#ifndef __parser_header__
#define __parser_header__

#include <config.h>
#include <common/o_stream.h>

class Parser{
  private:
    char mBuffer[BUFFERSIZE];
    unsigned int mNum;
    bool mFinished;

  public:
    enum Commands{
      unknown,
      start,
      kill,
      list,
      help
    };
    Parser();
    void clear();
    bool feed(char c);
    void erase();
    bool finished() const;
    Commands result(const char** arg) const;
    const char* commands() const;
};

O_Stream& operator<<(O_Stream& o, const Parser& p);

#endif
