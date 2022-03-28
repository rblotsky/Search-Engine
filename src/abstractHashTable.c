// Includes //
#include "../include/abstractHashTable.h"


// Function Definitions //
HashTable* InitializeHashTable(int numItems)
{
    // Generates a new empty table and returns it
    HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));
    newTable->size = numItems;
    newTable->valuesArray = (void**)calloc(numItems, sizeof(void*));

    return newTable;
}

void* RetrieveHashTableItem(HashTable* table, char* key)
{
    // Hashes key and returns item
    return RetrieveHashTableItemByIndex(table, HashDJB2(key)%(table->size));
}

bool InsertHashTableItem(HashTable* table, char* key, void* item)
{
    // Hashes key and returns item
    return InsertHashTableItemByIndex(table, HashDJB2(key)%(table->size), item);
}

bool ExistsHashTableKey(HashTable* table, char* key)
{
    // Returns false if the key is NULL, true otherwise.
    return (RetrieveHashTableItem(table, key) != NULL);
}

void* RetrieveHashTableItemByIndex(HashTable* table, unsigned long index)
{    
    // Prints error if index too large
    if(index >= table->size)
    {
        printf("%sERROR: RetrieveItem() generated index larger than size of table: (%ld >= %d)\n", RED_REG, index, table->size);
        return NULL;
    }

    // Tries retrieving the item at that index
    return table->valuesArray[index];
}

bool InsertHashTableItemByIndex(HashTable* table, unsigned long index, void* item)
{
    // Prints error if index too large
    if(index >= table->size)
    {
        printf("%sERROR: InsertItem() generated index larger than size of table: (%ld >= %d)\n", RED_REG, index, table->size);

        // Returns false if it couldn't add
        return false;
    }

    // Sets the value at that index to the new item (This can override the item currently there)
    table->valuesArray[index] = item;

    // Returns true if successfully added
    return true;
}


void ClearHashTable(HashTable* table)
{
    // Frees the array of pointers and the table itself
    free(table->valuesArray);
    free(table);
}

unsigned long GetTableKeyIndex(HashTable* table, char* key)
{
    return HashDJB2(key)%(table->size);
}

unsigned long HashDJB2(char* str)
{
    // Using string hash function "djb2" taken from http://www.cse.yorku.ca/~oz/hash.html
    // I do *not* understand why it works but it seems to be pretty effective.
    unsigned long hash = 5381;
    int c = *str;
    int strIndex = 0;

    // Loops until c is null char (Will loop forever on non-terminating strings!)
    while (c)
    {
        c = str[strIndex];
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        strIndex++;
    }

    //printf("%sHash for { %s } is %ld\n", GREEN_BOLD, str, hash);
    return hash;
}