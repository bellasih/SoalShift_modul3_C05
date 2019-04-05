#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int status;
pthread_mutex_t lock;

void* get_list(void* ptr){
    int val = *((int *) ptr);
    if(val == 1) {
        system("ps -aux | head -11 | tail -10  > ~/Documents/FolderProses1/SimpanProses1.txt");
    }
    else if(val == 2){
        system("ps -aux | head -11 | tail -10  > ~/Documents/FolderProses2/SimpanProses2.txt");
    }
    status--;
    return NULL;
}

void* zip_rm(void* ptr){
    int val = *((int *) ptr);
    if(val == 1){
        system("zip -j ~/Documents/KompresProses1.zip ~/Documents/FolderProses1/SimpanProses1.txt");
        system("rm ~/Documents/FolderProses1/SimpanProses1.txt");
    }
    else if(val == 2){
        system("zip -j ~/Documents/KompresProses2.zip ~/Documents/FolderProses2/SimpanProses2.txt");
        system("rm ~/Documents/FolderProses2/SimpanProses2.txt");
    }
    status--;
    return NULL;
}

void* unzip(void* ptr){
    int val = *((int *) ptr);
    if(val == 1){
        system("unzip ~/Documents/KompresProses1.zip -d ~/Documents/FolderProses1/");
    }
    else if(val == 2){
        system("unzip ~/Documents/KompresProses2.zip -d ~/Documents/FolderProses2/");
    }
    status--;
    return NULL;
}

int main(){
    pthread_t tid[6];
    int err,j=0;
    status=2;
    for(int i=0; i<2;i++){
        int *num = malloc(sizeof(*num));
        *num = ++j;
        printf("%d\n",j);
        err=pthread_create(&tid[i],NULL,get_list,num);
    }
    while(status);

    status=2; j=0;
    for(int i=2;i<4;i++){
        int *num = malloc(sizeof(*num));
        *num = ++j;
        printf("%d\n",j);
        err=pthread_create(&tid[i],NULL,zip_rm,num);
    }
    while(status);

    printf("Menunggu 15 detik untuk mengekstrak kembali\n");
    sleep(15);
    status=2; j=0;
    for(int i=4;i<6;i++){
        int *num = malloc(sizeof(*num));
        *num = ++j;
        printf("%d\n",j);
        err=pthread_create(&tid[i],NULL,unzip,num);
    }
    while(status);

    exit(EXIT_SUCCESS);
}
