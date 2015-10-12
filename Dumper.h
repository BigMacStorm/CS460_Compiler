#ifndef __DUMPER__H__
#define __DUMPER__H__
#include <iostream>
#include <fstream>
class Dumper{
  private:
    bool m_dump;
    string filename;
    ofstream fout;

  public:
    Dumper();
    void setDebug(bool debug);
    void setFileName(string filename);
    void dump(const std::string& message);
};
#endif