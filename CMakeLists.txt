cmake_minimum_required(VERSION 3.25)

project(obd_module LANGUAGES C CXX)
set (WPI_PATH /home/tomasz/opt/WiringPi/wiringPi)# Add the local ‘include’ directory and the wiringPi directory to grab headers

include_directories (include ${WPI_PATH})# Actually find the wiringPi library object
find_library(WPI_LIB wiringPi HINTS ${WPI_PATH} NO_CMAKE_FIND_ROOT_PATH)

# Alert the user if we do not find it
#if(NOT WPI_LIB)
# message(FATAL_ERROR “wiringPi library not found”)
#endif()# Add all the *.c files in our source directory to our executable output

add_library(can_messg STATIC src/can_messg.c)
target_include_directories(can_messg PRIVATE inc/)

add_executable(obd_main src/main.c )# Link the pre-compiled wiringPi library to the executable we just declared 
target_include_directories(obd_main PRIVATE inc/)
target_link_libraries(obd_main can_messg /home/tomasz/opt/WiringPi/wiringPi/libwiringPi.so /home/tomasz/opt/pigpio-master/build/libpigpio.so)