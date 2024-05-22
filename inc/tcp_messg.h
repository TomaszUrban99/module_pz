#ifndef TCP_MESSG_H
#define TCP_MESSG_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define CONNECTED 0
#define SOCKET_ERROR -1
#define GETADDRINFO_ERROR -2
#define CONNECT_ERROR -3

/* Module with functions enable sending data packets to remote server */

/*!
    \brief Establish TCP connection
*/
int establish_connection ( char **argv, int tcp_socket_descriptor );

/*!
    \brief Send packet to remote server

    \par tcp_socket_descriptor - socket id to send packet
    \par packet_to_send - packet to send via tcp socket

    \retval number_of_bytes - number of send bytes
    \retval -1 - failed to send
*/
int send_to_server ( int tcp_socket_descriptor );

#endif