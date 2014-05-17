/* 
 * 本软件为免费、开源软件。
 * 本软件的版权(包括源码及二进制发布版本)归一切公众所有。
 * 您可以自由使用、传播本软件。
 * 您也可以以任何形式、任何目的使用本软件(包括源码及二进制发布版本)，而不受任何版权限制。
 * =====================
 * 作者: 孙明保
 * 邮箱: sunmingbao@126.com
 */

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>

#include "socket.h"

#define    ErrSysLog(fmt, args...)  do     {;} while (0)

char * get_ipstr(struct sockaddr_in *sock_addr, char *ip)
{
    char *tmp_ipstr=(char *)inet_ntoa(sock_addr->sin_addr);
    if (ip != NULL)
        strcpy(ip, tmp_ipstr);

    return tmp_ipstr;

}

uint16_t get_port(struct sockaddr_in *sock_addr, uint16_t *port)
{
    uint16_t tmp_port=ntohs(sock_addr->sin_port);
    if (port != NULL)
    *port=tmp_port;

    return tmp_port;
}

int sockaddr_equal(struct sockaddr_in *sock_addr1, struct sockaddr_in *sock_addr2)
{
    return (sock_addr1->sin_family == sock_addr2->sin_family) &&
        (sock_addr1->sin_port == sock_addr2->sin_port) &&
        (sock_addr1->sin_addr.s_addr == sock_addr2->sin_addr.s_addr);
}


void make_sockaddr(struct sockaddr_in *sock_addr, uint32_t ip, uint16_t port)
{
    memset(sock_addr, 0, sizeof(struct sockaddr_in));
    sock_addr->sin_family = AF_INET;
    sock_addr->sin_addr.s_addr = ip;
    sock_addr->sin_port = port;

}

int socket_init(struct sockaddr_in *sock_addr, int type)
{
    int ret, sockfd;
    DWORD  reuse_addr = 1;

    
    sockfd = socket(AF_INET, type, 0);

    if (sockfd<0)
    {
        ErrSysLog("create udp socket failed");
        return -1;
    }

    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr));

    ret=bind(sockfd, (struct sockaddr *)sock_addr, sizeof(struct sockaddr_in));
    if (ret<0)
    {
        ErrSysLog("bind udp socket to %s:%d failed", get_ipstr(sock_addr, NULL), (int)get_port(sock_addr, NULL));
        return -1;
    }

    return sockfd;

}

int udp_socket_init(const char *ipstr, uint16_t port)
{
    uint32_t ip = htonl(INADDR_ANY);
    struct sockaddr_in sock_addr;
    
    if (ipstr != NULL) ip = inet_addr(ipstr);
    make_sockaddr(&sock_addr, ip, htons(port));

    return socket_init(&sock_addr, SOCK_DGRAM);

}


int udp_socket_recvfrom(int sockfd, void *buf, int buf_size, struct sockaddr_in *peer_addr)
{
    int addr_len = sizeof(struct sockaddr_in);
    int ret=recvfrom(sockfd, buf, buf_size
                     , 0
                     , (struct sockaddr *)peer_addr, peer_addr!=NULL?&addr_len:NULL);
    if (ret<0)
    {
        if (EINTR==errno) return 0;
        
        ErrSysLog("udp socket rcv failed");
        return -1;
    }

    return ret;
}

int udp_socket_sendto(int sockfd, void *buf, int buf_size, struct sockaddr_in *peer_addr)
{
    int addr_len = sizeof(struct sockaddr_in);
    int ret=sendto(sockfd, buf, buf_size
                     , 0
                     , (struct sockaddr *)peer_addr, addr_len);
    if (ret<0)
    {
        if (EINTR==errno) return 0;
        
        ErrSysLog("udp socket snd failed");
        return -1;
    }

    return ret;
}

int tcp_socket_init(const char *ipstr, uint16_t port)
{
    uint32_t ip = htonl(INADDR_ANY);
    struct sockaddr_in sock_addr;
    
    if (ipstr != NULL) ip = inet_addr(ipstr);
    make_sockaddr(&sock_addr, ip, htons(port));

    return socket_init(&sock_addr, SOCK_STREAM);
}

int fd_readable(int fd, int usec)
{
    fd_set rfds;
    struct timeval tv;
    int retval;

    /* Watch stdin (fd 0) to see when it has input. */
    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);

    /* Wait up to usec us. */
    tv.tv_sec = 0;
    tv.tv_usec = usec;

    retval = select(fd + 1, &rfds, NULL, NULL, &tv);
    /* Don't rely on the value of tv now! */

    if (retval != 1)
    {
       return 0;
    }
    
    return 1;

}

int win_socket_init()
{
    WSADATA wsaData = {0};
    return WSAStartup(MAKEWORD(2, 2), &wsaData);
}

