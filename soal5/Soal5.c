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

pthread_t tid1;
pthread_t tid2;
pthread_t tid3;
pthread_t tid4;

char xplayer[10];//nama monster
char opsi;
int hunger = 100;//nilai awal (max 200)
int hygiene = 100;//nilai awal
int health = 300;//nilai awal
int zblood = 100;//untuk battle
//int stok_toko = 5; //TOKO
int stok = 45; //stok monster
int turn = 0;

int getch(void){//https://gist.github.com/jerry2yu/2591964
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

void *lapar(void *arg){
	while(1){// -5 per 10 detik
		hunger -= 20;
        sleep(1);
	}
}

void *kotor(void *arg){
	while(1){// -10 per 30 detik
		hygiene -= 10;
        sleep(30);
	}
}

void *sehat(void *arg){
	while(1){ // +5 per 10 detik
		health += 5;
		sleep(10);
	}
}

void *waktu(void *arg){
	while(1){// timer ready or not
		if(turn > 0){
			turn--;
            sleep(1);
		}
	}
}

void battle(){
	while(1){
	    printf("MONSTER %s VS. MONSTER NPC \n", xplayer);
	    printf("HEALTH STATUS: %d\n", health);
	    printf("HUNGER STATUS: %d\n", hunger);
	    printf("STOK MAKANAN MONSTER: %d\n", stok);
	    printf("OPSI: 1. SERANG\t2. LARI\n");
	    
        opsi = getch();

	    //int turn = 1;
	    if(opsi == '1'){
		    health -= 20;//pemain
		    zblood -= 20;//lawan
    	    if(zblood <= 0){//jika lawan kehabisan darah
		        printf("\nGame telah selesai!\n");
			    printf("Skor Akhir: \n");
			    printf("%s hunger status: %d | hygiene status: %d\n", xplayer, hunger, hygiene);
				sleep(5);
		        break;
	        }
        }
	    if(opsi == '2'){
		    break;
	    }
        system("clear");
    }
}

void shop_buyer(){
    key_t key = 1234;
    int *stok_toko;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    stok_toko = shmat(shmid, NULL, 0);

    while(1){
    	printf("SHOP\n");
	    printf("STOK MAKANAN TOKO: %d\n", *stok_toko);
	    printf("STOK MAKANAN MONSTER: %d\n", stok);
	    printf("OPSI: 1. BUY\t2. BACK\n");    
        opsi = getch();
	    if(opsi == '1'){
            if(*stok_toko > 0){//toko masih punya stok
    		    stok += 15;
		        *stok_toko -= 15;
                printf("STOK MAKANAN MONSTER: %d\n", stok);
            }
            else{
                system("clear");
                printf("MAKANAN TOKO HABIS\n");
            }
        }
	    if(opsi == '2'){
		    break;
	    }
	    system("clear");
    }
    shmdt(stok_toko);
    shmctl(shmid, IPC_RMID, NULL);
}

// x -> PEMAIN
void xplay(){
	while(1){
		//if(opsi == '1'){
		printf("MONSTER DALAM KEADAAN STANDBY\n");
		printf("HEALTH STATUS: %d\n", health);
		printf("HUNGER STATUS: %d\n", hunger);
		printf("STOK MAKANAN MONSTER: %d\n", stok);
		printf("MANDI?? \n");
		if(turn == 0){printf("BATH IS READY\n");}
        else{printf("BATH WILL BE READY IN %d\n", turn);}
		printf("OPSI: 1. KASIH MAKAN\t2. MANDI\t3. BATTLE\t4. SHOP\t5. EXIT\n");
        opsi = getch();

		if(opsi == '1'){
            if(stok > 15){//liat stok masih sisa
    			if(stok-15 >= 0 && hunger+15 <= 200){//batas max 200
	    			hunger += 15;
		    		stok -= 15;
		    	}
			    else{
				    printf("SUDAH MAKSIMUM.\n");
			    }
		    }
            else{
                printf("STOK MAKANAN HABIS.\n");
            }
        }
		if(opsi == '2'){
            if(hygiene < 100){
                if(turn == 0){
                    hygiene += 30;
                    if(hygiene > 100){
                        hygiene = 100;
                    }
                    turn = 20; //mandi ready dlm 20 dtk
                }   
            }else{ //timer blm selesai
                system("clear");
                printf("NOT READY\n");
                sleep(1);
                system("clear");
            }
		}
		if(opsi == '3'){
            system("clear");
			battle();
		}
		if(opsi == '4'){
            system("clear");
			shop_buyer();
		}
		if(opsi == '5'){
			break;
		}
        /*}
		if(opsi == '2'){
			battle();
		}
		if(opsi == '3'){
			shop_buyer();
		}*/
		if(hunger <= 0 || hygiene <= 0){
			printf("\nGame telah selesai!\n");
			printf("Skor Akhir: \n");
			printf("%s hunger status: %d | hygiene status: %d\n", xplayer, hunger, hygiene);
			sleep(5);
            //exit(EXIT_FAILURE);
            break;
        }
        system("clear");
	    //break;
    }
}

int main(void){
	printf("Let's start:\n");
    printf("MONSTER'S NAME: ");
    scanf("%s", xplayer);
    
    printf("STANDBY\n");
	printf("BATTLE\n");
   	printf("SHOP\n");

   	pthread_create(&(tid1), NULL, &lapar, NULL);
   	pthread_create(&(tid2), NULL, &kotor, NULL);
    pthread_create(&(tid3), NULL, &sehat, NULL);
   	pthread_create(&(tid4), NULL, &waktu, NULL);
	
   	//pthread_join(tid1,NULL); pthread_join(tid2, NULL); pthread_join(tid3, NULL); pthread_join(tid4, NULL);
	
	xplay();
}
