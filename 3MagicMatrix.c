#include<stdio.h>

int main()
{
    int a[3][3], i, j, sumd1=0, sumd2=0, f=0, sumr=0, sumc=0;
//user input for requied elements(matix) to check magic matrix
    printf("Enter matrix elements:");
    for(i=0; i<3; i++)  //row
    {
        for(j=0; j<3; j++)  //col
            scanf("%d",&a[i][j]);
    }

//sum of digonal elements
    for(i=0; i<3; i++)  
    {
        for(j=0; j<3; j++)  
        {
            if (i==j)
                sumd1 += a[i][j];

            if (i+j==3-1)   //row or col size -1, in this case col or row size is 3
                sumd2 += a[i][j];
        }
    } 
    if(sumd1 != sumd2)
        f=1;
    else
    {
    for(i=0; i<3; i++)  
    {
        sumc=0; 
        sumr=0;
        for(j=0; j<3; j++)  
        {
            sumr += a[i][j];
            sumc += a[j][i];
        }
        if(sumc != sumd1 || sumr != sumd1)
            f=1;
        else
            f=0;
    }
    }
    if(f==0)
        printf("It is Magic Square Matrix.");
    else
        printf("NOT Magic Square Matrix.");
}