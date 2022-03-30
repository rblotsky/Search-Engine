// Includes //
#include "../include/abstractStack.h"

// Function Definitions //
void PushStackNode(AbstractStackNode** head, AbstractStackNode* node)
{
    node->next = *head;
    if(*head != NULL)
    {
        node->lengthFromHere = (*head)->lengthFromHere + 1;
    }
    else
    {
        node->lengthFromHere = 1;
    }
    *head = node;
}

bool RemoveStackNodeByNodePtr(AbstractStackNode** head, AbstractStackNode* nodePointer)
{
    // Variable declaration
    AbstractStackNode* currentNode = *head;
    AbstractStackNode* prevNode = NULL;

    // Removes the node with the given pointer.
    while(currentNode != NULL)
    {
        if(currentNode == nodePointer)
        {
            // If prevNode is not NULL, sets it to skip currentNode
            if(prevNode != NULL)
            {
                prevNode->next = currentNode->next;
            }

            // If prevNode is NULL, currentNode must be the head
            else
            {
                *head = currentNode->next;
            }

            break;
        }

        // Goes to next node
        prevNode = currentNode;
        currentNode = currentNode->next;
    }

    // If it found a node to remove, frees it
    if(currentNode != NULL)
    {
        free(currentNode);
        return true;
    }

    // Returns false if couldn't find the node
    return false;
}

AbstractStackNode* GetStackNodeByContentsPtr(AbstractStackNode* head, void* containedItemPointer)
{
    // Variable declaration
    AbstractStackNode* currentNode = head;

    // Removes the node with the given pointer.
    while(currentNode != NULL)
    {
        if(currentNode->itemPointer == containedItemPointer)
        {
            break;
        }

        // Prints big bad error message for self-referential nodes
        if(currentNode->next == currentNode)
        {
            printf("%sERROR: SELF-REFERENTIAL NODE FOUND: %p\n STOPPING.\n", RED_BOLD, currentNode);
            break;
        }
        // Goes to next node
        currentNode = currentNode->next;
    }

    // Returns the node that it found (NULL if it reached the end)
    return currentNode;
}

bool ExistsStackNodeByNodePtr(AbstractStackNode* head, AbstractStackNode* nodePointer)
{
    // Variable declaration
    AbstractStackNode* currentNode = head;

    // Removes the node with the given pointer.
    while(currentNode != NULL)
    {
        if(currentNode == nodePointer)
        {
            break;
        }

        // Goes to next node
        currentNode = currentNode->next;
    }

    // If it found a node, returns true
    if(currentNode != NULL)
    {
        return true;
    }

    // Returns false if couldn't find the node
    return false;
}


int GetStackLength(AbstractStackNode* head)
{
    // Determines length using lengthFromHere on head node
    if(head != NULL)
    {
        return head->lengthFromHere;
    }

    return 0;
}

AbstractStackNode* PopStackNode(AbstractStackNode** head)
{
    // Returns the head node and sets head to the next node
    AbstractStackNode* poppedNode = *head;
    poppedNode->lengthFromHere = 1;

    if(*head != NULL)
    {
        *head = (*head)->next;
    }

    return poppedNode;
}

AbstractStackNode* CreateEmptyStackNode()
{
    // Mallocs and returns a new stack node
    AbstractStackNode* newNode = (AbstractStackNode*)malloc(sizeof(AbstractStackNode));
    newNode->itemPointer = NULL;
    newNode->next = NULL;
    newNode->lengthFromHere = 1;

    return newNode;
}

void ClearAbstractStack(AbstractStackNode* head)
{
    // Iteratively clears the stack
    AbstractStackNode* currentNode = head;
    AbstractStackNode* nextNode = NULL;

    while(currentNode != NULL)
    {
        nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;

        // Prints error if next node is head, as that should never happen
        if(nextNode == head)
        {
            printf("%sERROR: ClearAbstractStack found a loop back to HEAD!%s\n", RED_BOLD, DEFAULT_COLOUR);
            return;
        }
    }
}

unsigned long long GetStackNodeMemory(AbstractStackNode* node)
{
    return sizeof(int) + sizeof(void*) + sizeof(AbstractStackNode*);
}

