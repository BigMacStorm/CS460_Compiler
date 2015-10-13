#include <stdio.h>

struct myStruct{ // define myStruct in struct name space
  int type;
};

// adds a type alias myStruct in the global name space
typedef struct myStruct myStruct;

typedef struct myStruct2{int type;} myStruct3;

void myStruct2(void){printf("myStruct2\n");}
// error void myStruct3(void){printf("myStruct3\n");}

int main(){

  struct myStruct st1;
  myStruct st2;
  struct myStruct2 st3;
  myStruct3 st4;
  myStruct2();

  return 0;
}