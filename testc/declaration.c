int main(){
  int; // warning: declaration does not declare anything [-Wmissing-declarations]
  // struct; error
  struct s;
  struct {int x;}; // warning: declaration does not declare anything [-Wmissing-declarations]
  struct s{ int x;};

  int a;
  int b, c, d;
  int e = 0, f = 1;
  int g, h = 2;

  int * p1;
  int * const p2;
  int * const p3;         // a constant pointer to int
  int * volatile p4;
  int * const volatile p5;
  int ** pp1;
  int * const * pp2;
  int * const * volatile * ppp1;
}