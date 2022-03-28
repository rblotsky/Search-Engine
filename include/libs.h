// (Only performs if it hasn't been already imported)//
#ifndef MAIN_LIBS_INCLUDED
    // Includes all libraries
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>
    #include <stdbool.h>
    #include <math.h>
    #include <time.h>
    #include <sys/stat.h>
    #if defined(_WIN64)
        #include <io.h>
    #endif
    #include <dirent.h>
    #include "../include/colours.h"
    #define MAIN_LIBS_INCLUDED 1
#endif