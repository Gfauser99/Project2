#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CARDS 52
#define MAX_CARD_LENGTH 3
void printEmptyBoard();

int Game = 1;
char last_command[] = "LD";


int main() {
    FILE* ptr;
    char ch;
    ptr = fopen("test.txt", "r");
    if (NULL == ptr) {
        printf("file can't be opened \n");
    }
    while(last_command!="Q") {
    printEmptyBoard();
    scanf("%s",&last_command);


    }
    return 0;
}





void printEmptyBoard(){
    printf("C1 \tC2 \tC3 \tC4 \tC5 \tC6 \tC7 \t\n\n" );
    printf("\t\t\t\t\t\t\t[]\tF1\n\t\t\t\t\t\t\t[]\tF2\n\t\t\t\t\t\t\t[]\tF3\n\t\t\t\t\t\t\t[]\tF4\n");
    printf("LAST COMMAND: %s \nMessage: %s\nINPUT > ",last_command);

}


