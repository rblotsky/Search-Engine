// Includes //
#include "../include/menuFunctions.h"


// Function Definitions //
void MenuAddNodeWithText(DataNode** dataListHead, HashTable* wordHashTable)
{
    // Variable declaration 
    char nodeText[MAX_CMD_INPUT];
    DataNode* newNode = NULL;

    // Asks user for text to write
    printf("%sEnter text (Max %d chars): %s",PROMPT_COLOUR, MAX_CMD_INPUT, USER_COLOUR);
    fgets(nodeText, MAX_CMD_INPUT, stdin);
    fflush(stdin);

    // Removes newline at end if it's present
    if (nodeText[strlen(nodeText) - 1] == '\n')
    {
        nodeText[strlen(nodeText) - 1] = '\0';
    }

    // Creates the data node and inserts it
    newNode = CreateEmptyDataNode();
    SetStringVariable(&(newNode->text), nodeText);
    newNode->nodeID = GetHighestDataNodeID(*dataListHead)+1;
    PushDataNode(dataListHead, newNode);

    // Indexes the data node
    IndexDataNode(newNode, wordHashTable);
}

void MenuAddNodeFromFile(DataNode** dataListHead, HashTable* wordHashTable)
{
    // Variable declaration 
    char inputPath[MAX_CMD_INPUT];
    DIR* inputFolder = NULL;
    struct dirent* inputFile;
    char* inputFileFullPath = NULL;
    clock_t indexStartTime, indexEndTime;

    // Asks user for file name
    printf("%sEnter a file name (Max %d chars): %s",PROMPT_COLOUR, MAX_CMD_INPUT, USER_COLOUR);
    fgets(inputPath, MAX_CMD_INPUT, stdin);
    fflush(stdin);

    // Removes newline at end if it's present
    if (inputPath[strlen(inputPath) - 1] == '\n')
    {
        inputPath[strlen(inputPath) - 1] = '\0';
    }

    // Starts indexing
    indexStartTime = clock();
    printf("%sStarting indexing!\n", INFO_COLOUR);

    // Checks if it's a directory
    if(IsDirectory(inputPath))
    {
        // Tries opening directory
        inputFolder = opendir(inputPath);
        if (inputFolder == NULL) 
        {
            printf("%sERROR: Failed to open input directory \"%s\"\n",ERROR_COLOUR, inputPath);
        }

        // If it opens successfully, reads from it and adds the file
        else
        {
            while((inputFile = readdir(inputFolder)))
            {
                // Ignores current and parent directory
                if (strcmp (inputFile->d_name, ".") == 0) continue;
                if (strcmp (inputFile->d_name, "..") == 0) continue;

                inputFileFullPath = (char*)malloc(sizeof(char)*(strlen(inputPath)+strlen(inputFile->d_name)+2));
                sprintf(inputFileFullPath, "%s/%s", inputPath, inputFile->d_name);

                // Ignores subdirectories
                if (IsDirectory(inputFileFullPath))
                {
                    free(inputFileFullPath);
                    continue;
                }

                // Tries adding a node from the current file
                AddNodeFromFile(inputFileFullPath, dataListHead, wordHashTable);
                free(inputFileFullPath);
            }

            closedir(inputFolder);
        }
    }

    else
    {
        MenuAddManyNodesFromFile(inputPath, dataListHead, wordHashTable);
    }

    // Finishes indexing
    indexEndTime = clock();

    printf("%sIndexing completed in %lf seconds!\n", INFO_COLOUR, (double)(indexEndTime-indexStartTime)/(double)CLOCKS_PER_SEC);
}

void AddNodeFromFile(const char* filePath, DataNode** dataListHead, HashTable* wordHashTable)
{
    // Variable declaration
    char* nodeText = NULL;
    int fileLength = 0;
    FILE* dataFile = NULL;
    DataNode* newNode = NULL;

    // Tries opening the file
    printf("%sTrying to open and load from { %s%s%s }...\n", INFO_COLOUR, TEXT_COLOUR, filePath, INFO_COLOUR);
    dataFile = fopen(filePath, "rb");

    // If it's not NULL, reads and loads its data
    if(dataFile != NULL)
    {
        // Gets size of file in bytes
        fseek(dataFile, 0, SEEK_END);
        fileLength = ftell(dataFile);
        fseek(dataFile, 0, SEEK_SET);

        // Mallocs enough memory to store the file text
        nodeText = (char*)malloc(fileLength+sizeof(char));
        fread(nodeText, sizeof(char), fileLength, dataFile);
        nodeText[fileLength] = '\0';
        fclose(dataFile);

        // Creates the data node and inserts it
        newNode = CreateEmptyDataNode();
        SetStringVariable(&(newNode->text), nodeText);
        newNode->nodeID = GetHighestDataNodeID(*dataListHead)+1;
        PushDataNode(dataListHead, newNode);
        free(nodeText);

        // Indexes the data node
        IndexDataNode(newNode, wordHashTable);
    }

    // Otherwise, prints an error
    else
    {
        printf("%sERROR: Could not open file {%s}!\n", ERROR_COLOUR, filePath);
    }
}

void MenuAddManyNodesFromFile(const char* filePath, DataNode** dataListHead, HashTable* wordHashTable)
{
    // Variable declaration
    char readLine[MAX_CMD_INPUT];
    FILE* dataFile = NULL;
    DataNode* newNode = NULL;

    // Tries opening the file
    printf("%sTrying to open and load many nodes from { %s%s%s }...\n", INFO_COLOUR, TEXT_COLOUR, filePath, INFO_COLOUR);
    dataFile = fopen(filePath, "r");

    // If it's not NULL, reads and loads its data
    if(dataFile != NULL)
    {
        // Reads each line
        while(fgets(readLine, MAX_CMD_INPUT, dataFile))
        {
            //printf("reading line. %s", readLine);
            // Removes newline at end
            if(readLine[strlen(readLine)-1] == '\n')
            {
                readLine[strlen(readLine)-1] = '\0';
            }

            // Creates the data node and inserts it
            newNode = CreateEmptyDataNode();
            SetStringVariable(&(newNode->text), readLine);
            newNode->nodeID = GetHighestDataNodeID(*dataListHead)+1;
            PushDataNode(dataListHead, newNode);

            // Indexes the data node
            IndexDataNode(newNode, wordHashTable);
        }

        fclose(dataFile);
    }

    // Otherwise, prints an error
    else
    {
        printf("%sERROR: Could not open file {%s}!\n", ERROR_COLOUR, filePath);
    }
}

void MenuDisplayNodes(DataNode* dataListHead)
{
    // Variable declaration
    int nodesPrinted = 0;
    DataNode* currentNode = dataListHead;
    int nodeCount = GetNumDataNodes(dataListHead);

    // Goes through all nodes and displays them (reverse order by ID b/c not recursive)
    while(currentNode != NULL)
    {
        // Prompts to continue if too many printed
        if(nodesPrinted%MAX_ITEMS_DISPLAYED == 0)
        {
            printf("%sThere are %d nodes left to print.\n", PROMPT_COLOUR, nodeCount-nodesPrinted);
            if(!GetYesNoInput("Continue printing?"))
            {
                break;
            }
        }

        // Displays node
        DisplayNodeData(currentNode);
        printf("\n");
        currentNode = currentNode->next;
        nodesPrinted++;
    }
}

void MenuSearchNodes(HashTable* wordHashTable)
{
    // Variable declaration
    char inputText[MAX_CMD_INPUT];
    AbstractStackNode* retrievedItems = NULL;
    AbstractStackNode* foundIndex = NULL;
    AbstractStackNode* tempStackNode = NULL;
    AbstractStackNode* nodeCopy = NULL;
    AbstractStackNode* intersectionStack = NULL;
    DataNode* displayedDataNode = NULL;
    int numHits = 0;
    char** keywords = NULL;
    int numKeywords = 0;
    clock_t searchStartTime, searchEndTime, displayStartTime, displayEndTime;

    // Gets input from user
    printf("%sEnter your keywords (Max %d chars): %s", PROMPT_COLOUR, MAX_CMD_INPUT, USER_COLOUR);
    fgets(inputText, MAX_CMD_INPUT, stdin);
    fflush(stdin);

    // Removes newline at end if it's present
    if (inputText[strlen(inputText) - 1] == '\n')
    {
        inputText[strlen(inputText) - 1] = '\0';
    }

    // Starts tracking time taken
    searchStartTime = clock();

    // Gets the keywords
    keywords = ExtractItems(inputText, WORD_SEPARATORS, &numKeywords);

    // Finds the search word indices for these keywords
    for(int i = 0; i < numKeywords; i++)
    {
        // Sets keyword to lowercase
        SetStringCase(keywords[i], 0);

        // Tries finding the word index
        foundIndex = RetrieveHashTableItem(wordHashTable, keywords[i]);

        // If it found something, continues to store it. If there are no remaining retrieved items, stops.
        if(foundIndex != NULL || (i != 0 && retrievedItems == NULL))
        {
            //printf("Hash for: %s is %ld\n", keywords[i], HashDJB2(keywords[i])%wordHashTable->size);

            // If this is the first keyword, sets retrievedItems to a copy of these nodes
            if(i == 0)
            {
                tempStackNode = foundIndex;
                while(tempStackNode != NULL)
                {
                    nodeCopy = CreateEmptyStackNode();
                    nodeCopy->itemPointer = tempStackNode->itemPointer;
                    PushStackNode(&retrievedItems, nodeCopy);
                    tempStackNode = tempStackNode->next;
                }
            }

            // Otherwise, sets retrieved items to the intersection of the current retrieved items and the new ones
            else
            {
                intersectionStack = CreateIntersectionStack(retrievedItems, foundIndex);
                ClearAbstractStack(retrievedItems);
                retrievedItems = intersectionStack;
                intersectionStack = NULL;
            } 
        }

        // Otherwise, clears retrievedItems and remaining keywords
        else
        {
            ClearAbstractStack(retrievedItems);
            for(int j = i; j < numKeywords; j++)
            {
                free(keywords[j]);
            }

            retrievedItems = NULL;
            break;
        }

        // Frees the keyword and goes to next
        foundIndex = NULL;
        free(keywords[i]);
    }

    // Frees keywords list
    free(keywords);

    // Updates the lengths cached in retrievedItems
    UpdateNodeCachedLengths(retrievedItems);

    // Notifies user if nothing found
    if(retrievedItems == NULL)
    {
        printf("%sNo items found for query: %s\n", ERROR_COLOUR, inputText);
        return;
    }

    // Stops tracking search time and starts tracking display time
    searchEndTime = clock();
    displayStartTime = clock();
    
    // If there are search word nodes, prints all of them
    tempStackNode = retrievedItems;
    while(tempStackNode != NULL)
    {
        // Doesn't display if too many
        if(numHits < MAX_ITEMS_DISPLAYED)
        {
            // Prints the node
            displayedDataNode = ((DataNode*)(tempStackNode->itemPointer));
            printf("%sMatch found (contains all keywords): ", TITLE_COLOUR);
            printf("%sID %d\n", INFO_COLOUR, (displayedDataNode->nodeID));
            DisplayNodeData(displayedDataNode);
            printf("\n");
        }
        
        // Goes to next node
        tempStackNode = tempStackNode->next;
        numHits++;
    }

    // Displays notification that too many hits to display if necessary
    if(numHits >= MAX_ITEMS_DISPLAYED)
    {
        printf("%s(%d more not displayed.)\n\n",TITLE_COLOUR, (numHits-MAX_ITEMS_DISPLAYED));
    }

    // Frees retrieved items stack
    ClearAbstractStack(retrievedItems);

    displayEndTime = clock();

    // Prints time taken
    printf("%sFound %d hits in %lf seconds!\n", INFO_COLOUR, numHits, ((double)searchEndTime-searchStartTime)/CLOCKS_PER_SEC);
    printf("%sDisplay completed in %lf seconds!\n", INFO_COLOUR, ((double)displayEndTime-displayStartTime)/CLOCKS_PER_SEC);
}

void MenuViewIndexAnalysis(HashTable* wordHashTable, DataNode* dataNodeHead)
{
    // Variable declaration
    AbstractStackNode* currentStackNode = NULL;
    DataNode* currentDataNode = NULL;
    int numSearchIndices = 0;
    int totalNodesInIndices = 0;
    int totalWordLength = 0;
    int totalDataNodes = 0;
    unsigned long numIndicesAllocatedInTable = wordHashTable->size;
    unsigned long totalIndexMemoryUsed = sizeof(*wordHashTable);
    unsigned long totalDataMemoryUsed = 0;
    bool displayAllIndices = false;

    // Prompts user if they want to display all the data
    printf("%sThis program permits viewing the first %d items in the index.\n", PROMPT_COLOUR, MAX_ITEMS_DISPLAYED);
    displayAllIndices = GetYesNoInput("Do you want to display it?");

    // Loops through all index nodes and prints their data
    for(int i = 0; i < wordHashTable->size; i++)
    {
        // Ignores if item at this index is NULL
        if(wordHashTable->valuesArray[i] == NULL)
        {
            continue;
        }

        // Prints data
        if(displayAllIndices && numSearchIndices < MAX_ITEMS_DISPLAYED)
        {
            printf("%sTable Index:  ", TITLE_COLOUR);
            printf("%s%-10d", TEXT_COLOUR, i);
            printf("%sData Nodes: [ ",TITLE_COLOUR);
        }

        // Prints all nodes in this index
        currentStackNode = wordHashTable->valuesArray[i];

        while(currentStackNode != NULL)
        {
            // Prints data
            if(displayAllIndices && numSearchIndices < MAX_ITEMS_DISPLAYED)
            {
                printf("%s%d ", INFO_COLOUR, ((DataNode*)(currentStackNode->itemPointer))->nodeID);
            }

            // Increments some counters
            totalNodesInIndices++;
            totalIndexMemoryUsed += GetStackNodeMemory(currentStackNode);

            // Goes to next item
            currentStackNode = currentStackNode->next;
        }

        // Prints data
        if(displayAllIndices && numSearchIndices < MAX_ITEMS_DISPLAYED)
        {
            printf("%s]\n", TITLE_COLOUR);
        }

        // Increments counters
        numSearchIndices++;
    }

    // Prints that it culled something if it did
    if(displayAllIndices && numSearchIndices > MAX_ITEMS_DISPLAYED)
    {
        printf("%s( %d more indices not displayed)\n", TITLE_COLOUR, numSearchIndices-MAX_ITEMS_DISPLAYED);
    }

    // Calculates data for data list itself
    currentDataNode = dataNodeHead;
    while(currentDataNode != NULL)
    {
        totalWordLength += strlen(currentDataNode->text);
        totalDataNodes++;
        totalDataMemoryUsed += GetDataNodeMemory(currentDataNode);
        currentDataNode = currentDataNode->next;
    }

    // Prints some more diagnostic info
    printf("\n");
    printf("%sIndexed Search Terms: %s%d\n", TITLE_COLOUR, INFO_COLOUR, numSearchIndices);
    printf("%sNumber of Data Nodes: %s%d\n", TITLE_COLOUR, INFO_COLOUR, GetNumDataNodes(dataNodeHead));
    printf("%sAverage Nodes Per Index: %s%0.2lf\n", TITLE_COLOUR, INFO_COLOUR,((float)totalNodesInIndices/(float)numSearchIndices));
    printf("%sAverage Node Length: %s%0.2lf chars\n", TITLE_COLOUR, INFO_COLOUR, ((float)totalWordLength/(float)totalDataNodes));
    printf("%sApprox. memory occupied by data: %s%ld bytes\n", TITLE_COLOUR, INFO_COLOUR, totalDataMemoryUsed);
    printf("%sApprox. memory occupied by indices: %s%ld bytes\n", TITLE_COLOUR, INFO_COLOUR, totalIndexMemoryUsed);
    printf("%sIndex space usage: %s%d indices used / %ld allocated ", TITLE_COLOUR, INFO_COLOUR, numSearchIndices, numIndicesAllocatedInTable);
    printf("%s(%s%0.6lf%%%s)\n", TITLE_COLOUR, INFO_COLOUR, ((float)(numSearchIndices)/(float)(numIndicesAllocatedInTable))*100, TITLE_COLOUR);
    printf("%sNumber of index collisions: %sNope can't calculate that yet sorry.\n", TITLE_COLOUR, INFO_COLOUR);
}

void MenuDisplayEntireNode(DataNode* dataListHead)
{
    // Variable declaration
    char inputText[MAX_CMD_INPUT];
    DataNode* retrievedNode = NULL;
    int requestedID = 0;
    int maxID = GetHighestDataNodeID(dataListHead);

    // Prints error if no IDs in data list
    if(maxID == 0)
    {
        printf("%sThere are no data nodes to print!\n", ERROR_COLOUR);
        return;
    }

    // Asks user for node ID until they enter a valid ID
    while(requestedID < 1 || requestedID > maxID)
    {
        printf("%sEnter the ID of the node (1-%d): %s", PROMPT_COLOUR, maxID, USER_COLOUR);
        fgets(inputText, MAX_CMD_INPUT, stdin);
        fflush(stdin);

        // Removes newline at end if it's present
        if (inputText[strlen(inputText) - 1] == '\n')
        {
            inputText[strlen(inputText) - 1] = '\0';
        }

        // Gets an integer from the input
        requestedID = atoi(inputText);
    }

    // Tries retrieving that node
    retrievedNode = GetDataNodeByID(dataListHead, requestedID);

    // If found, prints its text
    if(retrievedNode != NULL)
    {
        printf("%sFound node with ID %d!\n\n", INFO_COLOUR, requestedID);
        printf("%s--- [START OF TEXT] ---\n", TITLE_COLOUR);
        printf("%s%s\n\n", TEXT_COLOUR, retrievedNode->text );
        printf("%s--- [END OF TEXT] ---\n", TITLE_COLOUR);
    }

    else
    {
        printf("%sCould not find a node with ID %d! Are you sure it exists?\n", ERROR_COLOUR, requestedID);
    }
}

void MenuViewSpecificIndexAnalysis(HashTable* wordHashTable)
{
    //TODO: View analysis of a specific index (eg. listing all its nodes, showing the search term, etc.)
}