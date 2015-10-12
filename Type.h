#ifndef __TYPE__H__
#define __TYPE__H__
#include <iostream>
#include <vector>
#include <map>
#include <sstream>

namespace TypeName{
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
};

class Type{
public:
  Type(TypeName::TypeKind = TypeName::NoKind, TypeName::Storage = TypeName::NoStorage,
    TypeName::Qualifier = TypeName::NoQualifier);
  std::string getTypeStr() const;
  virtual std::string getTypeKindStr() const;
  std::string getStorageClassStr() const;
  std::string getTypeQualifierStr() const;
  void setTypeKind(TypeName::TypeKind typekind);
  void setStorage(TypeName::Storage storage);
  void setQualifier(TypeName::Qualifier qualifier);

protected:
  TypeName::TypeKind typekind;
  TypeName::Storage storage;
  TypeName::Qualifier qualifier;
};

// basic -----------------------------------------------
class TypeBasic: public Type{
 public:
  TypeBasic(TypeName::BaseType baseType = TypeName::NoType);
  std::string getTypeKindStr() const;
  void setBaseType(TypeName::BaseType baseType);
 private:
  TypeName::BaseType baseType;
};

// enum -----------------------------------------------
class TypeEnum: public Type{
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
class TypeArray: public Type{
 public:
   TypeArray();
   TypeArray(Type *elemType, int size);
   Type* getElemType() const;
   int getSize() const;

 private:
  Type *elemType;
  int size;
};
// function -----------------------------------------------
class TypeFunction : public Type{
public:
    TypeFunction();
    TypeFunction(Type *returnType);
    void insertArg(Type *argType);
    Type* getReturnType() const;
    int getArgSize() const;
    Type* getArgType(int nth) const;

  private:
    Type * returnType;
    std::vector<Type*> argTypes;
};
// TypeName -----------------------------------------------
class TypeTypeName: public Type{
 public:
   TypeTypeName();
   TypeTypeName(Type *baseType);
   Type* getBaseType() const;

 private:
  Type *baseType;
};

// pointer -----------------------------------------------
class TypePointer: public Type{
 public:
   TypePointer();
   TypePointer(Type *baseType);
   Type* getBaseType() const;

 private:
  Type *baseType;
};
// struct -----------------------------------------------
// no need to separate struct and union?
class TypeStruct: public Type{
 public:
  TypeStruct();
  void addMember(std::string name, Type* type);
  Type* findMember(std::string name);
 private:
  std::map<std::string, Type*> members;
};
// union -----------------------------------------------
// no need to separate struct and union?
class TypeUnion: public Type{
 public:
  TypeUnion();
  void addMember(std::string name, Type* type);
  Type* findMember(std::string name);
 private:
  std::map<std::string, Type*> members;
};

#endif