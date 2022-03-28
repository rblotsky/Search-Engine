// Only if not already included //
#ifndef MAIN_HEADER_INCLUDED


// Includes //
#include "../include/abstractStack.h"
#include "../include/abstractHashTable.h"
#include "../include/libs.h"

// Macros //
#define MAX_CMD_INPUT 511
#define ASCII_TOTAL_ALGORITHM_EXPONENT 1.5f
#define WORD_SEPARATORS " \t\r\b,.:;!?/\\\'\"-_+=*%%&@()[]{}~`^$#\n<>@|"
#define MAIN_HEADER_INCLUDED 1 // Prevents re-including this
#define MAX_DATA_NODE_DISPLAY_CHARS 256
#define INFO_COLOUR CYAN_REG
#define ERROR_COLOUR RED_REG
#define TITLE_COLOUR CYAN_BOLD
#define TEXT_COLOUR DEFAULT_COLOUR
#define USER_COLOUR DEFAULT_COLOUR
#define PROMPT_COLOUR PURPLE_BOLD
#define ULTIMATE_MAX_INDEX_SIZE 1073741824
#define MAX_ITEMS_DISPLAYED 300

// Struct Definitions //
typedef struct DataNode_struct
{
    int nodeID;
    char* text;
    struct DataNode_struct* next;
} DataNode;

typedef struct SearchWordIndex_struct
{
    char* searchTerm;
    AbstractStackNode* dataNodesHead;
    struct SearchWordIndex_struct* next;
} SearchWordIndex;


// Function Prototypes //
void PushDataNode(DataNode** listHead, DataNode* newNode);

void IndexDataNode(DataNode* node, HashTable* wordHashTable);

DataNode* CreateEmptyDataNode();

DataNode* GetDataNodeByID(DataNode* head, int idToFind);

void DisplayNodeData(DataNode* node);

int GetHighestDataNodeID(DataNode* head);

int GetNumDataNodes(DataNode* head);

unsigned long GetDataNodeMemory(DataNode* node);

void ClearDataList(DataNode* head);

SearchWordIndex* CreateEmptyWordIndex();

void PushWordIndex(SearchWordIndex** indexHead, SearchWordIndex* newNode);

SearchWordIndex* FindWordIndex(SearchWordIndex* indexHead, char* word);

void ClearWordIndexList(SearchWordIndex* indexHead);

char** ExtractItems(const char* text, const char* sepChars, int* numItemsRef);

void SetStringVariable(char** stringVar, char* text);

void SetStringCase(char* string, int lowerOrUpper);

int IsDirectory(const char* path);

bool GetYesNoInput(char* promptQuestion);

AbstractStackNode* CreateIntersectionStack(AbstractStackNode* stack1, AbstractStackNode* stack2);

#endif