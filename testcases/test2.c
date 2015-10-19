int main(){
  int foo();
  int x = foo();
  return 0;
}

int foo(){
  int y = 10;
  return y * y;
}