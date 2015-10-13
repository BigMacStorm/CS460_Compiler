#include <stdio.h>

int a = 100;
int b = 1000;

int main(){
  int x = 0;
  int y = 0;
  int z = 0;

  {
    int c = 1;
    x = a;
    z = 3;
  }

  {
    int a; // shadow the global variable a
    a = 1;
  }

  // printf("%d\n", a); error can't access a

  printf("%d: %d: %d: %d: %d\n",a,b,x,y,z);
}