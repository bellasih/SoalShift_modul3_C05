#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int *sf_stock;
int npc_health=100;
int st_hygiene=100;
int st_health=300;
int st_hunger=200;
int st_foods=0;
int current=1;
pthread_t tid[8];
char monster[1024],character;

void get_name();
void* regeneration();
void* standby_mode();
void* battle_mode();
void* shop_scene_m();
void* opt1();
void* opt2();
char choice_getch();

int main(){
    //shared memory
    key_t
    int shm = shmget(key,sizeof(int),IPC_CREAT|0666);
    sf_stock = shmat(shm,NULL,0);
    
    void get_name();
    pthread_create(&tid[0],NULL,standby_mode,NULL);
    pthread_create(&tid[1],NULL,battle_mode,NULL);
    pthread_create(&tid[2],NULL,shop_scene_m,NULL);
    pthread_create(&tid[3],NULL,regeneration,NULL);
    pthread_create(&tid[4],NULL,opt1,NULL);
    pthread_create(&tid[5],NULL,opt2,NULL);

    while(1){
        
    }
}

void get_name(){
    printf("please insert monstername :");
    fgets(monster,1024,stdin);
}

void* regeneration(){
    while(1){
        health+=5;
        sleep(10);
    }
}

void* standby_mode(){
    printf("Standby Mode\n");
    printf("Health : %d\nHunger : %d\nHygiene : \nFood left : ",st_health,st_hunger,st_hygiene,st_foods);
    printf("Bath will ready in %ds\n");
    printf("Choices\n1. Eat\n2. Bath\n3. Battle\n4. Shop\n5. Exit\n");
}

void* battle_scene(){
    printf("Battle Mode\n");
    printf("Monster's Health : %d\nEnemy's Health : %d\n",st_health,e_health);
    printf("Choices\n1. Attack\n2. Run\n");
}

void* shop_scene_m(){
    printf("Shop Mode\n");
    printf("Shop food stock : %d\nYour food stock\n",sf_stock,st_foods);
    printf("Choices\n1. Buy\n2. Back\n");
}

void* opt1(){
    while(1){
        hygine-=10;
        sleep(30);
    }
}

void* opt2(){
    while(1){
        hunger-=5;
        sleep(10);
    }
}

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
