// Includes //
#include "../include/searchProgram.h"


// Function Definitions //
int CalculateASCIITotal(char* word)
{
    // Variable declaration
    int asciiTotal = 0;

    // Adds the ascii values of each character
    for(int i = 0; i < strlen(word); i++)
    {
        asciiTotal += (int)word[i];
    }

    // Returns ascii total
    return asciiTotal;
}

char **ExtractItems(const char *text, const char *sepChars, int *numItemsRef)
{
    // printf("Started extractItems!\n");

    // Variable declaration
    char *tokenizedString = 0;
    char *currToken = NULL;
    char **itemsArray = NULL;
    int currItemIndex = 0;

    // Tokenizes string, adds each token to the output array
    tokenizedString = (char *)malloc(sizeof(char) * (strlen(text) + 1));
    strcpy(tokenizedString, text);
    currToken = strtok(tokenizedString, sepChars);

    while (currToken != NULL)
    {
        if (itemsArray != NULL)
        {
            itemsArray = (char **)realloc(itemsArray, sizeof(char *) * (currItemIndex + 1));
        }
        else
        {
            itemsArray = (char **)malloc(sizeof(char *) * (currItemIndex + 1));
        }

        itemsArray[currItemIndex] = (char *)malloc(sizeof(char) * (strlen(currToken) + 1));
        strcpy(itemsArray[currItemIndex], currToken);

        // Gets new token, continues to next
        currToken = strtok(NULL, sepChars);
        currItemIndex++;
    }

    // Frees the tokenized string as it is no longer needed
    free(tokenizedString);

    // Sets value of numItemsRef to the number of items
    *numItemsRef = currItemIndex;
    // printf("Finished extractItems!\n");

    // Returns the extracted items
    return itemsArray;
}

void SetStringVariable(char** stringVar, char* text)
{
    if(*stringVar == NULL)
    {
        *stringVar = (char*)malloc(sizeof(char*)*(strlen(text)+1));
        strcpy(*stringVar, text);
    }

    else
    {
        *stringVar = (char*)realloc(*stringVar, sizeof(char*)*(strlen(text)+1));
        strcpy(*stringVar, text);
    }
}

void SetStringCase(char* string, int lowerOrUpper)
{
    for(int i = 0; i < strlen(string); i++)
    {
        if(lowerOrUpper <= 0)
        {
            string[i] = tolower(string[i]);
        }

        else
        {
            string[i] = toupper(string[i]);
        }
    }
}

int IsDirectory(const char *path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
    {
        return 0;
    }
    return S_ISDIR(statbuf.st_mode);
}

bool GetYesNoInput(char* promptQuestion)
{
    // Variable declaration
    char userInput[MAX_CMD_INPUT];
    char selectedOption = 'a';

    // Loops until y/n is received, then returns and ends function
    while(true)
    {
        // Gets input
        printf("%s%s [y/n]: %s",PROMPT_COLOUR, promptQuestion, USER_COLOUR);
        fgets(userInput, MAX_CMD_INPUT, stdin);
        fflush(stdin);

        // Retrieves selected option from input (uses first char)
        selectedOption = userInput[0];

        // Checks if selected option is yes or no, returns true or false if it is
        if(tolower(selectedOption) == 'y')
        {
            return true;
        }
        else if(tolower(selectedOption) == 'n')
        {
            return false;
        }
    }
}

AbstractStackNode* CreateIntersectionStack(AbstractStackNode* stack1, AbstractStackNode* stack2)
{
    // Variable declaration
    AbstractStackNode* intersection = NULL;
    AbstractStackNode* currentNode = NULL;
    AbstractStackNode* retrievedTableNode = NULL;
    AbstractStackNode* newNode = NULL;
    AbstractStackNode* foundNodeWithPointer = NULL;
    HashTable* stack1Table = NULL;
    char keyText[512];
    unsigned long tempTableIndex = 0; 

    // Returns NULL if either stack is NULL
    if(stack1 == NULL || stack2 == NULL)
    {
        return NULL;
    }
    
    // Creates a hash table from the items in stack1
    stack1Table = InitializeHashTable(GetStackLength(stack1)*3);
    currentNode = stack1;
    while(currentNode != NULL)
    {
        // Sets the key text and index
        sprintf(keyText, "%p", currentNode->itemPointer);
        tempTableIndex = GetTableKeyIndex(stack1Table, keyText);

        // Tries retrieving the node at this index
        retrievedTableNode = RetrieveHashTableItemByIndex(stack1Table, tempTableIndex);

        // Generates a new node
        newNode = CreateEmptyStackNode();
        newNode->itemPointer = currentNode->itemPointer;

        // If it's NULL, sets it to a copy of the current node
        if(retrievedTableNode == NULL)
        {
            InsertHashTableItemByIndex(stack1Table, tempTableIndex, newNode);
        }

        // Otherwise, pushes this to the existing array at that index
        else
        {
            PushStackNode((AbstractStackNode**)&(stack1Table->valuesArray[tempTableIndex]), newNode);
            if(((AbstractStackNode*)RetrieveHashTableItemByIndex(stack1Table, tempTableIndex))->itemPointer != newNode->itemPointer)
            {
                printf("%sERROR: COULD NOT SUCCESSFULLY PUSH A NEW NODE TO A STACK AT AN INDEX IN THE TABLE!\n", ERROR_COLOUR);
            }
        }

        // Moves to next node
        currentNode = currentNode->next;
        strcpy(keyText, "\0");
        tempTableIndex = 0;
        retrievedTableNode = NULL;
        newNode = NULL;
    }

    // Checks if items from stack2 exist in the hash table of stack1. If they do, adds them to the intersection.
    currentNode = stack2;
    while(currentNode != NULL)
    {
        // Sets the key text and index
        sprintf(keyText, "%p", currentNode->itemPointer);
        tempTableIndex = GetTableKeyIndex(stack1Table, keyText);

        // Retrieves the node from the table
        retrievedTableNode = RetrieveHashTableItemByIndex(stack1Table, tempTableIndex);

        // Tries retrieving the node containing the current node's itemPointer from this stack
        foundNodeWithPointer = GetStackNodeByContentsPtr(retrievedTableNode, currentNode->itemPointer);

        // If it finds a node with that pointer, creates a copy and puts it in the intersection stack
        if(foundNodeWithPointer != NULL)
        {
            newNode = CreateEmptyStackNode();
            newNode->itemPointer = foundNodeWithPointer->itemPointer;
            PushStackNode(&intersection, newNode);
        }

        // Moves to next node
        currentNode = currentNode->next;
        strcpy(keyText, "\0");
        tempTableIndex = 0;
        newNode = NULL;
        retrievedTableNode = NULL;
        foundNodeWithPointer = NULL;
    }

    // Clears generated hash table
    for(int i = 0; i < stack1Table->size; i++)
    {
        ClearAbstractStack(stack1Table->valuesArray[i]);
    }
    ClearHashTable(stack1Table);

    // Returns intersection stack
    return intersection;
}