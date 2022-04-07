# Search-Engine
A simple search engine in C that allows adding "data nodes" and searching within them.

# Purpose
This program's purpose is simply to be an exercise in writing more complex C programs as well as data management and search methods.

# Program Functionality
- Indexing and Searching (via Hash table):
  * Each record is split into individual words, and a reference to the record is placed in the hash table under each one of those words.
  * When searching, the program takes each keyword, finds the list of records for each, and returns a list of records that appear under each of the keywords.
- Hash Table Functionality:
  * The hash table is custom-written rather than using a standard library. This is inefficient but I did it to learn how hash tables are constructed.
  * The hash function used is djb2 (retrieved from [York University](http://www.cse.yorku.ca/~oz/hash.html).
  * Hash collisions are not handled at all: if two terms have the same hash, the table will return the same index. (In this use case, this results in some extra "garbage" results potentially being given alongside correct search results)
 
