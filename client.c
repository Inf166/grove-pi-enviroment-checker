#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main() {

    //Wir machen einen Socket:
    int bs_socket; // ADRESSE ODER PROTOKOLLFAMILE / SOCKET TYP / PROTOKOLL (TCP)
    bs_socket = socket(AF_INET, SOCK_STREAM, 0);

    //Genauere Adresse fuer den Socket
    struct sockad_in serv_ad;
    serv_ad.sin_family = AF_INET;           //Adress-Familie
    serv_ad.sin_port = htons(5678);         //Portnummer
    serv_ad.sin_addr.s_addr = INADDR_ANY;   //Vlt noch ändern in IP Adresse

    //     Typ              Cast zur Adresse              Länge der Adresse
    int conect_status = connect(network_socket, (struct sockaddr *) &serv_ad, sizeof(serv_ad));
    //Auffangen von Connection error
    if(conect_status == -1){
        printf("Verbindung fehlgeschlagen...\n\n");
    }
    //Empfangen von Daten
    char server_antwort[256];
    recv(network_socket, &server_antwort, sizeof(server_antwort), 0);

    //Ausgabe
    printf("Dateien empfangen: %s\n", server_antwort);

    //Verbindung schließen
    close(network_socket);
    return 0;
}