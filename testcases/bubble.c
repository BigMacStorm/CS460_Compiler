void bubble(int array[], int size){
  int idx1 = 0;
  int idx2 = 0;
  int temp;
  for(idx1 = 0; idx1 < size-1; idx1++){
    for(idx2 = 0; idx2 < size-idx1-1; idx2++){
      if(array[idx2] > array[idx2+1]){
        temp = array[idx2];
        array[idx2] = array[idx2+1];
        array[idx2+1] = temp;
      }
    }
  }
  //!!S
}
int main(){
  int array[10] = {6,-128,100,7,-2,0,21,85,21,54};
  bubble(array, 10);
  return 0;
  //!!S
}