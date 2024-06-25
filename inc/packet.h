#ifndef PACKET_H
#define PACKET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LOCATION_LENGTH 10
#define MESSAGE_LENGTH 51

enum world_attitude { north, south, east, west };

/*!
    \brief Structure containing information to send to remote server
*/
struct packet {

    float longitude; /* West or East */
    enum world_attitude long_att;

    float latitude; /* North or South */
    enum world_attitude lat_att;

    int engine_rpm;
    int velocity;
    int engine_load;
};

/*!
    \brief Type conversion. Digits are converted to char. 
    Conversion is NOT based on ASCII table.
*/
char digit_to_char ( int digit );

/*!
    \brief Float conversion to char array.

    Float values are converted to string of digits with dot.
*/
void float_to_array ( float number, int integer_part,
                                    int precison, char *digit_array );

/*!
    \brief Preparation of string message with information stored in structure pointed
    by struct packet *data_packet.

    MESSAGE FORMAT:

    Fields in message string are separated by ':'.

    FIELD  NUMBER   |   DESCRIPTION
    1.              |   # - begin of message string
    2.              |   N/S - attitude of latitude
    3.              |   latitude - value
    4.              |   W/E - attitude of longitude
    5.              |   longitude - value
    6.              |   engine RPM
    7.              |   vehicle speed
    8.              |   engine load
    9.              |   ? - end of message string

*/
void prepare_message ( struct packet *data_packet, char *message_string);

#endif