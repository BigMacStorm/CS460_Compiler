int a = 100;
int b = 1000;

!!S

int main(){
  int x = 0;
  int y = 0;
  int z = 0;

!!S
  {
    int c = 1;
    x = a;
    z = 3;
    !!S
  }

  {
    int a; // shadow the global variable a
    a = 1;
    !!S
  }
  !!S
}