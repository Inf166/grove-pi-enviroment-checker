//
// Created by Joel Mai on 20.05.2018.
//
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
    int pid, neue;
    static int counter=0;
    /*String Token trennt string anhand von Trennzeichen auf*/
        strtok(str, separator);


    /* Kleine Hilfsfunktion von uns für euch: Speichert die erstellten Tokens direkt in einem Array*/
        int strtoken(char *str, char *separator, char **token, int size) {
            int i=0;
            token[0] = strtok(str, separator);
            while(token[i++] && i < size)
                token[i] = strtok(NULL, separator);
            return (i);
        }
    while (1) {
        neue = accept(server_socket, (struct sockaddr *) &clientaddr, (socklen_t) &len);
        if ((pid = fork()) == -1)
        {
            close(neue);
            continue;
        }
        else if (pid > 0)
        {
            close(neue);
            counter++;
            printf("here2/n");
            continue;
        }
        else if (pid == 0)
        {
            char buf[100];
            counter++;
            printf("here 1/n");
            snprintf(buf, sizeof buf, "hi %d", counter);
            send (neue, buf, strlen(buf), 0);
            while(1) {//Code von Gruppe 59 übernommen
                char client_cmd[256];
                recv(client_socket, &client_cmd, sizeof(client_cmd), 0);
                printf("Client: %s\n", client_cmd);
                if(strcmp(client_cmd[0], "GET") == 0) {
                    if (strcmp(client_cmd, "TEMP") == 0) {
                        float f = getTemperatureerature(8);
                        printf("[temp = %2.02f C]\n", f);
                        char *value = (char *) &f;
                        send(client_socket, value, sizeof(value), 0);
                    } else if (strcmp(client_cmd[1], "HUMIDITY") == 0) {
                        float f = getHumidty(8);
                        printf("[humidity = %.02f%%]\n", f);
                        char *value = (char *) &f;
                        send(client_socket, value, sizeof(value), 0);
                    } else if (strcmp(client_cmd[1], "LIGHT") == 0) {
                        int f = getLicht(4);
                        printf("Light value: %d  Resistance: %0.2f \n", f);
                        char value = (char *) &f;
                        send(client_socket, value, sizeof(value), 0);
                    } else if (strcmp(client_cmd[1], "SOUND") == 0) {
                        int f = getsound(3);
                        printf("SOUND: %d\n", f);
                        char *value = (char *) &f;
                        send(client_socket, value, sizeof(value), 0);
                    } else {
                        send(client_socket, client_cmd, sizeof(client_cmd), 0);
                    }
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
float getTemperature(int port);

int getsound(int port);

float getHumidty(int port);

int getLicht(int port);

float getTemperature(int port)
{
    float temp = 0;
    pinMode(port, INPUT);
    pi_sleep(1000);
    getTemperatureerature(&temp, port);
    return temp;
}

float getHumidty(int port)
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

int getsound(int port)
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
