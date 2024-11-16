#include<stdio.h>
int main(){
    int rows,cols;
    printf("Enter number of rows and columns: ");
    scanf("%d %d",&rows,&cols);
int s[30][30];
for(int i=0;i<cols;i++){
    for(int j=0;j<rows;j++){
        scanf("%d",&s[i][j]);
    }
}
int max=0,c=0,min=0;
for(int i=0;i<rows;i++){
        max=0,min=0,c=0;
    for(int j=0;j<cols;j++){
        if(max<=s[i][j]){
            max=s[i][j];
            c=j;
        }
    }
min=max;
for(int k=0;k<rows;k++){
    if(min>=s[k][c]){
        min=s[k][c];
    }
}
if(max==min){
    printf("Saddle point in %d ",max);
}
}
}
