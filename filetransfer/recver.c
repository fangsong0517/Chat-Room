/*************************************************************************
	> File Name: recver.c
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年04月02日 星期四 18时47分30秒
 ************************************************************************/

#include "./common/head.h"

#include "./common/tcp_server.h"

#include "./common/common.h"


struct FileMsg{
    long size;
    char name[50];
    char buf[4096];
};

void signal_process(int sig) {
    wait(NULL);
}

void child_do(int fd) {
    size_t recv_size, size = 0;
    struct FileMsg packet_t, packet, packet_pre;
    int packet_size = sizeof(struct FileMsg);
    int offset = 0, flag = 0, cnt = 0;
    long filesize;
    printf("Before recv!\n");
    /*while((recv_size = recv(fd,(void *)&packet_t, packet_size, 0)) > 0) {
        printf("recv_size = %ld\n", recv_size);
    }*/
    FILE *fp = NULL;
    while(1) {
        if(flag){
            memcpy(&packet, &packet_pre, flag);
            offset = flag;
        }
        flag = 0;
        while((recv_size = recv(fd, (void *)&packet_t, packet_size, 0)) > 0) {
            if(offset + recv_size == packet_size) {
                memcpy((char *)&packet + offset, &packet_t, recv_size);
                offset = 0;
                printf("整包!\n");
                break;
            } else if(offset + recv_size < packet_size) {
                memcpy((char *)&packet + offset, &packet_t, recv_size);
                offset += recv_size;
                printf("拆包\n"); 
            } else {
                memcpy((char *)&packet + offset, &packet_t, packet_size - offset);
                flag = recv_size-(packet_size - offset);
                memcpy(&packet_pre, (char *)&packet_t + packet_size - offset, flag);
                
                printf("粘包!\n");
                offset = 0;
                break;
            }
        }
        if(!cnt) {
            printf("recv %s : with size = %ld \n", packet.name, packet.size);
            if((fp = fopen(packet.name, "wb")) == NULL) {
                perror("fopen");
                break;
            }
        }
        cnt++;
        size_t write_size = 0;
        if(packet.size - size >= sizeof(packet.buf)){
            write_size = fwrite(packet.buf, 1, sizeof(packet.buf), fp);
        } else {
            write_size = fwrite(packet.buf, 1, packet.size - size, fp);
        }
        size += write_size;
        if(size >= packet.size) {
            printf("Finished: %s. \n", packet.name);
            break;
        }
    }
    close(fd);
    fclose(fp);
}

int main(int argc, char **argv) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s port!\n", argv[0]);
        return 1;
    }
    pid_t pid;
    int server_listen, port, fd;
    port = atoi(argv[1]);
    if((server_listen = socket_create(port)) < 0) {
        perror("socket_create");
        return 1;
    }
    signal(SIGCHLD, signal_process);
    while(1) {
        if((fd = accept(server_listen, NULL, NULL)) < 0) {
            perror("accept");
            continue;
        }
        printf("After arccept\n");
        if((pid = fork()) < 0) {
            perror("fork");
            continue;
        }
        if(pid == 0) {
            close(server_listen);
            child_do(fd);
            exit(0);
        } else {
            close(fd);
        }
    }


    return 0;
}

