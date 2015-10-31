#ifndef __GRAPH__H__
#define __GRAPH__H__
#include "Debugger.h"
#include <sstream>

class Graph{
    public:
        Graph(std::string filename = "graph.dot",std::string graph_name = "g");
        ~Graph();
        void setVisualizer(bool on_off);
        void startBuild();
        void addEdge(int pid, int cid);
        void addNode(int id, std::string label);
    private:
      Debugger visualizer;
      std::string filename, graph_name;
};
#endif
