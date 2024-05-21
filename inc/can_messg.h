#ifndef CAN_MESSG_H
#define CAN_MESSG_H

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

/* CAN arbitration ID */

#define CAN_CLIENT 0x7e8
#define CAN_BROADCAST_ID 0x7df

/* CAN Interfaces */

#define CAN_INTERFACE "can0"

/* -------------- REQUESTS ------------------------------ */

void generate_engine_speed_request_data ( struct can_frame *frame_data );


/* ------------- SEND ENGINE SPEED REQUEST ------------- */

int send_engine_speed_request ( struct can_frame *frame, int socket_descriptor );

/* ----------- RECEIVE ENGINE SPEED REQUEST ------------ */

/*!
    \brief receive_engine_speed - read response from ECU on speed engine speed request

    \retval 0 - answer received correctly
    \retval 1 - failed to receive answer, incomplete answer
*/
int receive_engine_speed ( struct can_frame *frame, int socket_descriptor );

/* ----- INTERPRET ANSWER FROM ECU (ENGINE SPEED) ------ */

/*!
    \brief

    \retval 0 - positive response from ECU, engine speed not read correctly
*/
int interpet_ecu_answer_engine_speed ( struct can_frame *frame, int socket_descriptor );

/*!
    \brief
*/
void print_can_frame ( struct can_frame *frame );

#endif