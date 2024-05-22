#ifndef PACKET_H
#define PACKET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LOCATION_LENGTH 10
#define MESSAGE_LENGTH 50

enum world_attitude { north, south, east, west };

/*!
    \brief Structure containing information to send to remote server
*/
struct packet {

    float longitude;
    enum world_attitude long_att;

    float latitude; /* North or South */
    enum world_attitude lat_att;

    int engine_rpm;
    int velocity;
    int engine_load;
};

char digit_to_char ( int digit );

void float_to_array ( float number, int integer_part,
                                    int precison, char *digit_array );

void prepare_message ( struct packet *data_packet, char *message_string);

#endif