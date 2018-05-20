#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include "grovepi.h"
#include <string.h>

#define INPUT 0
#define OUTPUT 1
int main(){
    char server_message[256] = "Du hast den Server erreicht";
    strcat(server_message, "\n");
        printf("Temperatur erkannt\n");
        int port = 8; //Sensor an digital Port D8 anschließen
        float temp = 0, humidity = 0;


        init(); //Initialisierung des GrovePi's
        pinMode(port, INPUT); //Modus festlegen (pinMode([PortNr.],[0(INPUT)/1(OUTPUT)])

        pi_sleep(1000); //wait 1s

        // do indefinitely
        getTemperature(&temp, port);

    char nurso[sizeof(temp)];
    nurso = (char) temp;
    char test[25] = "[temp = ";
    strcat(test, nurso);
    strcat(test, "]\n");

    strcat(server_message, test);

        printf("Humidity erkannt\n");
        int port = 8; //Sensor an digital Port D8 anschließen
        float temp = 0, humidity = 0;


        init(); //Initialisierung des GrovePi's
        pinMode(port, INPUT); //Modus festlegen (pinMode([PortNr.],[0(INPUT)/1(OUTPUT)])

        pi_sleep(1000); //wait 1s

        // do indefinitely
        //get only Humidity
        getHumidity(&humidity, port);
    char test[25] = ("[humidity = %.02f%%]\n", humidity);
    strcat(server_message, test);

        printf("Light erkannt\n");
        int port = 4; //connect the light sensor to this port
        int led = 2; //connect a LED to this port
        int value;
        float resistance;
        //threshhold to pass
        int threshhold = 10;

        //Exit on failure to start communications with the GrovePi
        if(init()==-1)
            exit(1);

        pinMode(port,INPUT);
        pinMode(led, OUTPUT);
        //read from the analog Port
        value = analogRead(port);
        //calculate the resistance of the light sensor
        resistance = (float)(1023 - value) * 10 / value;
        //if the resitance passes threshhold, turn on the LED
        if(resistance > threshhold)
            digitalWrite(led, 1);
        else
            digitalWrite(led, 0);

    strcat(server_message, "Value: %d  Resistance: %0.2f \n", value, resistance);

        pi_sleep(100); //wait 0,1s

        printf("Sound erkannt\n");
        int port = 3; //Audio-Sensor an analogen Port A0 anschließen
        int sound = 0; //Lautstärke

        init(); //Initialisierung des GrovePi's
        pinMode(port, INPUT); //Modus festlegen (pinMode([PinNr.],[0(INPUT)/1(OUTPUT)])

        pi_sleep(1000); //warte 1s

        // do indefinitely
        sound = analogRead(port); //Frage Port A0 ab und speichere Wert in Variable
    strcat(server_message, "SOUND: %d db\n", sound);

        pi_sleep(100); //warte 0,1s

    //Erstelle Server Socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    //Definiere Server Adress-Familie
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;           //Adress-Familie
    server_address.sin_port = htons(5678);         //Portnummer
    server_address.sin_addr.s_addr = INADDR_ANY;   //Vlt noch ändern in IP Adresse

    //bind den socket zu unser IP und port
    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    //listen to conections
    listen(server_socket, 5);

    int client_socket;

    //accept Funktion      Server Socket    IP des Clients      Size of IP
    client_socket = accept(server_socket, NULL, NULL);
    //Send Funktion     Clientsocket, definierte Nachricht und Size of der Nachricht
    send(client_socket, server_message, sizeof(server_message), 0);
    //close Funktion
    close(server_socket);
    return 0;
}