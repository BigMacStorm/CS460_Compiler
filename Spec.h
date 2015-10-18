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
   Char, //UChar, SChar,
   Int, //UInt,
   Short, //UShort,
   Long, //ULong,
   LLong, //ULLong,
   Float,
   Double,
   LDouble
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
  virtual ~Spec();
  virtual std::string toString() const;
  std::string getTypeKindStr() const;
  std::string getStorageClassStr() const;
  std::string getTypeQualifierStr() const;
  std::string getSignStr() const;

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

  SpecName::BaseType baseType;
};

// basic -----------------------------------------------
class TypeBasic: public Spec{
 public:
  TypeBasic(SpecName::Storage = SpecName::NoStorage, SpecName::Qualifier = SpecName::NoQualifier, SpecName::Sign = SpecName::NoSign);
  std::string toString() const;
  std::string getTypeName() const;
  std::string getBaseTypeStr() const;
  SpecName::BaseType getBaseType() const;
  std::string basetToStr(SpecName::BaseType basetype) const;
  void setBaseType(SpecName::BaseType baseType);
  bool isBase(SpecName::BaseType baseType);
 private:
  SpecName::BaseType baseType;
};

// enum -----------------------------------------------
class TypeEnum: public Spec{
 public:
   TypeEnum(SpecName::Storage = SpecName::NoStorage,SpecName::Qualifier = SpecName::NoQualifier, SpecName::Sign = SpecName::NoSign);
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
   TypeArray(SpecName::Storage = SpecName::NoStorage,SpecName::Qualifier = SpecName::NoQualifier, SpecName::Sign = SpecName::NoSign);
   std::string toString() const;
   std::string getElemType() const;
   int getSize(int n) const;
   int getDim() const;
   void setElemType(std::string elemType);
   void setArraySizes(std::vector<int> &arraysizes);

 private:
  std::string elemType;
  std::vector<int> arraySizes;
};
// function -----------------------------------------------
class TypeFunction : public Spec{
public:
    TypeFunction(SpecName::Storage = SpecName::NoStorage,SpecName::Qualifier = SpecName::NoQualifier, SpecName::Sign = SpecName::NoSign);
    void insertArg(Spec*argType);
    void setReturnType(Spec* returnType);
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
   TypeTypeName(SpecName::Storage = SpecName::NoStorage,SpecName::Qualifier = SpecName::NoQualifier, SpecName::Sign = SpecName::NoSign);
   TypeTypeName(Spec* baseSpec);
   Spec* getBaseSpec() const;

 private:
  Spec*baseSpec;
};

// pointer -----------------------------------------------
class TypePointer: public Spec{
 public:
   TypePointer(SpecName::Storage = SpecName::NoStorage,SpecName::Qualifier = SpecName::NoQualifier, SpecName::Sign = SpecName::NoSign);
   std::string toString() const;
   std::string getTargetType() const;
   int getLevels() const;
   void setTargetType(std::string targetType);
   void setLevels(int levels);
   void incLevel();

 private:
 std::string targetType;
 int levels;
};
// struct -----------------------------------------------
// no need to separate struct and union?
class TypeStruct: public Spec{
 public:
  TypeStruct(SpecName::Storage = SpecName::NoStorage,SpecName::Qualifier = SpecName::NoQualifier, SpecName::Sign = SpecName::NoSign);
  void addMember(std::string name, Spec* type);
  Spec* findMember(std::string name);
 private:
  std::map<std::string, Spec*> members;
};
// union -----------------------------------------------
// no need to separate struct and union?
class TypeUnion: public Spec{
 public:
  TypeUnion(SpecName::Storage = SpecName::NoStorage,SpecName::Qualifier = SpecName::NoQualifier, SpecName::Sign = SpecName::NoSign);
  void addMember(std::string name, Spec* type);
  Spec* findMember(std::string name);
 private:
  std::map<std::string, Spec*> members;
};

#endif