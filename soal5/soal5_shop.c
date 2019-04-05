#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <termios.h> //terminate I/O
#include <string.h>

char param = {'\0'}; //set bit 0
int *sf_stock;
pthread_t tid[2];

void* shop_scene_m();
void* restock();
char choice_getch();

int main(){
    pthread_create(&tid[0],NULL,shop_scene_m,NULL);
    int i=1;
    int p;

    //create shared memory
    key_t key = 1234;
    int shm = shmget(key,sizeof(int),IPC_CREAT|0666);
    sf_stock = shmat(shm,NULL,0);

    //read from input
    while((param = choice_getch())!=EOF && i){
        p=param;
        if(p == 50) i=0;
        else if(p == 49) pthread_create(&tid[1],NULL,restock,NULL);
        
    }
    exit(EXIT_SUCCESS);
}

void* shop_scene_m(){
    while(1){
        printf("Shop\n");
        printf("Food stock : %d\nYour food stock\n",*sf_stock);
        printf("Choices\n1. Buy\n2. Back\n");
        sleep(2);
        system("clear");
    }
}

void* restock(){
    *sf_stock+=1;
}

//internet
char choice_getch(){
    char character;
    struct termios oldt;
    struct termios newt;
    tcgetattr(STDIN_FILENO, &oldt);             //store old settings
    newt = oldt;                                // copy old settings to new settings
    newt.c_lflag &= ~(ICANON | ECHO);           // make one change to old settings in new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);    // apply the new settings immediatly
    scanf("%c",&character);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);    // reapply the old settings
    return character;
}
