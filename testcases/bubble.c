void swap(int* item1, int* item2);
void bubble(int array[], int size);

int main(){
  int idx = 0;
  const int SIZE = 10;
  int array[SIZE] = {6,-128,100,7,-2,0,21,85,21,54};

  bubble(array, SIZE);
  return 0;
  //!!S
}

void bubble(int array[], int size){
  int idx1 = 0;
  int idx2 = 0;
  for(idx1 = 0; idx1 < size-1; idx1++){
    for(idx2 = 0; idx2 < size-idx1-1; idx2++){
      if(array[idx2] > array[idx2+1]){
        swap(&array[idx2], &array[idx2+1]);
      }
    }
  }
  //!!S
}
void swap(int* item1, int* item2){
  int temp = *item1;
  *item1 = *item2;
  *item2 = temp;
  //!!S
}