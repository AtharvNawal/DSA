#include <stdio.h>
#include <stdlib.h>
#define MAX 999
 
void linearProbing(int arr[], int n){
   int table[n];
   int filled[n];
   int hash, collisions=0, k;
   
   for(int i = 0; i < n; i++)
       table[i] = -1;
       
   for(int i = 0; i < n; i++)

       filled[i] = 0;
   
   for(int i = 0; i<n; i++){
       k = 0;
       hash = (arr[i]+k)%n;
       
       while(filled[hash]==1){
           k++;
           hash = (arr[i]+k)%n;
       }
       table[hash] = arr[i];
       filled[hash] = 1;
       
       collisions+=k;
   }    
   
   printf("\nTotal Collisions with linear probing %d\n", collisions);
   printf("Hash Table with linear probing:\n");
   for(int i = 0; i<n; i++){
       printf("%d : %d\n", i, table[i]);
   }
   
   return;
}
 
void quadraticProbing(int arr[], int n) {
   int table[n];
   int filled[n];
   int hash, collisions = 0, k;
 
   for(int i = 0; i < n; i++)
       table[i] = -1;
       
   for(int i = 0; i < n; i++)
       filled[i] = 0;
 
   for(int i = 0; i < n; i++) {
       k = 0;
       hash = (arr[i] + k * k) % n;
       
       while(filled[hash] == 1) {
           k++;
           hash = (arr[i] + k * k) % n;
       }
       table[hash] = arr[i];
       filled[hash] = 1;
       
       collisions += k;
   }
 
   printf("\nTotal Collisions with quadratic probing: %d\n", collisions);
   printf("Hash Table with quadratic probing:\n");
   for(int i = 0; i<n; i++){
       printf("%d : %d\n", i, table[i]);
   }
   
   return;
}
 
void doubleHashing(int arr[], int n) {
   int table[n];
   int filled[n];
   int hash, collisions = 0, k, secondHash;
 
   for(int i = 0; i < n; i++)
       table[i] = -1;
       
   for(int i = 0; i < n; i++)
       filled[i] = 0;
 
   for(int i = 0; i < n; i++) {
       k = 0;
       secondHash = 7 - (arr[i] % 7);
       hash = (arr[i] + k * secondHash) % n;
       
       while(filled[hash] == 1) {
           k++;
           hash = (arr[i] + k * secondHash) % n;
       }
       table[hash] = arr[i];
       filled[hash] = 1;
       
       collisions += k;
   }
 
   printf("\nTotal Collisions with double hashing: %d\n", collisions);
   printf("Hash Table with double hashing:\n");
   for(int i = 0; i<n; i++){
       printf("%d : %d\n", i, table[i]);
   }
   
   return;
}
 
int main(){
   int n, s, arr[MAX];
   printf("Enter the number of elements: ");
   scanf("%d", &n);
   for(int i = 0; i<n; i++){
       scanf("%d", &arr[i]);
   }
   
   linearProbing(arr, n);
   quadraticProbing(arr, n);
   doubleHashing(arr, n);
}