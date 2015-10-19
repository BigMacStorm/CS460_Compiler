#include <stdio.h>
int main(){
  // base type checking -------------------------------------------------------
  // char (signed or unsigned)
  char c1 = 'C';

  // signed char
  signed char c2 = 67;

  // unsigned char
  unsigned char c3 = 67;

  // signed integer
  int i1 = 32767;
  signed i2 = -32767;
  signed int i3 = 65534;

  // unsigned integer
  unsigned i4 = 65534;
  unsigned int i5 = 65534;

  // short signed integer
  short i6 = 32767;
  short int i7 = 32767;
  signed short i8 = 32767;
  signed short int i9 = 32767;

  // short unsigned integer
  unsigned short  i10 = 65534;
  unsigned short int  i11 = 65534;

  // long signed integers
  long i12 = 2147483647;
  long int i13 = 2147483647;
  signed long i14 = -9223372036854775807;
  signed long int i15 = 9223372036854775807;

  // long unsigned integers
  unsigned long i16 = 0;
  unsigned long int i17 = 9223372036854775807;

  // long long signed integers
  long long i18 = -9223372036854775807;
  long long int i19 = -9223372036854775807;
  signed long long i20 = 9223372036854775807;
  signed long long int i21 = 9223372036854775807;

  // long long unsigned integers
  unsigned long long i22 = 9223372036854775807;
  unsigned long long int i23 = 9223372036854775807;

  // float
  float f1 = 3.40282e+38;

  // double
  double d1 = 1.79769e+308;

  // long double
  long double d2 = 1.79769e+308;

  // print out
  printf("%c\n", c1);
  printf("%c\n", c2);
  printf("%c\n", c3);

  printf("%i\n", i1);
  printf("%i\n", i2);
  printf("%i\n", i3);
  printf("%i\n", i4);
  printf("%i\n", i5);
  printf("%i\n", i6);
  printf("%i\n", i7);
  printf("%i\n", i8);
  printf("%i\n", i9);
  printf("%i\n", i10);
  printf("%i\n", i11);
  printf("%li\n", i12);
  printf("%li\n", i13);
  printf("%li\n", i14);
  printf("%li\n", i15);
  printf("%li\n", i16);
  printf("%li\n", i17);
  printf("%lli\n", i18);
  printf("%lli\n", i19);
  printf("%lli\n", i20);
  printf("%lli\n", i21);
  printf("%lli\n", i22);
  printf("%lli\n", i23);

  printf("%f\n", f1);
  printf("%f\n", d1);
  printf("%Lf\n", d2);

  return 0;
}