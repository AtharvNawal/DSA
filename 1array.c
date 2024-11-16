#include<stdio.h>
int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d",&n);
    int sum = 0;
    int s[20];
    printf("Enter %d elements: ",n);

    for(int i=0;i<n;i++) {
        scanf("%d",&s[i]);
        sum+=s[i];
    }
    int sum2 = (n*(n+1)/2);
    int result = sum - sum2;
    printf("%d",result);
}
