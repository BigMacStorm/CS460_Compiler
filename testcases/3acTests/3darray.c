int main(){
  int arr[10][10][10];
  int idx1,idx2,idx3;
  for(idx1 = 0; idx1 < 10; ++idx1){
    for(idx2 = 0; idx2 < 10; ++idx2){
      for(idx3 = 0; idx3 < 10; ++idx3){
        arr[idx1][idx2][idx3] = idx1*idx2*idx3;
      }
    }
  }

  arr[1][2][3] = arr[9][9][9] * 2;
}