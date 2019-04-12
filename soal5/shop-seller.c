#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<termios.h>
#include<assert.h>
#include<time.h>
#include<sys/ipc.h>
#include<sys/shm.h>

int getch(void){
    struct termios oldt,
    newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

void main(){
        key_t key = 1234;
        int *stok_toko;

        int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
        stok_toko = shmat(shmid, NULL, 0);

        *stok_toko = 45;
        
        while(1){
            printf("TOKO MAKANAN\n");
	        printf("STOK MAKANAN TOKO: %d\n", *stok_toko);
	        printf("OPSI: 1. RESTOCK\t2. EXIT\n");

            char opsi = getch();
            
            if(opsi == '1'){
                *stok_toko += 15;
            }
            if(opsi == '2'){
                break;
            }system("clear");
        }
        shmdt(stok_toko);
        shmctl(shmid, IPC_RMID, NULL);
}
