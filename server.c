//
// Created by Joel Mai on 26.04.2018.
//
/**************************************************************************/
/* Application creates an iterative server design                         */
/**************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_PORT  12345

main (int argc, char *argv[])
{
    int    i, len, num, rc, on = 1;
    int    listen_sd, accept_sd;
    char   buffer[80];
    struct sockaddr_in6   addr;

    /*************************************************/
    /* If an argument was specified, use it to       */
    /* control the number of incoming connections    */
    /*************************************************/
    if (argc >= 2)
        num = atoi(argv[1]);
    else
        num = 1;

    /*************************************************/
    /* Create an AF_INET6 stream socket to receive   */
    /* incoming connections on                       */
    /*************************************************/
    listen_sd = socket(AF_INET6, SOCK_STREAM, 0);
    if (listen_sd < 0)
    {
        perror("socket() failed");
        exit(-1);
    }

    /*************************************************/
    /* Allow socket descriptor to be reuseable       */
    /*************************************************/
    rc = setsockopt(listen_sd,
                    SOL_SOCKET,  SO_REUSEADDR,
                    (char *)&on, sizeof(on));
    if (rc < 0)
    {
        perror("setsockopt() failed");
        close(listen_sd);
        exit(-1);
    }

    /*************************************************/
    /* Bind the socket                               */
    /*************************************************/
    memset(&addr, 0, sizeof(addr));
    addr.sin6_family      = AF_INET6;
    memcpy(&addr.sin6_addr, &in6addr_any, sizeof(in6addr_any));
    addr.sin6_port        = htons(SERVER_PORT);
    rc = bind(listen_sd,
              (struct sockaddr *)&addr, sizeof(addr));
    if (rc < 0)
    {
        perror("bind() failed");
        close(listen_sd);
        exit(-1);
    }

    /*************************************************/
    /* Set the listen back log                       */
    /*************************************************/
    rc = listen(listen_sd, 5);
    if (rc < 0)
    {
        perror("listen() failed");
        close(listen_sd);
        exit(-1);
    }

    /*************************************************/
    /* Inform the user that the server is ready      */
    /*************************************************/
    printf("The server is ready\n");

    /*************************************************/
    /* Go through the loop once for each connection  */
    /*************************************************/
    for (i=0; i < num; i++)
    {
        /**********************************************/
        /* Wait for an incoming connection            */
        /**********************************************/
        printf("Interation: %d\n", i+1);
        printf("  waiting on accept()\n");
        accept_sd = accept(listen_sd, NULL, NULL);
        if (accept_sd < 0)
        {
            perror("accept() failed");
            close(listen_sd);
            exit(-1);
        }
        printf("  accept completed successfully\n");

        /**********************************************/
        /* Receive a message from the client          */
        /**********************************************/
        printf("  wait for client to send us a message\n");
        rc = recv(accept_sd, buffer, sizeof(buffer), 0);
        if (rc <= 0)
        {
            perror("recv() failed");
            close(listen_sd);
            close(accept_sd);
            exit(-1);
        }
        printf("  <%s>\n", buffer);

        /**********************************************/
        /* Echo the data back to the client           */
        /**********************************************/
        printf("  echo it back\n");
        len = rc;
        rc = send(accept_sd, buffer, len, 0);
        if (rc <= 0)
        {
            perror("send() failed");
            close(listen_sd);
            close(accept_sd);
            exit(-1);
        }

        /**********************************************/
        /* Close down the incoming connection         */
        /**********************************************/
        close(accept_sd);
    }

    /*************************************************/
    /* Close down the listen socket                  */
    /*************************************************/
    close(listen_sd);
}
