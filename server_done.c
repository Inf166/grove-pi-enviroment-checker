//
// Created by Joel Mai on 23.05.2018.
//
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <errno.h>

#include "grovepi.h"
#include <string.h>

#define INPUT 0
#define OUTPUT 1

// Raspberry-Funktionen anlegegen
float getTemp(int port);

int getSound(int port);

float getLuftfeuchtigkeit(int port);

int getLicht(int port);


int main(){
  
	init(); //Raspberry init.
  
    char server_message[256] = "Du hast den Server erreicht.\n";           //Server Nachricht an Client - hier vorgeschrieben
    //Erstelle Server Socket
        int server_socket;
        server_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (server_socket == -1) { //Stackoverflow übernommen
            printf("Error: unable to open a socket\n");
            exit(1);
        }

    //Definiere Server Adress-Familie
        struct sockaddr_in server_address;
        server_address.sin_family = AF_INET;           //Adress-Familie
        server_address.sin_port = htons(5678);         //Portnummer
        server_address.sin_addr.s_addr = INADDR_ANY;   //Vlt noch ändern in IP Adresse
        socklen_t len = sizeof(server_address);        //Länge der Adresse

    //bind den socket zu unser IP und port
    //    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
        if ((bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address))) == -1) { // Stackoverflow übernommen
            printf("Error: unable to bind\n");
            printf("Error code: %d\n", errno);
            exit(1);
        } else{
            bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
        }

    //listen to conections
        listen(server_socket, 5);
        if ((listen(server_socket, 5)) == -1) { // Stackoverflow übernommen
            printf("Error: unable to listen for connections\n");
            printf("Error code: %d\n", errno);
            exit(1);
        }else{
            listen(server_socket, 5); //lausche nach Clients
        }

    //Lege Client Socket an
        int client_socket;

    //accept Funktion      Server Socket    IP des Clients      Size of IP
        client_socket = accept(server_socket, NULL, NULL); // Stackoverflow übernommen
        if (client_socket == -1) {
            printf("Error: unable to accept connections\n");
            printf("Error code: %d\n", errno);
            exit(1);
        }

    //Send Funktion     Clientsocket, definierte Nachricht und Size of der Nachricht
        send(client_socket, server_message, sizeof(server_message), 0);

    int pid, neue;
    static int counter=0;
    while (1) {
        neue = accept(server_socket, (struct sockaddr *) &clientaddr, (socklen_t) &len);
        if ((pid = fork()) == -1) // Fehler
        {
            close(neue);
            continue;
        }
        else if (pid > 0) //Parent
        {
            close(neue);
            counter++;
            printf("here2/n");
            continue;
        }
        else if (pid == 0) //Son
        {
            char buf[100];
            counter++;
            printf("here 1/n");
            snprintf(buf, sizeof buf, "hi %d", counter);
            send (neue, buf, strlen(buf), 0);
          	boolean running=true;
            while(running) {//Code von Gruppe 59 übernommen
                char client_cmd[256];
                recv(client_socket, &client_cmd, sizeof(client_cmd), 0);
                printf("Client: %s\n", client_cmd);
                // einfacher: direkt den kompletten String vergleichen, ggfs. mit \n
                // strcmp(client_cmd, "GET TEMPERATURE\n") == 0 ....
                if ((strcmp(client_cmd, "GET TEMPERATURE") == 0)||(strcmp(client_cmd, "GET TEMPERATURE\n") == 0)) {
                    float f = getTemperatureerature(8);
                    printf("[temp = %2.02f C]\n", f); fflush();
                    fprintf(client_socket, "[temp = %2.02f C]\n", f);
                } else if ((strcmp(client_cmd, "GET HUMIDITY") == 0)||(strcmp(client_cmd, "GET HUMIDITY\n") == 0)) {
                    float f = getHumidty(8);
                    printf("[humidity = %.02f%%]\n", f);
                    fprintf(client_socket, "[humidity = %.02f%%]", f);
                } else if ((strcmp(client_cmd, "GET LIGHT") == 0)|| (strcmp(client_cmd, "GET LIGHT\n") == 0)) {
                    int f = getLicht(4);
                    printf("Light value: %d  Resistance: %0.2f \n", f);
                    fprintf(client_socket, "Light value: %d  Resistance: %0.2f \n", f);
                } else if ((strcmp(client_cmd, "GET SOUND") == 0)||(strcmp(client_cmd, "GET SOUND\n") == 0)) {
                    int f = getsound(3);
                    printf("SOUND: %d\n", f);
                    fprintf(client_socket, "SOUND: %d\n", f);
                } else if ((strcmp(client_cmd, "END") == 0)||(strcmp(client_cmd, "END\n") == 0)) {
                    running=false;
                } else {
                  
                    fprintf(client_socket,"Fehlerhafte Eingabe");
                }

            }
            close(neue);
            break;
        }
    }
    //close Funktion
    close(server_socket);
    return 0;
}

// Raspberry-Fubktionen definieren - Übernommen von Team 59
float getTemp(int port)
{
	float temp = 0;
    pinMode(port, INPUT);
    pi_sleep(1000);
	getTemperature(&temp, port);
    return temp;
}

float getLuftfeuchtigkeit(int port)
{
	float humidity = 0;
    getHumidity(&humidity, port);
	pi_sleep(1000); //wait 1s
	return humidity;

}

int getLicht(int port)
{
    int value;
    float resistance;
    value = analogRead(port);
    resistance = (float)(1023 - value) * 10 / value;
	return value;
}

int getSound(int port)
{
	int sound = 0;
	pinMode(port, INPUT);
	pi_sleep(1000);
	int i = 0;
	int summe = 0;
	while(i<5)
	{
        sound = analogRead(port);
        pi_sleep(100);
        summe = summe + sound;
        i++;
	}
	return summe / i;
}

