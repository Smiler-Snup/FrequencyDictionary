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


// ��������� ��� ������������� ���-�������
struct HashTable
{
	struct List* buckets;
	int size; // ������� ������ �������
	int count; // ������� ���������� ���������
};

// �������� � ����������� ���-�������
struct HashTable* createHashTable(int size);
void destroyHashTable(struct HashTable* table);

// ������� �������� � ���-�������
void insert(struct HashTable* table, const char* key, int value);

// ��������� �������� �� �����
struct GetResult get(struct HashTable* table, const char* key);

//���������� �������� �� �����
void updateValue(struct HashTable* table, const char* key, int value);

// �������� �������� �� �����
void removeEntry(struct HashTable* table, const char* key);

//��������� ���������� �� ������� � ������ ������
int contain(struct HashTable* table, const char* key);

// ��������������� ������� ��� ���������� ����
unsigned int hash(const char* key, int size);

void printHashTable(struct HashTable* table);

// ������� ��� ������ ��������������� �������
void printHashTableSort(struct HashTable* table);