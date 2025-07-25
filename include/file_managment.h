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


FILE* open_handle(char* path,char mode);


void close_handle(FILE* file);

long get_size(FILE* file);

char* read_file(int row,char* file_cont,char* MODE,int acc_size);

int get_file_rows(FILE* file);

void replace_word(int x,int y,int row,char c,char* file_cont,FILE* handel);

char* get_file_cont(FILE* file);

int get_pos(char* file_cont,int row,int x,int y);