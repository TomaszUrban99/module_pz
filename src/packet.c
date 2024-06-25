#include "packet.h"

char digit_to_char ( int digit ){
    
    switch (digit)
    {
    case 0:
        return '0';
    case 1:
        return '1';
    case 2:
        return '2';
    case 3:
        return '3';
    case 4:
        return '4';
    case 5:
        return '5';
    case 6:
        return '6';
    case 7:
        return '7';
    case 8:
        return '8';
    case 9:
        return '9';
    }

    return '0';
}

void float_to_array ( float number, int integer_part,
                                    int precison, char *digit_array ){

    int digital = 0;

    /* ------------------- INTEGER PART ------------------------*/

    for ( int i = 0; i < integer_part; ++i ){

        digital = number / ( pow( 10, integer_part - 1 - i));
        number = number - digital * pow( 10, integer_part - 1 - i);

        /* Save digit in array */        
        digit_array[i] = digit_to_char( (int) digital);
    }

    /* ------------------- DECIMAL PART ----------------------- */

    if ( precison > 0){
        
        digit_array[integer_part] = '.';

        number = number * pow(10,precison);
    
        for ( int i = 0; i < precison; ++i ){
            
            digital = number / ( pow(10, precison -1 - i));
            number = number - digital * pow ( 10, precison -1 -i );

            /* Save digit in array */
            digit_array[integer_part + 1 + i] = digit_to_char(digital);
        }

    }

    /* End of string character */
    digit_array[integer_part+precison] = '\0';
}

void prepare_message ( struct packet *data_packet, char *message_string ){

    char latitude[LOCATION_LENGTH];
    char longitude[LOCATION_LENGTH];

    /* Transform latitude & longitude float values to char array */
    float_to_array(data_packet->latitude,2,6,latitude);
    float_to_array(data_packet->longitude,3,6,longitude);

    message_string[0] = '#'; /* Message begins */
    message_string[1] = ':'; /* First separator */

    /* string 1 - latitude */

    if ( data_packet->lat_att == north ){
        message_string[2] = 'N';
    }
    else{
        message_string[2] = 'S';
    }

    message_string[3] = ':';
    message_string[4] = '\0';

    strcat(message_string,latitude);

    /* ------------- LONGITUDE -------------------- */

    int message_size = strlen(message_string);
    
    message_string[message_size] = ':';
    message_size++;

    if ( data_packet->long_att == east ){
        message_string[message_size] = 'E'; 
    }
    else{
        message_string[message_size] = 'W';
    }

    message_size++;
    message_string[message_size] = ':';
    message_string[message_size+1] = '\0';

    strcat(message_string,longitude);

    message_size = strlen(message_string);
    message_string[message_size] = ':';
    message_string[message_size+1] = '\0';

    char values[8];

    float_to_array(data_packet->engine_rpm,4,0,values);

    strcat(message_string,values);

    message_size = strlen(message_string);
    message_string[message_size] = ':';
    message_string[message_size+1] = '\0';

    char velocity[4];

    float_to_array(data_packet->velocity,3,0,velocity);

    strcat(message_string,velocity);
    
    message_size = strlen(message_string);
    message_string[message_size] = ':';
    message_string[message_size+1] = '\0';

    char engine_load[4];

    float_to_array(data_packet->velocity,3,0,engine_load);
    
    strcat(message_string,engine_load);
    
    message_size = strlen(message_string);
    message_string[message_size] = ':';
    message_size++;

    message_string[message_size] = '?';
    message_string[message_size+1] = '\0';
    
    printf("%s\n", message_string);

}