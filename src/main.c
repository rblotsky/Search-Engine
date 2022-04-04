// Includes //
#include "../include/menuFunctions.h"

// Main Function //
int main()
{
    // Variable declaration
    char selectedOption = '0';
    char userInput[MAX_CMD_INPUT] = "\0";
    HashTable* wordHashTable = NULL;
    DataNode* dataNodesHead = NULL;
    int maxIndexSize = 0;
    //AbstractStackNode* allSearchTerms = NULL;

    // Prompts user to enter the max index size
    printf("%s## Program Initialization ##\n", TITLE_COLOUR);
    printf("%sPlease enter a desired maximum index size. The program will function fine with\n", INFO_COLOUR);
    printf("%sany size, however more query collisions will occur when the maximum size is smaller\n", INFO_COLOUR);
    printf("%sthan the number of search terms being indexed.\n", INFO_COLOUR);
    while(maxIndexSize <= 0 || maxIndexSize > ULTIMATE_MAX_INDEX_SIZE)
    {
        printf("%sEnter a size (Integer greater than 0): %s", PROMPT_COLOUR, USER_COLOUR);
        fgets(userInput, MAX_CMD_INPUT, stdin);
        fflush(stdin);
        maxIndexSize = atoi(userInput);
    }
    
    // Generates a hash table with given max size
    wordHashTable = InitializeHashTable(maxIndexSize);

    // Runs main menu
    while (selectedOption != '8')
    {
        // Empties input initially
        strcpy(userInput, "\0");
        selectedOption = '0';

        // Displays menu
        printf("%s\n---- [Welcome to Roman's Search Algorithm] ----\n\n", TITLE_COLOUR);
        printf("%sPlease select a menu option:\n", TEXT_COLOUR);
        printf("\t1: Index a new node (via text input)\n");
        printf("\t2: Index a new node (from a file)\n");
        printf("\t3: View all nodes\n");
        printf("\t4: Search by keywords\n");
        printf("\t5: View index analysis\n");
        printf("\t6: View a node by ID\n");
        printf("\t7: View breakdown of a specific index\n");
        printf("\t8: Exit Program\n");
        printf("%sEnter a number (1-8):%s ", PROMPT_COLOUR, USER_COLOUR);

        // Gets input (reads via scanf, then clears buffer if failed reading)
        fgets(userInput, MAX_CMD_INPUT, stdin);
        selectedOption = userInput[0];
        fflush(stdin);

        // Runs options depending on the entered value
        switch (selectedOption)
        {
            case '1':
                printf("%s\n## Creating a new node from text input ##\n", TITLE_COLOUR);
                MenuAddNodeWithText(&dataNodesHead, wordHashTable);
                break;
            case '2':
                printf("%s\n## Creating a new node from file ##\n", TITLE_COLOUR);
                MenuAddNodeFromFile(&dataNodesHead, wordHashTable);
                break;
            case '3':
                printf("%s\n## Listing all nodes ##\n", TITLE_COLOUR);
                MenuDisplayNodes(dataNodesHead);
                break;
            case '4':
                printf("%s\n## Searching for nodes by keywords ##\n", TITLE_COLOUR);
                MenuSearchNodes(wordHashTable);
                break;
            case '5':
                printf("%s\n## Viewing index analysis ##\n", TITLE_COLOUR);
                MenuViewIndexAnalysis(wordHashTable, dataNodesHead);
                break;
            case '6':
                printf("%s\n## Displaying a node by ID ##\n", TITLE_COLOUR);
                MenuDisplayEntireNode(dataNodesHead);
                break;
            case '7':
                printf("%s\n## Viewing a specific search index ##\n", TITLE_COLOUR);
                MenuViewSpecificIndexAnalysis(wordHashTable);
                break;
            case '8':
                printf("%sExiting...\n", INFO_COLOUR);
                break;
            default:
                printf("%sInvalid input!\n", ERROR_COLOUR);
        }
    }

    // Returns 0 on successful run
    printf("Finished!\n%s", DEFAULT_COLOUR);
    return 0;
}