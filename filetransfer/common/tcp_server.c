/*************************************************************************
	> File Name: tcp_server.c
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年03月30日 星期一 00时19分42秒
 ************************************************************************/

#include "head.h"

int socket_create(int port) {
    int server_listen;
    if((server_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;

    struct linger m_linger;
    m_linger.l_onoff = 1;
    m_linger.l_linger = 5;
    if(setsockopt(server_listen, SOL_SOCKET, SO_LINGER, &m_linger, (socklen_t)sizeof(m_linger)) < 0) {
        return -1;
    }
    int flag = 1;
    if(setsockopt(server_listen, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int)) < 0) {
        return -1;
    }
    if(bind(server_listen, (struct sockaddr *)&server, sizeof(server)) < 0) {
        return -1;
    }
    if(listen(server_listen, 20) < 0) {
        return -1;
    }
    return server_listen;
}
