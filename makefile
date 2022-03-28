FLAGS = -std=c99 -Wall
CC = gcc
OUTPUT = SearchAlgorithm.exe
HEADERS=include/menuFunctions.h include/abstractStack.h include/searchProgram.h include/libs.h include/abstractHashTable.h
OBJECTS = main.o menuFunctions.o utility.o data.o abstractStack.o wordIndex.o abstractHashTable.o
ifeq ($(OS),Windows_NT)
	DEL_FUNC = del
else
	DEL_FUNC = rm
endif


$(OUTPUT): $(OBJECTS) $(HEADERS)
	$(CC) $(FLAGS) $(OBJECTS) -g -o $(OUTPUT)

$(OBJECTS): %.o: src/%.c $(HEADERS)
	$(CC) -c $(FLAGS) -g $< -o $@

.PHONY: clean test

test:
	echo "This isn't done yet!"

clean:
	$(DEL_FUNC) *.o *.exe
