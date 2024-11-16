#include<stdio.h>
 void sparse(int A[10][10],int m, int n)
 {
 int SPB[15][3],i,j,k=1;
 SPB[0][0]=m;
 SPB[0][1]=n;
 for(int i=0;i<m;i++)
 {
 for(j=0;j<n;j++)
 {
     printf("%d ",A[i][j]);
 }
 printf("\n");
 }

 for(int i=0;i<m;i++)
 {
 for(j=0;j<n;j++)
 {
 if(A[i][j]!=0)
 {
 SPB[k][0]=i;
 SPB[k][1]=j;
 SPB[k][2]=A[i][j];
 k++;
 }
 }
 }
 SPB[0][2]=k-1;
 for(i=0;i<=SPB[0][2];i++)
 {
 printf("%d %d %d",SPB[i][0],SPB[i][1],SPB[i][2]);
 }
 }

int main()
 {
 int B[10][10],r,c;
 printf("Enter the number of rows and coulms");
 scanf("%d%d",&r,&c);
 printf("Enter the numbrs in the matrix");
 for(int w=0;w<r;w++)
 {
 for(int z=0;z<c;z++)
 {
 scanf("%d",&B[w][z]);
 }
 }
 sparse(B,r,c);
 }
