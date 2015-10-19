#ifndef __DECLNODE__H__
#define __DECLNODE__H__
#include "SymbolTable.h"
#include "Spec.h"
#include <vector>
#include <iostream>

extern SymbolTable symTable;
extern void error(const std::string& message);
namespace DeclMode{
  enum Mode{
    NoMode, Basic, Pointer, Array, Enum, Struct, Union, Function, FunctionCall, FunctionArg
  };
};

class Declaration{
 public:
  Declaration();
  ~Declaration();

  // push info to declaration from parser
  void pushID(std::string id);
  void pushPos(int pos);
  void pushSpec(std::string spec);
  void pushKind(SpecName::TypeKind);
  void pushBase(SpecName::BaseType);
  void pushSign(SpecName::Sign);
  void pushQualifier(SpecName::Qualifier);
  void pushStorage(SpecName::Storage);
  void pushArraySize(int size);
  void incLevels();
  void incArgSize();

  std::string getID(int idx) const;
  std::string getSpecStr(int idx) const;
  int getArgSize() const;
  std::vector<SymbolNode*> getArgSymbolNodes() const;

  Spec* getSpec();

  void setSpec(Spec& spec);
  bool setSign(SpecName::Sign sign);
  bool setType(SpecName::TypeKind typekind);
  bool setBaseType(TypeBasic *base, SpecName::BaseType BaseType);
  bool setQualifier(SpecName::Qualifier qualifier);
  bool setStorage(SpecName::Storage storage);

  bool checkSigned(SpecName::BaseType type) const;

  void setMode(DeclMode::Mode mode);
  bool isMode(DeclMode::Mode mode) const;

  void clearArgs();
  void clear();
  bool complete();

  TypeBasic* makeBasicType();
  bool pushBasic(std::string name);
  bool pushArray(std::string name);
  bool pushPointer(std::string name);
  bool pushFunction(std::string name);

  // debug
  void showKinds() const;
  void showSigns() const;
  void showBases() const;
  void showIDs() const;

 private:
  DeclMode::Mode mode;
  Spec spec;
  std::vector<std::string> ids; // identifiers
  std::vector<int> pos; // identifier positions

  std::vector<SpecName::TypeKind> kinds;
  std::vector<SpecName::BaseType> bases; // for basic type
  std::vector<int> arraySizes; // for multi dimension
  int levels; // pointer deepness
  int argSize; // function argments
  std::vector<SymbolNode*> argSymbolNodes;

  std::vector<std::string> specs;
  std::vector<SpecName::Sign> signs;
  std::vector<SpecName::Qualifier> qualifiers;
  std::vector<SpecName::Storage> storages;

};
#endif