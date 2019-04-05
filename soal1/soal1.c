#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define MOD 1000000007

pthread_t tid[100001];
int arr[100001],st;
long long int fact[100001]={0};

void merge(int l, int m, int r){ 
    int n1 = m - l + 1, n2 =  r - m; 
    int L[n1], R[n2],i,j,k; 

    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 

    i = 0; j = 0; k = l; 
    while (i < n1 && j < n2){ 
        if (L[i] <= R[j]){ 
            arr[k] = L[i]; 
            i++; 
        } 
        else{ 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) { 
        arr[k] = L[i]; 
        i++; k++; 
    } 
    while (j < n2) { 
        arr[k] = R[j]; 
        j++; k++; 
    } 
}

void merge_sort(int l, int r){
    if (l < r) { 
        int m = l+(r-l)/2; 
        merge_sort(l, m); 
        merge_sort(m+1, r); 
        merge(l, m, r); 
    } 
}

void* factorial(void *ptr){
    int i=2;
    int val = *((int *) ptr);
    while( i <= val){
        fact[i]=((fact[i-1]%MOD)*(i%MOD))%MOD;
        i++;
    }
    return NULL;
}

int main(int argc, char *argv[]){
    int T=0,err,j=1,i=1,k;
    fact[0]=1; fact[1]=1;
    for(k=1;k<argc;k++){
        arr[k]=atoi(argv[k]);
    }
    merge_sort(0,k-1);
    while(i<argc){
        int *num = malloc(sizeof(*num));
        *num = arr[i];
        err = pthread_create(&tid[i],NULL,factorial,num);
        i++;
    }
    while(j<argc){
        pthread_join(tid[j],NULL);
        j++;
    }
    for(i=1;i<argc;i++){
        printf("%d! = %lld\n",arr[i],fact[arr[i]]);
    }
    exit(EXIT_SUCCESS);
}
