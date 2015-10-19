signed int si = -10;
const double cd = 1.4;
volatile double vd = 2.5;
const volatile int cvi = 0;
static const volatile float scvf = 2.0;
static const volatile signed long long int scvsll;

long static const unsigned int lscui[];
extern double long edl[10];
float f2d[20];
int i3d[2][2][2];

int foo();
unsigned int boo(float x, long double z);
void zoo(int a, register unsigned int b){
  int x, y;
  //!!S
}

struct s1{
  long int x;
  int y;
  struct s11{
    int x1;
    int y1;
  }str11;
  //!!S
}str1;

union u1{
  int x;
};

int main(){
  int *ip;
  int **ipp;

  int i1, i2[10], *i3;

  //!!S
  return 0;
}