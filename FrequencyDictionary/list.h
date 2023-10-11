#pragma once
#include <stdlib.h>
#include "dictionary.h"

struct Node
{
	struct KeyValuePair* pair;
	struct Node* next;
};

struct List
{
	struct Node* head;
};

struct Node* createNode(char* key, int value);

void init(struct List** list);
void push(struct List* list, char* key, int value);
void removeNode(struct List* list, char* key);
void printList(struct List* list);