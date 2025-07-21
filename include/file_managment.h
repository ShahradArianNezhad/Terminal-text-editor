#ifdef _WIN32
    #define fseek _fseeki64
    #define ftell _ftelli64
#else
    #define fseek fseeko
    #define ftell ftello
#endif

#include <stdio.h>
#include <stdlib.h>
#pragma once


FILE* open_handle(char* path);


void close_handle(FILE* file);

long get_size(FILE* file);

char* read_file(FILE* file,int row);

int get_file_rows(FILE* file);