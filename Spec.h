#ifndef __TYPE__H__
#define __TYPE__H__
#include <iostream>
#include <vector>
#include <map>
#include <sstream>

namespace SpecName{
  enum TypeKind{
    NoKind, Basic, Pointer, Array, Struct, Union, Function, Enum, TypeName
  };
  enum BaseType{
   NoType,
   Void,
   Char, UChar, SChar,
   Int, UInt,
   Short, UShort,
   Long, ULong,
   LLong, ULLong,
   Float, Double, LDouble,
  };
  enum Storage{
    NoStorage, Extern, Static, Auto, Register, Typedef
  };
  enum Qualifier{
    NoQualifier, Const, Volatile, ConstVolatile
  };
  enum Sign{
    NoSign, Signed, Unsigned
  };
};

class Spec{
public:
  Spec(SpecName::TypeKind = SpecName::NoKind, SpecName::Storage = SpecName::NoStorage,
    SpecName::Qualifier = SpecName::NoQualifier, SpecName::Sign = SpecName::NoSign);

  std::string getSpecStr() const;
  virtual std::string getTypeKindStr() const;
  std::string getStorageClassStr() const;
  std::string getTypeQualifierStr() const;

  SpecName::TypeKind getTypeKind() const;
  SpecName::Storage getStorage() const;
  SpecName::Qualifier getQualifier() const;
  SpecName::Sign getSign() const;

  void setTypeKind(SpecName::TypeKind typekind);
  void setStorage(SpecName::Storage storage);
  void setQualifier(SpecName::Qualifier qualifier);
  void setSign(SpecName::Sign sign);

  bool isTypeKind(SpecName::TypeKind) const;
  bool isStorageClass(SpecName::Storage) const;
  bool isTypeQualifier(SpecName::Qualifier) const;
  bool isSign(SpecName::Sign) const;

protected:
  SpecName::TypeKind typekind;
  SpecName::Storage storage;
  SpecName::Qualifier qualifier;
  SpecName::Sign sign;
};

// basic -----------------------------------------------
class TypeBasic: public Spec{
 public:
  TypeBasic(SpecName::BaseType baseType = SpecName::NoType);
  std::string getTypeKindStr() const;
  void setBaseType(SpecName::BaseType baseType);
 private:
  SpecName::BaseType baseType;
};

// enum -----------------------------------------------
class TypeEnum: public Spec{
 public:
   TypeEnum();
   int getSize() const;
   void addConst(std::string name, int number);
   int getNextNumber() const;

 private:
  int nextNumber;
  std::map<std::string, int> constants;
};

// array -----------------------------------------------
class TypeArray: public Spec{
 public:
   TypeArray();
   TypeArray(Spec*elemType, int size);
   Spec* getElemType() const;
   int getSize() const;

 private:
  Spec*elemType;
  int size;
};
// function -----------------------------------------------
class TypeFunction : public Spec{
public:
    TypeFunction();
    TypeFunction(Spec*returnType);
    void insertArg(Spec*argType);
    Spec* getReturnType() const;
    int getArgSize() const;
    Spec* getArgType(int nth) const;

  private:
    Spec* returnType;
    std::vector<Spec*> argTypes;
};
// TypeName -----------------------------------------------
class TypeTypeName: public Spec{
 public:
   TypeTypeName();
   TypeTypeName(Spec* baseType);
   Spec* getBaseType() const;

 private:
  Spec*baseType;
};

// pointer -----------------------------------------------
class TypePointer: public Spec{
 public:
   TypePointer();
   TypePointer(Spec*baseType);
   Spec* getBaseType() const;

 private:
  Spec*baseType;
};
// struct -----------------------------------------------
// no need to separate struct and union?
class TypeStruct: public Spec{
 public:
  TypeStruct();
  void addMember(std::string name, Spec* type);
  Spec* findMember(std::string name);
 private:
  std::map<std::string, Spec*> members;
};
// union -----------------------------------------------
// no need to separate struct and union?
class TypeUnion: public Spec{
 public:
  TypeUnion();
  void addMember(std::string name, Spec* type);
  Spec* findMember(std::string name);
 private:
  std::map<std::string, Spec*> members;
};

#endif