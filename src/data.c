// Includes //
#include "../include/searchProgram.h"


// Function Definitions //
void PushDataNode(DataNode** listHead, DataNode* newNode)
{
    // Pushes this node to the front of the list
    newNode->next = *listHead;
    *listHead = newNode;
}

void IndexDataNode(DataNode* node, HashTable* wordHashTable)
{
    // Variable declaration
    int numWords = 0;
    char** wordsInNode = NULL;
    AbstractStackNode* foundWordStack = NULL;
    AbstractStackNode* newStackNode = NULL;
    unsigned long keyIndex = -1;

    // Extracts word from the node text
    wordsInNode = ExtractItems(node->text, WORD_SEPARATORS, &numWords);

    // Iterates over all words in the text
    for(int i = 0; i < numWords; i++)
    {
        // Generates a new stack node for this item
        newStackNode = CreateEmptyStackNode();
        newStackNode->itemPointer = node;

        // Sets word text to lowercase and gets its index
        SetStringCase(wordsInNode[i], 0);
        keyIndex = GetTableKeyIndex(wordHashTable, wordsInNode[i]);

        // Tries finding the search index for this word
        foundWordStack = RetrieveHashTableItemByIndex(wordHashTable, keyIndex);

        // If the search index wasn't found, creates it and adds it to the table
        if(foundWordStack == NULL)
        {
            InsertHashTableItemByIndex(wordHashTable, keyIndex, newStackNode);
        }

        // Otherwise, adds a new item the stack found
        else
        {
            // Only adds if it wasn't the last added item to this node
            if(foundWordStack->itemPointer != node)
            {
                PushStackNode(&foundWordStack, newStackNode); // TODO: This can be optimized. Have the hash table return a pointer to the pointer in its storage, and rather than overriding it, just modify it.
                InsertHashTableItemByIndex(wordHashTable, keyIndex, foundWordStack);
            }

            else
            {
                ClearAbstractStack(newStackNode);
            }
        }

        // Resets newStackNode and foundWordStack
        foundWordStack = NULL;
        newStackNode = NULL;

        // Frees the word reference
        free(wordsInNode[i]);
    }

    // Frees wordsInNode pointer
    free(wordsInNode);
}

DataNode* CreateEmptyDataNode()
{
    // Creates the node and returns it.
    DataNode* newNode = (DataNode*)malloc(sizeof(DataNode));
    newNode->nodeID = 0;
    newNode->text = NULL;
    newNode->next = NULL;

    return newNode;
}

int GetHighestDataNodeID(DataNode* head)
{
    // Gets the ID of the first node since that was the one most recently created
    if(head == NULL)
    {
        return 0;
    }

    else
    {
        return head->nodeID;
    }
}

void ClearDataList(DataNode* head)
{
    // Iteratively frees the entire list of nodes
    DataNode* currentNode = head;
    DataNode* nextNode = NULL;

    while(currentNode != NULL)
    {
        nextNode = currentNode->next;
        if(currentNode->text != NULL)
        {
            free(currentNode->text);
        }
        free(currentNode);
        currentNode = nextNode;
    }
}

void DisplayNodeData(DataNode* node)
{
    // Variable declaration
    long int nodeTextLen = strlen(node->text);

    // Prints opening info
    printf("%s[Data ID #%d]",TITLE_COLOUR, node->nodeID);
    printf("%s { ", INFO_COLOUR);
    
    for(int i = 0; i < MAX_DATA_NODE_DISPLAY_CHARS; i++)
    {
        // Breaks out if it goes past string length
        if(i >= nodeTextLen)
        {
            break;
        }

        // Avoids printing certain escape characters for ease of reading
        if(node->text[i] == '\n')
        {
            printf("%s\\n", INFO_COLOUR);
        }
        else if(node->text[i] == '\r')
        {
            printf("%s\\r", INFO_COLOUR);
        }
        else if(node->text[i] == '\b')
        {
            printf("%s\\b", INFO_COLOUR);
        }
        else
        {
            printf("%s%c", TEXT_COLOUR, node->text[i]);
        }
    }
    
    // Prints closing bracket and ellipsis if ended early
    if(nodeTextLen > MAX_DATA_NODE_DISPLAY_CHARS)
    {
        printf("%s(... %ld chars)", INFO_COLOUR, nodeTextLen);
    }
    printf("%s }\n", INFO_COLOUR);
}

DataNode* GetDataNodeByID(DataNode* head, int idToFind)
{
    // Loops through all nodes until it finds the requested one
    DataNode* currentNode = head;

    while(currentNode != NULL)
    {
        if(currentNode->nodeID == idToFind)
        {
            return currentNode;
        }

        currentNode = currentNode->next;
    }

    // Returns NULL if none found
    return NULL;
}

int GetNumDataNodes(DataNode* head)
{
    // Iteratively calculates length of list
    int numNodes = 0;
    DataNode* currentDataNode = head;

    while(currentDataNode != NULL)
    {
        currentDataNode = currentDataNode->next;
        numNodes++;
    }
    
    return numNodes;
}

unsigned long GetDataNodeMemory(DataNode* node)
{
    return (sizeof(char)*strlen(node->text)) + sizeof(DataNode*) + sizeof(int);
}