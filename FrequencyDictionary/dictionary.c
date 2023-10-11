#include "dictionary.h"
#include "list.h"

struct HashTable* createHashTable(int size) {
    struct HashTable* table = (struct HashTable*)malloc(sizeof(struct HashTable));
    if (table == NULL) {
        printf("Ошибка при выделении памяти для хеш-таблицы\n");
        exit(1);
    }

    table->buckets = (struct List*)malloc(sizeof(struct List) * size);
    if (table->buckets == NULL) {
        free(table);
        printf("Ошибка при выделении памяти для массива корзин\n");
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        struct List* list = &table->buckets[i];
        init(&list);
    }

    table->size = size;
    table->count = 0;

    return table;
}

void destroyHashTable(struct HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        struct List* bucket = &table->buckets[i];
        struct Node* current = bucket->head;

        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp->pair->key);
            free(temp->pair);
            free(temp);
        }
    }

    free(table->buckets);
    free(table);
}

void insert(struct HashTable* table, const char* key, int value) {

    if (contain(table, key)) {
        return;
    }

    unsigned int index = hash(key, table->size);
    struct List* bucket = &table->buckets[index];

    push(bucket, key, value);
    table->count++;
}

int contain(struct HashTable* table, const char* key) {
    
    unsigned int index = hash(key, table->size);
    struct List* bucket = &table->buckets[index];

    struct Node* current = bucket->head;

    while (current != NULL) {
        if (strcmp(current->pair->key, key) == 0) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}

struct GetResult get(struct HashTable* table, const char* key) {
    unsigned int index = hash(key, table->size);
    struct List* bucket = &table->buckets[index];
    struct Node* current = bucket->head;
    struct GetResult result = { 0, false };

    while (current != NULL) {
        if (strcmp(current->pair->key, key) == 0) {
            result.value = current->pair->value;
            result.found = true;
            return result;
        }
        current = current->next;
    }

    return result;
}

void updateValue(struct HashTable* table, const char* key, int value) {
    unsigned int index = hash(key, table->size);
    struct List* bucket = &table->buckets[index];
    struct Node* current = bucket->head;

    while (current != NULL) {
        if (strcmp(current->pair->key, key) == 0) {
            
            current->pair->value = value;
            return;
        }
        current = current->next;
    }
    printf("Ошибка при изменении значения, ключ не существует\n");
    destroyHashTable(table);
    exit(1);
}

void removeEntry(struct HashTable* table, const char* key) {
    unsigned int index = hash(key, table->size);
    struct List* bucket = &table->buckets[index];

    removeNode(bucket, key);
}

unsigned int hash(const char* key, int size)
{
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 16) + *key;
        key++;
    }
    return hash % size;
}

void printHashTable(struct HashTable* table) {
    printf("Hash Table Contents:\n");
    printf("Bucket\t\tKey\t\tValue\n");

    for (int i = 0; i < table->size; i++) {
        struct List* bucket = &table->buckets[i];
        struct Node* current = bucket->head;

        while (current != NULL) {
            printf("%d\t\t%s\t\t%d\n", i, current->pair->key, current->pair->value);
            current = current->next;
        }
    }
}

int compareKeyValuePair(const void* a, const void* b) {
    const struct KeyValuePair* pairA = *(const struct KeyValuePair**)a;
    const struct KeyValuePair* pairB = *(const struct KeyValuePair**)b;
    return pairB->value - pairA->value;
}

void printHashTableSort(struct HashTable* table) {

    struct KeyValuePair** pairs = (struct KeyValuePair**)malloc(table->count * sizeof(struct KeyValuePair*));
    int index = 0;

    for (int i = 0; i < table->size; i++) {
        struct List* bucket = &table->buckets[i];
        struct Node* current = bucket->head;

        while (current != NULL) {
            pairs[index] = current->pair;
            current = current->next;
            index++;
        }
    }

    qsort(pairs, table->count, sizeof(struct KeyValuePair*), compareKeyValuePair);

    printf("Word\t\tCount in the text\n");
    for (int i = 0; i < table->count; i++) {
        printf("%s\t\t%d\n", pairs[i]->key, pairs[i]->value);
    }
}