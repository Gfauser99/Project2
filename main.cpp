#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#define MAX_CARDS 52
#define MAX_CARD_LENGTH 4
#define NUM_LISTS 7




typedef struct CardNode {
    char card[MAX_CARD_LENGTH];
    bool visible;
    struct CardNode *next;
} CardNode;



void playPhasePrintInitial();
void printBoard(CardNode *lists[], int list_lengths[]);
int  printBoardPlayPhase();
int printBoardStartupPhase();
int loadFile(char[]);
void shuffleCards(char cards[MAX_CARDS][MAX_CARD_LENGTH], char shuffled_cards[MAX_CARDS][MAX_CARD_LENGTH]);
int saveDeck(char cards[MAX_CARDS][MAX_CARD_LENGTH], char filename[]);
void trimWhiteSpace(char *str);
void initialCardAppend(CardNode **list, const char *card, int visible_position);
void printBoard(CardNode *lists[], int list_lengths[]);
//void print_list(CardNode *list);

bool game = true;
bool loaded = false;
char ok[3] = "OK";
char msg[30] = "";
char phase[] = "STARTUP";
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

    //initial print
    printf("\nC1 \tC2 \tC3 \tC4 \tC5 \tC6 \tC7 \t\n\n" );
    printf("\t\t\t\t\t\t\t\t[]\tF1\n\n\t\t\t\t\t\t\t\t[]\tF2\n\n\t\t\t\t\t\t\t\t[]\tF3\n\n\t\t\t\t\t\t\t\t[]\tF4\n");
    printf("LAST COMMAND:\nMessage:\nINPUT > ");
    while(game) {

        fgets(last_command, sizeof(last_command), stdin);


        if (strcmp(phase,"STARTUP")==0){
            char *token = strtok(last_command, " ");
            strncpy(command_1, token, sizeof(command_1) - 1);
            command_1[sizeof(command_1) - 1] = '\0';
            trimWhiteSpace(command_1);
            token = strtok(NULL, " ");



            if (token != NULL &&
                (strcmp(command_1, "LD") == 0 || strcmp(command_1, "SI") == 0 || strcmp(command_1, "SD") == 0)) {
                strncpy(command_2, token, sizeof(command_2) - 1);
                command_2[sizeof(command_2) - 1] = '\0';
                trimWhiteSpace(command_2);
            } else {
                command_2[0] = '\0';
            }


            printBoardStartupPhase();}

        else if (strcmp(phase,"PLAY")==0){
            printBoardPlayPhase();
            /** TODO - PlayPhase game */
        }




    }

    return 0;
}




    //while(last_command!="Q") {
    //printEmptyBoard();
    //scanf("%s",&last_command);





int printBoardPlayPhase(){
    trimWhiteSpace(last_command);
    int j=1;
    if (strcmp(last_command,"Q")==0){

        strcpy(phase,"STARTUP");
        printf("\nC1 \tC2 \tC3 \tC4 \tC5 \tC6 \tC7 \t\n\n");
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
    printf("\nLAST COMMAND: %s \nMessage: %s\nINPUT > ", last_command,msg);



    return 0;
}

int printBoardStartupPhase() {
    strcpy(msg,"");

    if (strcmp(command_1, "QQ") == 0) {
        game = false;
        return 0;
    }

    int j = 1;
    int k = 0;
    //Always print top columns
    printf("\nC1 \tC2 \tC3 \tC4 \tC5 \tC6 \tC7 \t\n\n");

    if (strcmp(command_1, "P") == 0) {
        if (!loaded) {
            strcpy(msg, "Error - no file loaded");
        }
        else {
            strcpy(phase,"PLAY");
            strcpy(msg, ok);
            playPhasePrintInitial();

        }
    }

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
            }
        else{ strcpy(msg, "Error - file doesn't exist");}
        }

        if (loaded){
        for (int i = 1; i < 9; i++) {
            if (i % 2 != 0) {
                printf("[]\t[]\t[]\t[]\t[]\t[]\t[]\t\t[]\tF%d\n", j);
                j++;
            }
            if (i % 2 == 0 && i < 8) {
                printf("[]\t[]\t[]\t[]\t[]\t[]\t[]\n");
            }
        }
        printf("[]\t[]\t[]\n");}

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
                if (atoi(command_2) < 52 && atoi(command_2) > 0) {

                    pile_size = atoi(command_2);
                }
                else {
                strcpy(msg, "Error - shuffle index");

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
                       // printf("Card in index %d: %s\n", 2 * mix_index, cards[2 * mix_index]);
                        strcpy(cards[2 * mix_index + 1], pile2[mix_index]);
                       // printf("Card in index %d: %s\n", 2 * mix_index + 1, cards[2 * mix_index + 1]);

                        mix_index++;
                    }
                    int new_mix_index = 2 * mix_index;
                    while (new_mix_index < MAX_CARDS) {
                        strcpy(cards[new_mix_index], pile2[mix_index]);
                      //  printf("Card at index %d: %s\n", new_mix_index, cards[new_mix_index]);
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
                strcpy(msg,ok);
            }
        }
    }

    if (strcmp(msg,"")==0){
        strcpy(msg,"Error - invalid command");
        if (loaded){
            for (int i = 1; i < 9; i++) {
                if (i % 2 != 0) {
                    printf("[]\t[]\t[]\t[]\t[]\t[]\t[]\t\t[]\tF%d\n", j);
                    j++;
                }
                if (i % 2 == 0 && i < 8) {
                    printf("[]\t[]\t[]\t[]\t[]\t[]\t[]\n");
                }
            }
            printf("[]\t[]\t[]\n");}
    }

    if ( !loaded  && (strcmp(command_1,"")==0 || strcmp(msg,ok)!=0)){
        printf("\t\t\t\t\t\t\t\t[]\tF1\n\n\t\t\t\t\t\t\t\t[]\tF2\n\n\t\t\t\t\t\t\t\t[]\tF3\n\n\t\t\t\t\t\t\t\t[]\tF4\n");
    }


    printf("\nLAST COMMAND: %s %s \nMessage: %s\nINPUT > ", command_1,command_2,msg);


return 0;

}

int loadFile(char cardfile[]) {
    FILE *file = fopen(cardfile, "r");

    if (file == NULL) {
        return 1;
    }

    char temp_cards[MAX_CARDS][MAX_CARD_LENGTH];
    int i = 0;

    while (fgets(temp_cards[i], MAX_CARD_LENGTH, file) != NULL && i < MAX_CARDS) {
        size_t len = strlen(temp_cards[i]);
        if (temp_cards[i][len - 1] == '\n') {
            temp_cards[i][len - 1] = '\0';
        }
        i++;
    }
    fclose(file);

    if (i != MAX_CARDS) {
        strcpy(msg,"Error - wrong file content");
        return 1;
    }

    const char *suits = "CDHS";
    const char *values = "A23456789TJQK";
    int found;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            found = 0;
            char card[3] = {values[j], suits[i], '\0'};
            for (int k = 0; k < MAX_CARDS; k++) {
                if (strcmp(card, temp_cards[k]) == 0) {
                    found = 1;
                    break;
                }
            }
            if (!found) {

                printf("Error: Card %s not found in the file.\n", card);
                return 1;
            }
        }
    }

    for (int i = 0; i < MAX_CARDS; i++) {
        strcpy(cards[i], temp_cards[i]);
    }

    strcpy(msg, ok);
    loaded = true;
    return 0;
}

void shuffleCards(char cards[MAX_CARDS][MAX_CARD_LENGTH], char shuffled_cards[MAX_CARDS][MAX_CARD_LENGTH]) {
    // Copy cards into shuffled_cards
    for (int i = 0; i < MAX_CARDS; i++) {
        strcpy(shuffled_cards[i], cards[i]);
    }




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
    strcpy(msg,"Error - file doesn't exist");
return 1;
}

for (int i = 0; i < MAX_CARDS; i++) {
fprintf(file, "%s\n", cards[i]);
}

fclose(file);

return 0;
}

void trimWhiteSpace(char *str) {
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

// Adds cards to lists when play-phase initially starts
// visible_position is used to set initial visibility, since we know which cards will be visible at the start.
void initialCardAppend(CardNode **list, const char *card, int visible_position) {
    CardNode *new_node = (CardNode *)malloc(sizeof(CardNode));
    strcpy(new_node->card, card);
    new_node->next = NULL;
    new_node->visible = visible_position;

    //Choosing where to put cardnode. Will place new_node as latest part of ->
    // -> list (or first & last if list is empty).
    if (*list == NULL) {
        *list = new_node;
    } else {
        CardNode *current = *list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void printBoard(CardNode *lists[], int list_lengths[]) {
    int max_length = 0;
    int F_val=1;

    for (int i = 0; i < NUM_LISTS; i++) {
        if (list_lengths[i] > max_length) {
            max_length = list_lengths[i];
        }
    }

    // Prints every row of the board one at a time. Prints F(1,2,3,4) depending on row
    // and skips the columns in rows where current = 0 (when list doesn't reach length of j)
    for (int i = 0; i < max_length; i++) {
        for (int j = 0; j < NUM_LISTS; j++) {
            CardNode *current = lists[j];
            int k = 0;
            while (current != NULL && k < i) {
                current = current->next;
                k++;
            }

            if (current != NULL) {
                if (current->visible) {
                    printf("%s\t", current->card);
                } else {
                    printf("[]\t");
                }
                if (j==(NUM_LISTS-1) && i%2==0 && i<=6) {
                    printf("\t[]\tF%d",F_val);
                    F_val++;}


            } else {
                printf(" \t");
            }
        }
        printf("\n");

    }
}

void playPhasePrintInitial(){

    // make initial lists with starting lengths
    CardNode *lists[NUM_LISTS] ={};
    int list_lengths[NUM_LISTS] = {1, 6, 7, 8, 9, 10, 11};
    int list_positions[NUM_LISTS] = {0};

    int card_index = 0;
    int list_index = 0;

    // Placing cards from startup-array into the lists. visibility depending on placement and position
    // depending on the card's place in the startup array.
    while (card_index < MAX_CARDS) {
        if (list_positions[list_index] < list_lengths[list_index]) {
            int visible_position = list_positions[list_index] >= list_index;
            initialCardAppend(&lists[list_index], cards[card_index], visible_position);

            list_positions[list_index]++;
            card_index++;
        }
        list_index = (list_index + 1) % NUM_LISTS;
    }

    /* for (int i = 0; i < NUM_LISTS; i++) {
         printf("List %d: ", i + 1);
         print_list(lists[i]);
     }*/

    printBoard(lists, list_lengths);

}




/*Used to make sure, that the lists were set up correctly
void print_list(CardNode *list) {
    CardNode *current = list;
    while (current != NULL) {
        printf("%s -> ", current->card);
        current = current->next;
    }
    printf("NULL\n");
}*/