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

/* ECU answers codes */

#define PID_01_POSITIVE 0x41 /* 0x01 + 0x40 */

/* PID 01 request data code */

#define ENGINE_SPEED_REQUEST 0x0c
#define VELOCITY_REQUEST 0x0d
#define CALCULATED_ENGINE_LOAD 0x04

/* ---------- DATA STRUCTURE ------------------------------ */

struct can_data {

    struct  sockaddr_can address;
    struct ifreq ifr;
    struct can_filter receive_filter;
};

int set_id ( struct can_frame *frame, char *can_id );

/* -------------- CONNECTION ESTABLISHMENT --------------- */

/*!
    \brief establish_can_connection - establish connection to CAN bus
*/
int establish_can_connection ( char *can_interface, int *can_socket_descriptor, struct can_data *conn_par );

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
int interpet_ecu_answer_engine_speed ( struct can_frame *frame );


void generate_velocity_request_data ( struct can_frame *frame );

int send_velocity_request ( struct can_frame *frame, int socket_descriptor );

int receive_velocity ( struct can_frame *frame, int socket_descriptor );

int interpet_ecu_answer_velocity ( struct can_frame *frame );

void generate_load_request ( struct can_frame *frame_data );

int send_load_request ( struct can_frame *frame, int socket_descriptor );

int receive_load ( struct can_frame *frame, int socekt_descriptor );

int interpet_ecu_answer_load ( struct can_frame *frame );

/*!
    \brief
*/
void print_can_frame ( struct can_frame *frame );

#endif