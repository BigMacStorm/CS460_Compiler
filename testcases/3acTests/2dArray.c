int main(){
    int twoD[3][4] = {0,1,2,3,4,5,6,7,8,9,10,11};
    int hold;
    
    hold = twoD[1][2];
    hold = twoD[2][3] + twoD[0][3];
    hold = twoD[0][1] * hold;
    
    return 0;
}
    
