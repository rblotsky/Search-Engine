// Includes //
#include "../include/libs.h"


// Macros //
#define NUM_ITEMS_SPACE_MULTIPLIER 1


// Struct Definitions //
typedef struct HashTable_struct
{
    int size;
    void** valuesArray;
} HashTable;


// Function Prototypes //
HashTable* InitializeHashTable(int numItems);

void* RetrieveHashTableItem(HashTable* table, char* key);

bool InsertHashTableItem(HashTable* table, char* key, void* item);

void* RetrieveHashTableItemByIndex(HashTable* table, unsigned long index);

bool InsertHashTableItemByIndex(HashTable* table, unsigned long index, void* item);

bool ExistsHashTableKey(HashTable* table, char* key);

void ClearHashTable(HashTable* table);

unsigned long GetTableKeyIndex(HashTable* table, char* key);

unsigned long HashDJB2(char* str);

