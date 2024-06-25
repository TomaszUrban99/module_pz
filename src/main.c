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

    struct can_data conn_par;

    /* Sockets descriptor */
    
        int socket_desc_can; /* can interface - to OBD */
        int socket_desc_tcp; /* tcp interface - to remote server */

    /*------------------------------------------------------------*/

    /* Establish CAN connection */

    if ( establish_can_connection(argv[3], &socket_desc_can, &conn_par) < 0 ){
        fprintf(stderr,"failed to connect to CAN bus");
        return -1;
    }

    /* Establish TCP connection */
    if ( establish_connection(argv,&socket_desc_tcp) < 0){
        return -1;
    };

    struct can_frame frame;
    struct can_frame receive_frame;

    struct packet data_packet;
    
    data_packet.lat_att = north;
    data_packet.latitude = 8.000;

    data_packet.long_att = west;
    data_packet.longitude = 15.000;

    while (1){


    /* ------------------------- CAN REQUESTS -------------------------------------- */
        
        /* ---------------------- ENGINE RPM --------------------------------------- */
            
            printf("%d\n",send_engine_speed_request(&frame, socket_desc_can));
        
            receive_engine_speed(&receive_frame, socket_desc_can);
            data_packet.engine_rpm = interpet_ecu_answer_engine_speed(&receive_frame);

            printf("%s%d\n", "Obroty silnika: ", data_packet.engine_rpm);

            printf("%d\n",send_velocity_request(&frame, socket_desc_can));

            receive_velocity(&receive_frame, socket_desc_can);
            data_packet.velocity = interpet_ecu_answer_velocity(&receive_frame);
            printf("%s%d\n", "Predkosc: ", data_packet.velocity);

            printf("%d\n",send_load_request(&frame, socket_desc_can));
            receive_load(&receive_frame, socket_desc_can);
            data_packet.engine_load = interpet_ecu_answer_load(&receive_frame);
            printf("%s%d\n", "Obciazenie: ", data_packet.engine_load);

        
    /* ------------------------ SEND TO SERVER ------------------------------------ */
            
        /* ---------------- PREPARE STRING MESSAGE -------------------------------- */
            
            char message_string[MESSAGE_LENGTH];
            prepare_message(&data_packet,message_string);
            printf("%d\n", send_to_server(socket_desc_tcp,message_string));

    /* --------------------------------------------------------------------------- */
        sleep(10);
    }

    return 0;
}
