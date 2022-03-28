// Includes (Only if not already included)//
#ifndef ABSTRACTLIST_INCLUDED
#include "../include/libs.h"

// Defines ABSTRACTLIST_INCLUDED to avoid including this multiple times
#define ABSTRACTLIST_INCLUDED 1


// Struct Definitions //
typedef struct AbstractStackNode_struct
{
    int lengthFromHere;
    void* itemPointer;
    struct AbstractStackNode_struct* next;
} AbstractStackNode;


// Function Prototypes //
void PushStackNode(AbstractStackNode** head, AbstractStackNode* node);

AbstractStackNode* GetStackNodeByContentsPtr(AbstractStackNode* head, void* containedItemPointer);

bool ExistsStackNodeByNodePtr(AbstractStackNode* head, AbstractStackNode* nodePointer);

bool RemoveStackNodeByNodePtr(AbstractStackNode** head, AbstractStackNode* nodePointer);

int GetStackLength(AbstractStackNode* head);

AbstractStackNode* PopStackNode(AbstractStackNode **head);

AbstractStackNode* CreateEmptyStackNode();

void ClearAbstractStack(AbstractStackNode* head);

unsigned long long GetStackNodeMemory(AbstractStackNode* node);

#endif