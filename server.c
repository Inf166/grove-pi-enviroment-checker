#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main(){

    chat server_message[256] = "Du hast den Server erreicht";

    //Erstelle Server Socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    //Definiere Server Adress-Familie
    struct sockaddr_in server_ad;
    serv_ad.sin_family = AF_INET;           //Adress-Familie
    serv_ad.sin_port = htons(5678);         //Portnummer
    serv_ad.sin_addr.s_addr = INADDR_ANY;   //Vlt noch ändern in IP Adresse

    //bind den socket zu unser IP und port
    bind(network_socket, (struct sockaddr *) &serv_ad, sizeof(serv_ad));

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