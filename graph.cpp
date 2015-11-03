#include "graph.h"
#include <iostream>
/**
@file graph.cpp
@author Yuta Miyake
@brief Creates a dot file of simple tree for graphviz
*/
Graph::Graph(std::string filename, std::string graph_name){
  // parameterized constructor w/ default arguments
  this->filename = filename;
  this->graph_name = graph_name;
  this->visualizer.setFileName(this->filename);
}
Graph::~Graph(){
  // destructor
  this->visualizer.debug("}");

  std::stringstream ss;
  ss << "dot -Tpng ";
  ss << this->filename << " -o graph.png";
  system(ss.str().c_str());
}
void Graph::setVisualizer(bool on_off){
  // on/off visualizer
  this->visualizer.setDebug(on_off);
}
void Graph::startBuild(){
  // start building the dot file
  std::stringstream ss;
  this->visualizer.setFileName(this->filename);
  this->visualizer.setDebug(true);
  ss << "digraph " << this->graph_name << " {" << std::endl;
  this->visualizer.debug(ss.str());
}
void Graph::addNode(int id, std::string label){
  // add new node into the dot file
  std::stringstream ss;
  ss << id << " [label=\"" << label << "\"];" << std::endl;
  this->visualizer.debug(ss.str());
  //std::cout <<"[graphviz]: add " << label << std::endl;
}
void Graph::addEdge(int pid, int cid){
  // add new edge between two nodes into the dot file
  std::stringstream ss;
  ss << pid << " -> " << cid << ";" << std::endl;
  this->visualizer.debug(ss.str());
  //std::cout <<"[graphviz]: add edge " << pid << " -> " << cid << std::endl;
}
