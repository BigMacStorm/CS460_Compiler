#ifndef __TYPE__H__
#define __TYPE__H__
#include <iostream>

namespace TypeName{
  enum TypeKind{
    Char, UChar, SChar, Int, UInt, Short, UShort, Long, ULong, LLong, ULLong,
    Float, Double, LDouble,
    Pointer, Array, Struct, Union, Function, Void, Enum, Typedef
  };
  enum Storage{
    Extern, Static, Auto, Register
  };
  enum Qualifier{
    Const, Volatile, NoQualifier
  };
};

class Type{
public:
  Type(TypeName::TypeKind, TypeName::Storage, TypeName::Qualifier);
  std::string getTypeKindStr();
  std::string getStorageClassStr();
  std::string getTypeQualifierStr();
  TypeName::TypeKind typekind;
  TypeName::Storage storage;
  TypeName::Qualifier qualifier;
};
#endif