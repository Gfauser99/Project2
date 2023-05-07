#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#define MAX_CARDS 52
#define MAX_CARD_LENGTH 4
int printEmptyBoard();
int printBoardStartupPhase();
int loadFile(char[]);
void shuffleCards(char cards[MAX_CARDS][MAX_CARD_LENGTH], char shuffled_cards[MAX_CARDS][MAX_CARD_LENGTH]);
int saveDeck(char cards[MAX_CARDS][MAX_CARD_LENGTH], char filename[]);
void trim_white_space(char *str);
bool game = true;
bool loaded = false;
char ok[3] = "OK";



/** TODO IN PREPARE PHASE:
 *          1. Accept file-option in SD.
 *          2. If no optional input - load basic file OR create array
 *          3. Validate file content/name before loading.
 */

char cards[MAX_CARDS][MAX_CARD_LENGTH];
char last_command[30];
char command_1[4];
char command_2[25];




int main() {


  //  char test123[]="KS";
   /* FILE *file = fopen("cards.txt", "r");
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
    }*/

   // fclose(file);

    // Print the array to check the result
  //  for (int j = 0; j < i; j++) {
  //      printf("%s\n", cards[j]);
 //   }
   // printf("%s",cards[51]);
  //  int result = strcmp(test123,cards[51]);
   // printf("%d\n",result);
    printf("\nC1 \tC2 \tC3 \tC4 \tC5 \tC6 \tC7 \t\n\n" );
    printf("\t\t\t\t\t\t\t\t[]\tF1\n\n\t\t\t\t\t\t\t\t[]\tF2\n\n\t\t\t\t\t\t\t\t[]\tF3\n\n\t\t\t\t\t\t\t\t[]\tF4\n");
    printf("LAST COMMAND:\nMessage:\nINPUT > ");
    while(game) {

        fgets(last_command, sizeof(last_command), stdin);
        printf("%s",last_command);
            char *token = strtok(last_command, " ");
            strncpy(command_1, token, sizeof(command_1) - 1);
            command_1[sizeof(command_1) - 1] = '\0';
            trim_white_space(command_1);
            token = strtok(NULL, " ");

            if (token != NULL &&
                (strcmp(command_1, "LD") == 0 || strcmp(command_1, "SI") == 0 || strcmp(command_1, "SD") == 0)) {
                strncpy(command_2, token, sizeof(command_2) - 1);
                command_2[sizeof(command_2) - 1] = '\0';
                trim_white_space(command_2);
            } else {
                command_2[0] = '\0';
            }

            if (strlen(command_2) > 0) {
                printf("Sentence 2: %s\n", command_2);
                if (strcmp(command_2, "test") == 0) { printf("correct string capture"); }
                else { printf("incorrect string!!!! %s", command_2); }
            }
            printBoardStartupPhase();




    }

    return 0;
}




    //while(last_command!="Q") {
    //printEmptyBoard();
    //scanf("%s",&last_command);







int printBoardStartupPhase() {

    if (strcmp(command_1, "QQ") == 0) {
        game = false;
        return 0;
    }
    char msg[30] = "";
    int j = 1;
    int k = 0;
    //Always print top columns
    printf("\nC1 \tC2 \tC3 \tC4 \tC5 \tC6 \tC7 \t\n\n");

    if (strcmp(command_1, "LD") == 0) {
        if (strcmp(command_2, "") == 0) {
              const char *suits = "CDHS";
                const char *values = "A23456789TJQK";

                int index = 0;
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 13; j++) {
                        cards[index][0] = values[j];
                        cards[index][1] = suits[i];
                        cards[index][2] = '\0';
                        index++;
                    }
                }
                loaded=true;
                strcpy(msg, ok);
        }
        else {
        if (access(command_2, F_OK) == 0) {
            loadFile(command_2);
            strcpy(msg, ok);}
        else{ strcpy(msg, "Error - file doesn't exist");}
        }
        for (int i = 1; i < 9; i++) {
            if (i % 2 != 0) {
                printf("[]\t[]\t[]\t[]\t[]\t[]\t[]\t\t[]\tF%d\n", j);
                j++;
            }
            if (i % 2 == 0 && i < 8) {
                printf("[]\t[]\t[]\t[]\t[]\t[]\t[]\n");
            }
        }
        printf("[]\t[]\t[]\n");

    }

    if (strcmp(command_1, "SW") == 0) {
        if (!loaded) {
            strcpy(msg, "Error - no file loaded");
        }
            // Change k to 0 to start from the first index
        else {
            for (int i = 1; i < 9; i++) {
                if (i % 2 != 0) {
                    printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t\t[]\tF%d\n", cards[k], cards[k + 1], cards[k + 2],
                           cards[k + 3], cards[k + 4], cards[k + 5], cards[k + 6], j);
                    k = k + 7;
                    j++;
                }
                if (i % 2 == 0 && i < 8) {
                    printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n", cards[k], cards[k + 1], cards[k + 2], cards[k + 3],
                           cards[k + 4], cards[k + 5], cards[k + 6]);
                    k = k + 7;
                }
            }
            printf("%s\t%s\t%s\n", cards[49], cards[50],
                   cards[51]); // Change the last line to print the last 3 elements
            strcpy(msg, ok);
        }
    }

    if (strcmp(command_1, "SI") == 0) {
        if (loaded) {
            int mix_index = 0;
            srand(time(NULL));
            int pile_size = (rand() % 51) + 1;
            int valid_shuffle_index = 1;

            if (strcmp(command_2, "") != 0) {
                if (atoi(command_2) < 51 && atoi(command_2) > 1) {

                    pile_size = atoi(command_2);
                }
                else {
                strcpy(msg, "Error - shuffle index");
                printf("%s\n", msg);
                valid_shuffle_index = 0;
            }}


            if (valid_shuffle_index) {
                char pile1[pile_size][MAX_CARD_LENGTH], pile2[MAX_CARDS - pile_size][MAX_CARD_LENGTH];


                for (int i = 0; i < pile_size; i++) {
                    strcpy(pile1[i], cards[i]);
                    if (i + pile_size < MAX_CARDS) {
                        strcpy(pile2[i], cards[i + pile_size]);
                    }
                }
                if (pile_size < MAX_CARDS / 2) {
                    for (int i = 2 * pile_size; i < MAX_CARDS; i++) {
                        strcpy(pile2[i - pile_size], cards[i]);
                    }
                }
                // IF pile 1 is bigger than pile 2, this section will mix the piles
                if (2 * pile_size >= MAX_CARDS) {
                    while ((mix_index + pile_size) < MAX_CARDS) {
                        strcpy(cards[2 * mix_index], pile1[mix_index]);
                        printf("Card in index %d: %s\n", 2 * mix_index, cards[2 * mix_index]);
                        strcpy(cards[2 * mix_index + 1], pile2[mix_index]);
                        printf("Card in index %d: %s\n", 2 * mix_index + 1, cards[2 * mix_index + 1]);
                        mix_index++;
                    }
                    int new_mix_index = 2 * mix_index;
                    while (mix_index < pile_size) {
                        strcpy(cards[new_mix_index], pile1[mix_index]);
                        new_mix_index++;
                        mix_index++;
                    }
                }
                    // IF pile 2 is bigger than pile 1, this section will mix the piles instead
                else {

                    while ((mix_index + MAX_CARDS - pile_size) < MAX_CARDS) {

                        strcpy(cards[2 * mix_index], pile1[mix_index]);
                        printf("Card in index %d: %s\n", 2 * mix_index, cards[2 * mix_index]);
                        strcpy(cards[2 * mix_index + 1], pile2[mix_index]);
                        printf("Card in index %d: %s\n", 2 * mix_index + 1, cards[2 * mix_index + 1]);

                        mix_index++;
                    }
                    int new_mix_index = 2 * mix_index;
                    while (new_mix_index < MAX_CARDS) {
                        strcpy(cards[new_mix_index], pile2[mix_index]);
                        printf("Card at index %d: %s\n", new_mix_index, cards[new_mix_index]);
                        new_mix_index++;
                        mix_index++;
                    }
                }
                strcpy(msg, ok);
            }


        }
        else { strcpy(msg, "Error - no file loaded");
        }
        for (int i = 1; i < 9; i++) {
            if (i % 2 != 0) {
                printf("[]\t[]\t[]\t[]\t[]\t[]\t[]\t\t[]\tF%d\n", j);
                j++;
            }
            if (i % 2 == 0 && i < 8) {
                printf("[]\t[]\t[]\t[]\t[]\t[]\t[]\n");
            }
        }
        printf("[]\t[]\t[]\n");


    }

    if (strcmp(command_1, "SR") == 0) {
        if (!loaded){
            strcpy(msg,"Error - no file loaded");}
        else {
        char shuffled_cards[MAX_CARDS][MAX_CARD_LENGTH];
        shuffleCards(cards, shuffled_cards);
            for (int i = 1; i < 9; i++) {
                if (i % 2 != 0) {
                    printf("[]\t[]\t[]\t[]\t[]\t[]\t[]\t\t[]\tF%d\n", j);
                    j++;}
                if (i%2 == 0 && i < 8) {
                    printf("[]\t[]\t[]\t[]\t[]\t[]\t[]\n");
                }
            }
            printf("[]\t[]\t[]\n");
            strcpy(msg,ok);

    }}
    if (strcmp(command_1, "SD") == 0) {
        if (!loaded){
            strcpy(msg,"Error - no file loaded");}
        else {
            for (int i = 1; i < 9; i++) {
                if (i % 2 != 0) {
                    printf("[]\t[]\t[]\t[]\t[]\t[]\t[]\t\t[]\tF%d\n", j);
                    j++;}
                if (i%2 == 0 && i < 8) {
                    printf("[]\t[]\t[]\t[]\t[]\t[]\t[]\n");
                }
            }
            printf("[]\t[]\t[]\n");
            if (access(command_2, F_OK) == 0) {
            saveDeck(cards, command_2);
            strcpy(msg,ok);
        }
            else if (strcmp(command_2,"")==0){
               saveDeck(cards, "cards.txt");
            }
        }
    }

    if (strcmp(msg,"")==0){
        strcpy(msg,"Error - invalid command");
    }

    if ( !loaded  || (strcmp(command_1,"")==0 || strcmp(msg,ok)!=0)){
        printf("\t\t\t\t\t\t\t\t[]\tF1\n\n\t\t\t\t\t\t\t\t[]\tF2\n\n\t\t\t\t\t\t\t\t[]\tF3\n\n\t\t\t\t\t\t\t\t[]\tF4\n");
    }


    printf("\nLAST COMMAND: %s %s \nMessage: %s\nINPUT > ", command_1,command_2,msg);


return 0;

}

int loadFile(char cardfile[]) {

    FILE *file = fopen(cardfile, "r");
   // printf("%s",cardfile);
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }


    int i = 0;

    while (fgets(cards[i], MAX_CARD_LENGTH, file) != NULL && i < MAX_CARDS) {
// Remove newline character if present
        size_t len = strlen(cards[i]);
        if (cards[i][len - 1] == '\n') {
            cards[i][len - 1] = '\0';
        }

        i++;
    }
    fclose(file);
    loaded= true;
    return 0;
}

void shuffleCards(char cards[MAX_CARDS][MAX_CARD_LENGTH], char shuffled_cards[MAX_CARDS][MAX_CARD_LENGTH]) {
    // Copy cards into shuffled_cards
    for (int i = 0; i < MAX_CARDS; i++) {
        strcpy(shuffled_cards[i], cards[i]);
    }



   // Fisher-yates shuffle style from online example
    for (int i = MAX_CARDS - 1; i > 0; i--) {
        int random_index = rand() % (i + 1);

        // Swap shuffled_cards[i] and shuffled_cards[random_index]
        char temp[MAX_CARD_LENGTH];
        strcpy(temp, shuffled_cards[i]);
        strcpy(shuffled_cards[i], shuffled_cards[random_index]);
        strcpy(shuffled_cards[random_index], temp);
    }
    for (int i = 0;i < MAX_CARDS; i++){
        strcpy(cards[i],shuffled_cards[i]);
    }
}

int saveDeck(char cards[MAX_CARDS][MAX_CARD_LENGTH], char filename[]){
FILE *file = fopen(filename, "w");
if (file == NULL) {
printf("Error opening file.\n");
return 1;
}

for (int i = 0; i < MAX_CARDS; i++) {
fprintf(file, "%s\n", cards[i]);
}

fclose(file);

return 0;
}

void trim_white_space(char *str) {
    int last_non_space = -1;
    for (int i = 0; str[i]; ++i) {
        if (!isspace((unsigned char)str[i])) {
            last_non_space = i;
        }
    }
    if (last_non_space != -1) {
        str[last_non_space + 1] = '\0';
    }
}