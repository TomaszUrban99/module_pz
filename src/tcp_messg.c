#include "tcp_messg.h"

int establish_connection ( char **argv, int *tcp_socket_descriptor ){

    printf("Configuring remote address....\n");

    struct addrinfo remote_address;
    memset(&remote_address, 0, sizeof(remote_address));
    remote_address.ai_socktype = SOCK_STREAM; /* Stream socket */

    struct addrinfo *peer_address;

    if ( getaddrinfo ( argv[1], argv[2], &remote_address, &peer_address) ){
        fprintf(stderr, "getaddrinfo() failed");
        return GETADDRINFO_ERROR;
    }

    printf("Trying to connect...\n");
    
    printf("Creating socket...\n");
    
    /* Create new socket */
    *tcp_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

    /* Check if socket has been created */
    if ( *tcp_socket_descriptor < 0 ){
        fprintf(stderr,"%s\n","SOCKET: failed to create");
        return SOCKET_ERROR;
    }

    printf("Connecting...\n");

    /* Connecting */
    if ( connect(*tcp_socket_descriptor, peer_address->ai_addr, peer_address->ai_addrlen) ){
        fprintf(stderr, "connect() failed");
        return CONNECT_ERROR;
    }

    printf("Connected!\n");
    freeaddrinfo(peer_address);

    return CONNECTED;
}

int send_to_server ( int tcp_socket_descriptor, char *packet_to_send ){

    int size_of_message = strlen(packet_to_send);

    int bytes = send(tcp_socket_descriptor, packet_to_send, size_of_message, 0);

    return bytes;
}