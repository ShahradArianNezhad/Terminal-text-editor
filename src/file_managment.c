#ifdef _WIN32
    #define fseek _fseeki64
    #define ftell _ftelli64
#else
    #define fseek fseeko
    #define ftell ftello
#endif

#include <stdio.h>
#include "../include/terminal.h"
#include <stdlib.h>


FILE* open_handle(char* path){
    FILE *file = fopen(path,"a+");
    return file;
}


void close_handle(FILE* file){
    fclose(file);
}

int get_file_rows(FILE* file){
    int i =0;
    char buffer[256];
    while(fgets(buffer,sizeof(buffer),file)!=NULL){
        i++;
    }
    return i;
}


long get_size(FILE* file){
    fseek(file,0,SEEK_END);
    long file_size = ftell(file);
    fseek(file,0,SEEK_SET);
    return file_size;
}

void read_file(FILE* file,int row){
    system("clear");
    int term_row = get_row()-1;
    long size = get_size(file)+1;
    char* buffer = malloc(size);
    fread(buffer,1,size,file);
    buffer[size]='\0';

    int row_count=1;
    int word_count=0;
    int i=0;
    int printed_rows=0;


    while(term_row>=printed_rows){

        if (buffer[i]=='\n'){

            if(row_count>=row){
                printf("%c",buffer[i]);
                printed_rows++;
            }
            row_count++;
            word_count=0;
            i++;
            continue;
        }else{
            if(word_count==get_col()){

                if(row_count>=row){
                    printf("%c",buffer[i]);
                    printed_rows++;
                }
                word_count=0;
                row_count++;
                i++;
                continue;
            }
            if(row_count>=row){
                printf("%c",buffer[i]);
            }
            word_count++;
            i++;
            continue;
        }

    }
    printf("\n");
    printf("use arrow keys to navigate, press 'q' to quit\n");
    


}
