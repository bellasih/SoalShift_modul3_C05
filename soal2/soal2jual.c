#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define PORT_S 8080

int *n,st=0;
pthread_t tid[2];

void* display_stock(){
    while(1){
        printf("Stock : %d\n",*n);
        sleep(5);
    }
}

void* selling(void *ptr){
    int sock_client = *((int *) ptr);
    int size_of_read;
    char client_ms[1024], message[1024];
    while(size_of_read=read(sock_client,client_ms,1024)){
        if(!strcmp(client_ms,"tambah")){
            *n = *n + 1;
        } 
        memset(message,0,sizeof(message));
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

    int err = pthread_create(&tid[0],NULL,display_stock,NULL);

    key_t key = 1234;
    int shm = shmget(key,sizeof(int),IPC_CREAT|0666);
    n = shmat(shm,NULL,0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT_S );

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
            int err = pthread_create(&tid[1], NULL , selling, (void*) &new_socket);
            write(new_socket , buffer , strlen(buffer));
            st++;
        }
    }
}
