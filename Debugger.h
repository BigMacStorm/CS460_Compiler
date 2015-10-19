#ifndef __DEBUGGER__H__
#define __DEBUGGER__H__
#include <fstream>
class Debugger{
  private:
    bool m_debug;
    std::string filename;
    std::ofstream *pfout;

  public:
    Debugger();
    ~Debugger();
    void create();
    void close();
    void setDebug(bool debug);
    void setFileName(const std::string& message);
    void debug(const std::string& message);
};
#endif