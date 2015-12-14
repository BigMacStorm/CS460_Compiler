int square(int x);
int sum(int x, int y);

int main(){
  int result;

  result = square(3);
  print_int(result);

  result = sum(3, 6);
  print_int(result);
}

int square(int x){
  int result1;
  result1 = x*x;
  return result1;
}

int sum(int x, int y){
  int result2;
  result2 = x + y;
  return result2;
}