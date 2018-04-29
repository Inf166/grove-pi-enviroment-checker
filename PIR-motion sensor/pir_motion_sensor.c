#include "../grovepi.h"

/**
*   The motion sensor detects every motion in its range.
*   it returns "1" in case of a motion
*
**/

int main(){

    int port = 8; //connect the sensor to a digital port
    int led = 4; //connect a LED to this port
    int motion = -1;

    //Exit on failure to start communications with the GrovePi
	if(init()==-1)
		exit(1);

    pinMode(port,INPUT); // set the mode of the sensor
    pinMode(led, OUTPUT);

	while(1){
        // get the value of the sensor on a digital port
        motion = digitalRead(port);

        if(motion == 255)
            printf("PIR-Motion: IO Error!");

        if(motion == 1){ //motion detected...
            digitalWrite(led, 1); //turn the LED ON
            pi_sleep(3000);
        }
        else if(motion == 0){
            digitalWrite(led, 0); //turn the LED ON
            pi_sleep(3000);
        }

            printf("Motion-Value: %d \n", motion);

            pi_sleep(100);
	}
	return 0;

}
