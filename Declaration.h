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
  void pushKind(SpecName::TypeKind);
  void pushBase(SpecName::BaseType);
  void pushSign(SpecName::Sign);
  void pushQualifier(SpecName::Qualifier);
  void pushStorage(SpecName::Storage);
  void pushArraySize(int size);
  void incLevels();
  void incArgSize();

  std::string getID(int idx) const;
  int getArgSize() const;
  int getBasesNum() const{
    return this->bases.size();
  }
  std::vector<SymbolNode*> getArgSymbolNodes() const;

  bool setSign(Spec*, SpecName::Sign sign);
  bool setBaseType(TypeBasic *base, SpecName::BaseType BaseType);
  bool setQualifier(Spec*,SpecName::Qualifier qualifier);
  bool setStorage(Spec*, SpecName::Storage storage);
  void setHasType();

  bool buildStorage(Spec* spec, std::vector<SpecName::Storage> storages);
  bool buildSign(Spec* spec, std::vector<SpecName::Sign> signs);
  bool buildQualifier(Spec* spec, std::vector<SpecName::Qualifier> qualifiers);
  bool buildBase(Spec* spec, std::vector<SpecName::BaseType> bases);

  TypeBasic* makeBasicType(std::vector<SpecName::BaseType> bases, std::vector<SpecName::Sign>signs);
  TypeBasic* makeBasicVar(std::vector<SpecName::BaseType> bases,
    std::vector<SpecName::Sign>signs, std::vector<SpecName::Storage> storages,
     std::vector<SpecName::Qualifier> qualifiers);

  TypePointer* makePointerVar(SpecName::TypeKind typekind, std::vector<SpecName::BaseType> bases,
    std::vector<SpecName::Sign>signs, std::vector<SpecName::Storage> storages,
     std::vector<SpecName::Qualifier> qualifiers);

  bool checkSigned(SpecName::BaseType type) const;

  void setMode(DeclMode::Mode mode);
  bool isMode(DeclMode::Mode mode) const;

  void clearArgs();
  void clear();
  bool complete();

  bool pushBasic(std::string name);
  bool pushArray(std::string name);
  bool pushPointer(std::string name);
  bool pushFunction(std::string name);

  bool insertSymbol(std::string name, SymbolNode* val, int pos);

  // debug
  void showKinds() const;
  void showSigns() const;
  void showBases() const;
  void showIDs() const;
  void showStorages() const;

 private:
  DeclMode::Mode mode;
  std::vector<std::string> ids; // identifiers
  std::vector<int> pos; // identifier positions

  // type-specific detail
  std::vector<int> arraySizes; // for multi dimension
  int levels; // pointer deepness
  int argSize; // function argments
  bool hasType;
  std::vector<SymbolNode*> argSymbolNodes;

  // main components of spec
  std::vector<SpecName::TypeKind> kinds;
  std::vector<SpecName::BaseType> bases;
  std::vector<SpecName::Sign> signs;
  std::vector<SpecName::Qualifier> qualifiers;
  std::vector<SpecName::Storage> storages;

  // holder holds a set of each component set
  std::vector<std::vector<SpecName::TypeKind>> kindsHolder;
  std::vector<std::vector<SpecName::Sign>> signsHolder;
  std::vector<std::vector<SpecName::Qualifier>> qualifiersHolder;
  std::vector<std::vector<SpecName::Storage>> storagesHolder;
  std::vector<std::vector<SpecName::BaseType>> basesHolder;

};
#endif