// Only if not already included //
#ifndef MENU_FUNCS_INCLUDED

// Includes //
#include "../include/searchProgram.h"

// Prevents re-including
#define MENU_FUNCS_INCLUDED 1


// Function Prototypes //
void MenuAddNodeWithText(DataNode** dataListHead, HashTable* wordHashTable);

void MenuAddNodeFromFile(DataNode** dataListHead, HashTable* wordHashTable);

void MenuDisplayNodes(DataNode* dataListHead);

void MenuSearchNodes(HashTable* wordHashTable);

void MenuViewIndexAnalysis(HashTable* wordHashTable, DataNode* dataNodeHead);

void MenuDisplayEntireNode(DataNode* dataListHead);

void AddNodeFromFile(const char* filePath, DataNode** dataListHead, HashTable* wordHashTable);

void MenuAddManyNodesFromFile(const char* filePath, DataNode** dataListHead, HashTable* wordHashTable);

void MenuViewSpecificIndexAnalysis(HashTable* wordHashTable);

#endif