// Includes //
#include "../include/searchProgram.h"


// Function Definitions //
SearchWordIndex* FindWordIndex(SearchWordIndex* indexHead, char* word)
{
    // Variable declaration
    SearchWordIndex* currentNode = indexHead;

    // Goes through the entirelist of search indices to find one with the right word
    while(currentNode != NULL)
    {
        if(strcmp(currentNode->searchTerm, word) == 0)
        {
            return currentNode;
        }

        // Goes to  next node
        currentNode = currentNode->next;
    }

    // Returns NULL if can't find anything
    return NULL;
}

SearchWordIndex* CreateEmptyWordIndex()
{
    // Mallocs and returns a new empty word index
    SearchWordIndex* newIndex = (SearchWordIndex*)malloc(sizeof(SearchWordIndex));
    newIndex->dataNodesHead = NULL;
    newIndex->searchTerm = NULL;
    newIndex->next = NULL;

    return newIndex;
}

void PushWordIndex(SearchWordIndex** indexHead, SearchWordIndex* newNode)
{
    // Sets the new head to the newNode
    newNode->next = *indexHead;
    *indexHead = newNode;
}

void ClearWordIndexList(SearchWordIndex* indexHead)
{
    // Clears the word index iteratively
    SearchWordIndex* currentWordIndex = indexHead;
    SearchWordIndex* nextWordIndex = NULL;

    while(currentWordIndex != NULL)
    {
        nextWordIndex = currentWordIndex->next;
        ClearAbstractStack(currentWordIndex->dataNodesHead);
        free(currentWordIndex->searchTerm);
        free(currentWordIndex);
        currentWordIndex = nextWordIndex;
    }
}