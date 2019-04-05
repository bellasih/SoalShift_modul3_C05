#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define PORT_B 7999

int *n,st=0;
pthread_t tid;

void* buying(void *ptr){
    int sock_client = *((int *) ptr);
    int size_of_read;
    char client_ms[2000];
    while(size_of_read=read(sock_client,client_ms,2000) != 0){
        if(!strcmp(client_ms,"beli")){
            if(*n>0){
                *n-=1;
                printf("%s\n",client_ms);
                char message[]="transaksi berhasil";
                write(sock_client,message,strlen(message));
            }
            else{
                printf("gagal beli karena stock habis\n");
                char message[]="transaksi gagal";
                write(sock_client,message,strlen(message));
            }
        } 
        memset(client_ms,0,sizeof(client_ms));
    }
    st--;
    close(sock_client);
}

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    key_t key = 1234;
    int shm = shmget(key,sizeof(int),IPC_CREAT|0666);
    n = shmat(shm,NULL,0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT_B );

    if (!(server_fd = socket(AF_INET, SOCK_STREAM, 0))) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))){
        if(st < 1){
            int err = pthread_create(&tid, NULL , buying, (void*) &new_socket);
            write(new_socket , buffer , strlen(buffer));
            st++;
        }
    }
}