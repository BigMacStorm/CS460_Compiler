#ifndef __DEBUGGER__H__
#define __DEBUGGER__H__
#include <iostream>
class Debugger{
  private:
    bool m_debug;

  public:
    Debugger();
    void setDebug(bool debug);
    void debug(const std::string& message);
};
#endif