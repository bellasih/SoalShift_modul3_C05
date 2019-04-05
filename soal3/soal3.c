#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

int agmal_wstatus = 0, iraj_sstatus=100;
int status[2]={0}, rs_iraj=0, rs_agmal=0; //status[0] for wakeup, status[1] for sleep
pthread_t tid[3];

void* sleep_iraj(void* ptr);
void* wakeup_agmal(void* ptr);
void menu();
void decission(char urut[1001]);

int main(){
    char urut[1001];
    printf("Gambaran hidup Iraj dan Agmal\n");
    pthread_create(&tid[0],NULL,sleep_iraj,status);
    pthread_create(&tid[1],NULL,wakeup_agmal,status);
    
    while(agmal_wstatus < 100 && iraj_sstatus > 0){
        while(rs_agmal || rs_iraj);
        if(status[0] == 3 || status[1] == 3) sleep(1),menu();
        else menu();
        fgets(urut,1001,stdin);
        decission(urut);
    }

    if(agmal_wstatus > 99) printf("Agmal Terbangun, mereka bangun pagi dan berolahraga\n");
    else if(iraj_sstatus < 1) printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
}

void* sleep_iraj(void* ptr){
    while(1){
        int* val = (int* ) ptr;
        if(val[0]==3){
            printf("Fitur Iraj Ayo tidur disabled 10 s\n");
            sleep(10);
            status[0]=0; rs_iraj=0;
            continue;
        }
        if(rs_iraj==0) continue;
        if(val[0]<3){
            iraj_sstatus-=20;
            status[1]+=1;
        }
        rs_iraj=0;
    }
}

void* wakeup_agmal(void* ptr){
    while(1){
        int *val = (int* ) ptr;
        if(val[1]==3){
            printf("Agmal Ayo Bangun disabled 10 s\n");
            sleep(10);
            status[1]=0; rs_agmal=0;
            continue;
        }
        if(rs_agmal==0) continue;
        if(val[1]<3){
            agmal_wstatus+=15;
            status[0]+=1;
        }
        rs_agmal=0;
    }
}

void menu(){
    printf("List command :\n");
    printf("- All status\n- Agmal Ayo Bangun\n- Iraj Ayo Tidur\n");
    printf("Enter command : ");
}

void decission(char urut[1001]){
    if(strcmp(urut,"All status\n")==0){
        printf("Agmal Wakeup_Status = %d\n",agmal_wstatus);
        printf("Iraj Spirit_Status = %d\n",iraj_sstatus);
    }
    if(strcmp(urut,"Iraj Ayo Tidur\n")==0 && status[0]<3 ){ rs_iraj=1; }
    if(strcmp(urut,"Agmal Ayo Bangun\n")==0 && status[1]<3) { rs_agmal=1; }
    printf("\n\n");
}
