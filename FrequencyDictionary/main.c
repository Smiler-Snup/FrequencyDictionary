#include <stdio.h>

#include "list.h"
#include "dictionary.h"

void countWordsInFile(const char* filename)
{

    FILE* file;
    if (fopen_s(&file, filename, "r") != 0) {
        printf("Ошибка открытия файла.\n");
        return;
    }


    struct HashTable* hash = createHashTable(100);
    char word[100];
    char symbol;
    int wordLength = 0;

    while ((symbol = fgetc(file)) != EOF)
    {
        if (symbol != '\n' && symbol != ' ' && symbol != '.' && symbol != ',')
        {
            word[wordLength++] = symbol;
        }
        else
        {
            if (wordLength == 0)
                continue;

            word[wordLength] = '\0';
            struct GetResult result = get(hash, word);
            if (result.found)
                updateValue(hash, word, result.value + 1);
            else
                insert(hash, word, 1);
            wordLength = 0;

        }
    }
    if (wordLength >0)
    {
        word[wordLength] = '\0';
        struct GetResult result = get(hash, word);
        if (result.found)
            updateValue(hash, word, result.value + 1);
        else
            insert(hash, word, 1);
    }
    fclose(file);

    printHashTableSort(hash);

    destroyHashTable(hash);
}

int main() {
    
    system("chcp 65001");
    const char* filename = "file.txt";
    countWordsInFile(filename);

    return 0;
}