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

#include <time.h>

#include "can_messg.h"
#include "packet.h"
#include "tcp_messg.h"

int main(int argc, char** argv){


    /* Socket descriptor */
    /*int socket_desc;

    struct  sockaddr_can address;
    struct ifreq ifr;

    /*!
        PF_CAN - can protocol family
        SOCK_RAW - choose CAN protocol
    */
    /*socket_desc = socket(PF_CAN, SOCK_RAW, CAN_RAW);   */

    /* Check if socket has been correctly assigned */
    /*if ( socket_desc == -1 ){
        fprintf(stderr, "socket() failed\n");
        return 1;
    }

    strcpy(ifr.ifr_name, CAN_INTERFACE);*/
    /*
        System call for manipulating underlying device
        parameters of special files.
    */
    /*ioctl(socket_desc, SIOCGIFINDEX, &ifr);

    address.can_family = AF_CAN;
    address.can_ifindex = ifr.ifr_ifindex;*/

    /* Set filters on incoming messages */
    /*struct can_filter receive_filter;

    receive_filter.can_id = CAN_CLIENT;
    receive_filter.can_mask = (CAN_EFF_FLAG | CAN_RTR_FLAG | CAN_SFF_MASK);

    setsockopt(socket_desc, SOL_CAN_RAW, 
        CAN_RAW_FILTER, &receive_filter, sizeof(receive_filter));*/

    /* Bind a socket to CAN interface */
    /*bind(socket_desc, (struct sockaddr *) &address, sizeof(address));

    struct can_frame frame;
    struct can_frame receive_frame; */

    /*
    while (1){

        generate_engine_speed_request_data(&frame);
        send_engine_speed_request(&frame, socket_desc);
        receive_engine_speed(&receive_frame, socket_desc);

        interpet_ecu_answer_engine_speed(&receive_frame);
        print_can_frame(&receive_frame);
        sleep(5);
    }
    */

    struct packet data_packet;

    data_packet.lat_att = north;
    data_packet.latitude = 8.000;
   

    char message_string[MESSAGE_LENGTH];

    int socket_desc;

    prepare_message(&data_packet,message_string);
    establish_connection(argv,&socket_desc);
    printf("%d\n", send_to_server(socket_desc,message_string));

    return 0;
}
