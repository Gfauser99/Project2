#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CARDS 52
#define MAX_CARD_LENGTH 5
void printEmptyBoard();
void printLoadedBoard();

int Game = 1;






char cards[MAX_CARDS][MAX_CARD_LENGTH];
char last_command[2] = "";
char msg[]="";
int main() {

    char test123[]="KS";
    FILE *file = fopen("cards.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }


    int i = 0;

    while (fgets(cards[i], MAX_CARD_LENGTH, file) != NULL && i < MAX_CARDS) {
        // Remove newline character if present
        size_t len = strlen(cards[i]);
        if (cards[i][len-1] == '\n') {
            cards[i][len-1] = '\0';
        }

        i++;
    }

    fclose(file);

    // Print the array to check the result
    for (int j = 0; j < i; j++) {
        printf("%s\n", cards[j]);
    }
    printf("%s",cards[51]);
    int result = strcmp(test123,cards[51]);
    printf("%d\n",result);
    while(1) {
        printEmptyBoard();
        scanf("%s",last_command);

    }

    return 0;
}




    //while(last_command!="Q") {
    //printEmptyBoard();
    //scanf("%s",&last_command);







void printEmptyBoard(){

        //Print top of cards always
    printf("C1 \tC2 \tC3 \tC4 \tC5 \tC6 \tC7 \t\n\n" );

    if (strcmp(last_command,"")==0){
            printf("\t\t\t\t\t\t\t[]\tF1\n\n\t\t\t\t\t\t\t[]\tF2\n\n\t\t\t\t\t\t\t[]\tF3\n\n\t\t\t\t\t\t\t[]\tF4\n");
    }

    if (strcmp(last_command,"LD")==0){
        printf("[]\t[]\t[]\t[]\t[]\t[]\t[]\t\t[]\tF1\n"
               "[]\t[]\t[]\t[]\t[]\t[]\t[]\n"
               "[]\t[]\t[]\t[]\t[]\t[]\t[]\t\t[]\tF2\n"
               "[]\t[]\t[]\t[]\t[]\t[]\t[]\n"
               "[]\t[]\t[]\t[]\t[]\t[]\t[]\t\t[]\tF3\n"
               "[]\t[]\t[]\t[]\t[]\t[]\t[]\n"
               "[]\t[]\t[]\t[]\t[]\t[]\t[]\t\t[]\tF4\n"
               "[]\t[]\t[]\n"
               );
    }

    if (strcmp(last_command, "SW") == 0) {
        int j = 1;
        int k = 0; // Change k to 0 to start from the first index
        for (int i = 1; i < 9; i++) {
            if (i % 2 != 0) {
                printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t\t[]\tF%d\n", cards[k], cards[k+1], cards[k+2], cards[k+3], cards[k+4], cards[k+5], cards[k+6], j);
                k = k + 7;
                j++;
            }
            if (i%2 == 0 && i < 8) {
                printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n", cards[k], cards[k+1], cards[k+2], cards[k+3], cards[k+4], cards[k+5], cards[k+6]);
                k = k + 7;
            }
        }
        printf("%s\t%s\t%s\n", cards[49], cards[50], cards[51]); // Change the last line to print the last 3 elements
    }



    printf("LAST COMMAND: %s \nMessage: %s\nINPUT > ", last_command,msg);


}

void printLoadedBoard(char *last_command, char cards[MAX_CARDS][MAX_CARD_LENGTH]){
    printf("C1 \tC2 \tC3 \tC4 \tC5 \tC6 \tC7 \t\n\n" );
    printf("\t\t\t\t\t\t\t[]\tF1\n\t\t\t\t\t\t\t[]\tF2\n\t\t\t\t\t\t\t[]\tF3\n\t\t\t\t\t\t\t[]\tF4\n");
    printf("LAST COMMAND: %s \nMessage: %s\nINPUT > ",last_command,msg);
}

