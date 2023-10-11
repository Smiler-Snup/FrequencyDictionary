#include <stdlib.h>
#include <stdio.h>
#include "list.h"

struct Node* createNode(char* key, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Ошибка при выделении памяти для узла\n");
        exit(1);
    }

    newNode->pair = (struct KeyValuePair*)malloc(sizeof(struct KeyValuePair));
    if (newNode->pair == NULL) {
        printf("Ошибка при выделении памяти для KeyValuePair\n");
        free(newNode);
        exit(1);
    }

    newNode->pair->key = strdup(key);
    newNode->pair->value = value;
    newNode->next = NULL;

    return newNode;
}

void init(struct List** list) {
    
    if (*list == NULL)
    {
        (*list) = (struct List*)malloc(sizeof(struct List));
        if (*list == NULL) {
            printf("Ошибка при выделении памяти для списка\n");
            exit(1);
        }
    }

    (*list)->head = NULL;
}

void push(struct List* list, char* key, int value) {
    struct Node* newNode = createNode(key, value);
    newNode->next = list->head;
    list->head = newNode;
}

void removeNode(struct List* list, char* key)
{
    struct Node* currentHead = list->head;

    if (currentHead == NULL)
        return;

    if (strcmp(currentHead->pair->key, key) == 0)
    {
        list->head = currentHead->next;
        free(currentHead);
        return;
    }

    struct Node* currentNextHead = currentHead->next;

    while (currentNextHead != NULL)
    {
        if (strcmp(currentNextHead->pair->key, key) == 0)
        {
            currentHead->next = currentNextHead->next;
            free(currentNextHead);
            return;
        }
        currentHead = currentNextHead;
        currentNextHead = currentNextHead->next;
    }
}

void printList(struct List* list)
{
	struct Node* current = list->head;

	printf("%-20s %s\n", "Key", "Value");

	while (current != NULL)
	{
		printf("%-20s %d\n", current->pair->key, current->pair->value);
		current = current->next;
	}
}