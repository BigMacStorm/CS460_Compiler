/*
Every
1. variable
2. function
has one of these storage classes

Storage class     Lifetime             Visibility
extern            program execution   external (whole program)
static            program execution   internal (translation unit only)
auto, register    function execution  (none)

Declaration without the storage class:
1. extern for all top-level declarations in a source file
2. auto for variables declared in function bodies.

register variable:
- A special case of automatic variable
- It suggests to the compiler that particular auto variables should be allocated to CPU registers instead of RAM, if possible.
- The variable has a maximum size equal to the register size (usually one word) and cant have the unary '&' operator applied to it (as it does not have a memory location).
- For most computers, accessing data in memory is considerably slower than processing in the CPU. Variables which are used repeatedly or whose access times are critical, may be declared to be of storage class register

static variable
- it is only initialized at the beginning of program execution

 */

#include <stdio.h>
int count(){
  static int inc;
  return inc++;
}
int main(){
  int ctr;
  for(int ctr = 0; ctr < 10; ctr++){
    printf("%d\n",count());
  }
}