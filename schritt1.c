#include "grovepi.h"
#include <stdio.h>
int main() {
    char str1[255];

    printf("Bitte Eingabe.\n");
    printf("GET TEMPERATURE\n");
    printf("GET HUMIDITY\n");
    printf("GET LIGHT\n");
    printf("GET SOUND\n");

    while(1){
        printf(">");
        scanf("%s", &str1);
        char temp[15] = "GET TEMPERATURE";
        char hum[15] = "GET HUMIDITY";
        char light[15] = "GET LIGHT";
        char sound[15] = "GET SOUND";
        if(strcmp(str1, temp)==0){

        } else if(strcmp(str1, hum)==0) {

        }else if (strcmp(str1, light)==0) {

        }else if (strcmp(str1, sound)==0) {

        }
    }
//    switch(str1){
//        case temp:;
//        case hum:;
//        case :;
//        case :;
    }
}
