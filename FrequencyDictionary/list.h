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

//Инициализирует список
void init(struct List** list);
//Добавляет элемент в начало списка
void push(struct List* list, char* key, int value);
//Удаляет элемент из списка
void removeNode(struct List* list, char* key);
//Печатает содержимое списка на консоль
void printList(struct List* list);