/**
 * @file main.c
 * @author Kevin Wing (kevinrwing@gmail.com)
 * @brief A C Program that simulates the scheduling for a processor or processors.
 * @date 2022-04-28
 */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

const char *filename = "data.txt";
const int MAX_LINE_LEN = 1024;
const int MAX_TOKENS = 32;
const int MAX_TOKEN_LEN = 64;
const char DELIMITER = ',';

void print_list(const List *list);

int main()
{
    List input_queue;
    List wait_queue;

    init_list(&input_queue);
    init_list(&wait_queue);

    FILE *fin = fopen(filename, "r");
    if (fin == NULL)
    {
        fprintf(stderr, "Error opening %s. Exiting.\n", filename);
        exit(1);
    }

    // printf("Success!\n");

    char str[MAX_LINE_LEN];
    while (!feof(fin) || !ferror(fin))
    {
        char *status = fgets(str, MAX_LINE_LEN, fin);

        // check for end of file.
        if (status == NULL)
        {
            break;
        }

        int count = 0;
        char line_tokens[MAX_TOKENS][MAX_TOKEN_LEN];
        char *token = strtok(str, &DELIMITER);
        while (token)
        {
            strcpy(line_tokens[count++], token);
            // printf("%s\n", line_tokens[count]);
            token = strtok(NULL, &DELIMITER);
        }

        // printf("%s %s %s", line_tokens[0], line_tokens[1], line_tokens[2]);
        Proc *data = new_proc(line_tokens[0], atoi(line_tokens[1]), atoi(line_tokens[2]));
        append(&input_queue, data);
        free(data->name);
        free(data);
    }

    fclose(fin);

    print_list(&input_queue);

    destroy_list(&input_queue);
    destroy_list(&wait_queue);
}

void print_list(const List *list)
{
    Node *ptr = list->head;

    while (ptr != NULL)
    {
        printf("%s | %d | %d\n",
                ptr->data.name,
                ptr->data.e_time,
                ptr->data.n_instructions
        );
        ptr = ptr->next;
    }
    printf("\n");
}