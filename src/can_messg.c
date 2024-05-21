#include "can_messg.h"

void generate_engine_speed_request_data ( struct can_frame *frame_data ){

    frame_data->can_id = CAN_BROADCAST_ID;

    frame_data->data[0] = 0x02; /* Size of packet */
    frame_data->data[1] = 0x01; /* Service type */
    frame_data->data[2] = 0x0c; /* PID 0x0c - get engine speed request data */

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

void print_can_frame ( struct can_frame *frame){

    printf("%x\n", frame->can_id);
    printf("\n");

    for ( int i = 0; i < CAN_MAX_DLEN; ++i ){
        printf("%x\n", frame->data[i]);
    }
}