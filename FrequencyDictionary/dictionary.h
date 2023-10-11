#pragma once
#include "list.h"
#include <stdbool.h>

struct KeyValuePair
{
	char* key;
	int value;
};

struct GetResult {
	int value;
	bool found;
};


// Структура для представления хеш-таблицы
struct HashTable
{
	struct List* buckets;
	int size; // Текущий размер массива
	int count; // Текущее количество элементов
};

// Создание и уничтожение хеш-таблицы
struct HashTable* createHashTable(int size);
void destroyHashTable(struct HashTable* table);

// Вставка элемента в хеш-таблицу
void insert(struct HashTable* table, const char* key, int value);

// Получение значения по ключу
struct GetResult get(struct HashTable* table, const char* key);

//Обновление значения по ключу
void updateValue(struct HashTable* table, const char* key, int value);

// Удаление элемента по ключу
void removeEntry(struct HashTable* table, const char* key);

//Проверяет содержится ли элемент с данным ключом
int contain(struct HashTable* table, const char* key);

// Вспомогательная функция для вычисления хеша
unsigned int hash(const char* key, int size);

void printHashTable(struct HashTable* table);

// Функция для вывода отсортированной таблицы
void printHashTableSort(struct HashTable* table);