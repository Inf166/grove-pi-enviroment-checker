//Libary
#include "../grovepi.h"
#include <stdio.h>
#include <string.h>
//Input Output
#define INPUT 0
#define OUTPUT 1
//ports
#define BUTTONPORT 5
#define TEMPPORT 6
#define LIGHTPORT 7
#define HUMPORT 8
#define SOUNDPORT 9
//colors
#define RED 243,23,23
#define GREEN 23, 243, 45
#define WHITE 255, 255, 255

int main(){
    connectLCD();

    setRGB(WHITE);
    setText("Bitte eine Ausgabe auswaehlen:");
    // save the text with a value in char array "text" with the function "sprintf()"
    sprintf(text, "Text mit Wert: %02f", value);
    //show the text
    setText(text);


    return 0;
}
