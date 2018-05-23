//
// Created by Joel Mai on 20.05.2018.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main() {

    //Wir machen einen Socket:
    int bs_socket; // ADRESSE ODER PROTOKOLLFAMILE / SOCKET TYP / PROTOKOLL (TCP)
    bs_socket = socket(AF_INET, SOCK_STREAM, 0);

    //Genauere Adresse fuer den Socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;           //Adress-Familie
    server_address.sin_port = htons(5678);         //Portnummer
    server_address.sin_addr.s_addr = INADDR_ANY;   //Vlt noch ändern in IP Adresse

    //     Typ              Cast zur Adresse              Länge der Adresse
    int conect_status = connect(bs_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    //Auffangen von Connection error
    if(conect_status == -1){
        printf("Verbindung fehlgeschlagen...\n\n");
    }
    else
    {
        while(1)//While Schleife von Gruppe 59 übernommen 
        {
            char client_command[50] = {0};
            scanf ("%[^\n]%*c", &client_command);
            int i = 0;
            while(client_command[i])
            {
                client_command[i] = toupper(client_command[i]);
                i++;
            }
            printf("Die Eingabe ist: %s \n", client_command);
            send(network_socket,client_command,sizeof(client_command),0);
            char server_response[256];
            recv(bs_socket,&server_response,sizeof(server_response),0);
            printf("Server: %s\n",server_response);
        }
    //Empfangen von Daten
    char server_antwort[256];
    recv(bs_socket, &server_antwort, sizeof(server_antwort), 0);

    //Ausgabe
    printf("Dateien empfangen: %s\n", server_antwort);

    //Verbindung schließen
    close(bs_socket);
    return 0;
}
