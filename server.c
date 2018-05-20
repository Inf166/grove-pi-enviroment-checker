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

    char temperaturinchar[sizeof(temp)];
    strcat(temperaturinchar, (char *) &temp);
    char tempuebergang[25] = "[temp = ";
    strcat(tempuebergang, temperaturinchar);
    strcat(tempuebergang, "]\n");

    strcat(server_message, tempuebergang);

        printf("Humidity erkannt\n");



        pinMode(port, INPUT); //Modus festlegen (pinMode([PortNr.],[0(INPUT)/1(OUTPUT)])

        pi_sleep(1000); //wait 1s

        // do indefinitely
        //get only Humidity
        getHumidity(&humidity, port);

    char humidityalschar[sizeof(humidity)];
    strcat(humidityalschar, (char *) &humidity);
    char humidityuebergnag[25] = "[humidity = ";
    strcat(humidityuebergnag, humidityalschar);
    strcat(humidityuebergnag, "]\n");

    strcat(server_message, humidityuebergnag);

        printf("Light erkannt\n");
        int portlight = 4; //connect the light sensor to this port
        int led = 2; //connect a LED to this port
        int value;
        float resistance;
        //threshhold to pass
        int threshhold = 10;



        pinMode(portlight,INPUT);
        pinMode(led, OUTPUT);
        //read from the analog Port
        value = analogRead(portlight);
        //calculate the resistance of the light sensor
        resistance = (float)(1023 - value) * 10 / value;
        //if the resitance passes threshhold, turn on the LED
        if(resistance > threshhold)
            digitalWrite(led, 1);
        else
            digitalWrite(led, 0);

    char resitancealschar[sizeof(resistance)];
    strcat(resitancealschar, (char *) &resistance);
    char valuealschar[sizeof(value)];
    strcat(valuealschar, (char *) &value);
    char valresuebergang[25] = "[Value: ";
    strcat(valresuebergang, valuealschar);
    strcat(valresuebergang, " Resistance: ");
    strcat(valresuebergang, resitancealschar);
    strcat(valresuebergang, "]\n");

    strcat(server_message, valresuebergang);

        pi_sleep(100); //wait 0,1s

        printf("Sound erkannt\n");
        int portsound = 3; //Audio-Sensor an analogen Port A0 anschließen
        int sound = 0; //Lautstärke


        pinMode(portsound, INPUT); //Modus festlegen (pinMode([PinNr.],[0(INPUT)/1(OUTPUT)])

        pi_sleep(1000); //warte 1s

        // do indefinitely
        sound = analogRead(portsound); //Frage Port A0 ab und speichere Wert in Variable

    char soundalschar[sizeof(sound)];
    strcat(soundalschar, (char *) &sound);
    char sounduebergang[25] = "[sound in db = ";
    strcat(sounduebergang, soundalschar);
    strcat(sounduebergang, "]\n");

    strcat(server_message, sounduebergang);
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