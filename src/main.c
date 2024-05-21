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
#include <linux/can.h>
#include <linux/can/raw.h>

#include "can_messg.h"

int main(int argc, char** argv){


    /* Socket descriptor */
    int socket_desc;

    struct  sockaddr_can address;
    struct ifreq ifr;

    /*!
        PF_CAN - can protocol family
        SOCK_RAW - choose CAN protocol
    */
    socket_desc = socket(PF_CAN, SOCK_RAW, CAN_RAW);    

    /* Check if socket has been correctly assigned */
    if ( socket_desc == -1 ){
        fprintf(stderr, "socket() failed\n");
        return 1;
    }

    strcpy(ifr.ifr_name, CAN_INTERFACE);
    /*
        System call for manipulating underlying device
        parameters of special files.
    */
    ioctl(socket_desc, SIOCGIFINDEX, &ifr);

    /* */
    address.can_family = AF_CAN;
    address.can_ifindex = ifr.ifr_ifindex;

    /* Set filters on incoming messages */
    struct can_filter receive_filter;

    receive_filter.can_id = CAN_CLIENT;
    receive_filter.can_mask = (CAN_EFF_FLAG | CAN_RTR_FLAG | CAN_SFF_MASK);

    setsockopt(socket_desc, SOL_CAN_RAW, 
        CAN_RAW_FILTER, &receive_filter, sizeof(receive_filter));

    /* Bind a socket to CAN interface */
    bind(socket_desc, (struct sockaddr *) &address, sizeof(address));

    struct can_frame frame;

    receive_engine_speed(&frame, socket_desc);

    printf("%s%d\n", "Obroty: ", interpet_ecu_answer_engine_speed(&frame));

    print_can_frame(&frame);

    return 0;
}
