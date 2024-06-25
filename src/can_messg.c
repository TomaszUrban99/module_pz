#include "can_messg.h"


int set_id ( struct can_frame *frame, char *can_id ){
    return 0;
}

/* CAN connection establishment */
int establish_can_connection ( char *can_interface, int *can_socket_descriptor, struct can_data *conn_par){

    /*!
        PF_CAN - can protocol family
        SOCK_RAW - choose CAN protocol
    */
    *can_socket_descriptor = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    /* Check if socket has been correctly assigned */
    if ( *can_socket_descriptor == -1 ){
        fprintf(stderr, "socket() failed\n");
        return -1;
    }

    printf("%s%s\n", "Interface: ", can_interface);
    
    /* Set can interface name */
    strcpy(conn_par->ifr.ifr_name, can_interface);

    /*
        System call for manipulating underlying device
        parameters of special files.
    */
    ioctl(*can_socket_descriptor, SIOCGIFINDEX, &conn_par->ifr);

    conn_par->address.can_family = AF_CAN;
    conn_par->address.can_ifindex = conn_par->ifr.ifr_ifindex;

    /* CAN FILTER */
    conn_par->receive_filter.can_id = CAN_CLIENT;
    conn_par->receive_filter.can_mask = (CAN_EFF_FLAG | CAN_RTR_FLAG | CAN_SFF_MASK);

    setsockopt(*can_socket_descriptor, SOL_CAN_RAW, 
        CAN_RAW_FILTER, &conn_par->receive_filter, sizeof(conn_par->receive_filter));

    /* Bind a socket to CAN interface */
    bind(*can_socket_descriptor, (struct sockaddr *) &conn_par->address, sizeof(conn_par->address));

    return *can_socket_descriptor;
}

void generate_engine_speed_request_data ( struct can_frame *frame_data ){

    /* Address */
    frame_data->can_id = 0x7df;

    frame_data->can_dlc = CAN_MAX_DLEN; 

    frame_data->data[0] = 0x02; /* Size of packet */
    frame_data->data[1] = 0x01; /* Service type */
    frame_data->data[2] = ENGINE_SPEED_REQUEST; /* PID 0x0c - get engine speed request data */

    /* Fill frame_data->data with data */
    for ( int i = 3; i < CAN_MAX_DLEN; ++i ){
        frame_data->data[i] = 0xaa;
    }
}

int send_engine_speed_request ( struct can_frame *frame, int socket_descriptor ){

    /* Fill data field with relevant */
    generate_engine_speed_request_data(frame);

    /* Write can_frame to the given socket descriptor */
    int nbytes = write(socket_descriptor, frame, sizeof(struct can_frame));

    if ( nbytes < 0 ){
        perror("Failed to send CAN frame");
        return 1;
    }

    if ( nbytes < sizeof(struct can_frame) ){
        fprintf(stderr, "write: incomplete CAN frame");
        return 1;
    }

    /* If everything is correct return 0 */
    return 0;
}

/*!
    \brief receive_engine_speed - read response from ECU on speed engine speed request
*/
int receive_engine_speed ( struct can_frame *frame, int socket_descriptor ){

    printf("%s\n","mmmm");

    int nbytes = read(socket_descriptor, frame, sizeof(struct can_frame));

    if ( nbytes < 0 ){
        perror("Failed to send CAN frame");
        return 1;
    }

    if ( nbytes < sizeof(struct can_frame)){
        fprintf(stderr, "read: incomplete CAN frame");
        return 1;
    }
}

/*!
    \brief interpret ecu response on engine speed
*/
int interpet_ecu_answer_engine_speed ( struct can_frame *frame ){

    int response_size = frame->data[0];

    /* Check if ECU response is positive */
    if ( frame->data[1] == PID_01_POSITIVE ){

        /* Check if response has engine speed code */
        if ( frame->data[2] == ENGINE_SPEED_REQUEST ){
            
            /* Return engine speed, result is cast to int value */
            return (int) ((256 * frame->data[3] + frame->data[4]) / 4 );
        }
    }
    /* If ECU response is not positive return negative value */
    else{
        fprintf(stderr, "ecu_answer: negative response");
        return -1;
    }

}


void generate_velocity_request_data ( struct can_frame *frame ){

    /* Address */
    frame->can_id = 0x7df;
    frame->can_dlc = CAN_MAX_DLEN; 
    
    frame->data[0] = 0x02; /* Size of packet */
    frame->data[1] = 0x01; /* Service type */
    frame->data[2] = VELOCITY_REQUEST;
    
    /* Fill frame_data->data with data */
    for ( int i = 3; i < CAN_MAX_DLEN; ++i ){
        frame->data[i] = 0xaa;
    }
}

int send_velocity_request ( struct can_frame *frame, int socket_descriptor ){

    /* Fill data field with relevant */
    generate_velocity_request_data(frame);

    /* Write can_frame to the given socket descriptor */
    int nbytes = write(socket_descriptor, frame, sizeof(struct can_frame));

    if ( nbytes < 0 ){
        perror("Failed to send CAN frame");
        return 1;
    }

    if ( nbytes < sizeof(struct can_frame) ){
        fprintf(stderr, "write: incomplete CAN frame");
        return 1;
    }

    /* If everything is correct return 0 */
    return 0;
}

int receive_velocity ( struct can_frame *frame, int socket_descriptor ){

    int nbytes = read(socket_descriptor, frame, sizeof(struct can_frame));

    if ( nbytes < 0 ){
        perror("Failed to send CAN frame");
        return 1;
    }

    if ( nbytes < sizeof(struct can_frame)){
        fprintf(stderr, "read: incomplete CAN frame");
        return 1;
    }

    return 0;
}

int interpet_ecu_answer_velocity ( struct can_frame *frame ){

    int response_size = frame->data[0];

    /* Check if ECU response is positive */
    if ( frame->data[1] == PID_01_POSITIVE ){

        /* Check if response has engine speed code */
        if ( frame->data[2] == VELOCITY_REQUEST ){
            
            /* Return engine speed, result is cast to int value */
            return (int) ( frame->data[3] );
        }
    }
    /* If ECU response is not positive return negative value */
    else{
        fprintf(stderr, "ecu_answer: negative response");
        return -1;
    }

}



void generate_load_request ( struct can_frame *frame_data ){

    /* Address */
    frame_data->can_id = 0x7df;
    frame_data->can_dlc = CAN_MAX_DLEN; 
    
    frame_data->data[0] = 0x02; /* Size of packet */
    frame_data->data[1] = 0x01; /* Service type */
    frame_data->data[2] = CALCULATED_ENGINE_LOAD;
    
    /* Fill frame_data->data with data */
    for ( int i = 3; i < CAN_MAX_DLEN; ++i ){
        frame_data->data[i] = 0xaa;
    }
}

int send_load_request ( struct can_frame *frame, int socket_descriptor ){

    /* Fill data field with relevant */
    generate_load_request(frame);

    /* Write can_frame to the given socket descriptor */
    int nbytes = write(socket_descriptor, frame, sizeof(struct can_frame));

    if ( nbytes < 0 ){
        perror("Failed to send CAN frame");
        return 1;
    }

    if ( nbytes < sizeof(struct can_frame) ){
        fprintf(stderr, "write: incomplete CAN frame");
        return 1;
    }

    /* If everything is correct return 0 */
    return 0;
}

int receive_load ( struct can_frame *frame, int socket_descriptor ){

    int nbytes = read(socket_descriptor, frame, sizeof(struct can_frame));

    if ( nbytes < 0 ){
        perror("Failed to send CAN frame");
        return 1;
    }

    if ( nbytes < sizeof(struct can_frame)){
        fprintf(stderr, "read: incomplete CAN frame");
        return 1;
    }

    return 0;
}

int interpet_ecu_answer_load ( struct can_frame *frame ){

    int response_size = frame->data[0];

    /* Check if ECU response is positive */
    if ( frame->data[1] == PID_01_POSITIVE ){

        /* Check if response has engine speed code */
        if ( frame->data[2] == CALCULATED_ENGINE_LOAD ){
            
            /* Return engine speed, result is cast to int value */
            return (int) ( (100/255) * frame->data[3] );
        }
    }
    /* If ECU response is not positive return negative value */
    else{
        fprintf(stderr, "ecu_answer: negative response");
        return -1;
    }

}




void print_can_frame ( struct can_frame *frame){

    printf("%x\n", frame->can_id);
    printf("\n");

    for ( int i = 0; i < CAN_MAX_DLEN; ++i ){
        printf("%d%s", i, " ");
        printf("%x\n", frame->data[i]);
    }
}