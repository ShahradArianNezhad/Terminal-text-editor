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
#include <string.h>


FILE* open_handle(char* path,char mode){
    FILE* file;
    if(mode=='r'){
        file = fopen(path,"r+");
    }else{
        file = fopen(path,"w+");
    }

    if(file==NULL){
        perror("File not found/ error opening file");
        exit(EXIT_FAILURE);
    }
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

char* get_file_cont(FILE* file){
    long size = get_size(file)+1;
    char* buffer = malloc(size);
    fread(buffer,1,size,file);
    buffer[size]='\0';
    return buffer;
}

void read_file(int row,char* file_cont,char* MODE){

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif



    int term_row = get_row()-2;
    

    int row_count=1;
    int word_count=0;
    int i=0;
    int printed_rows=0;
    char* buffer = file_cont;


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
    
    printf("%s press Q to exit\n",MODE);
    


}


int get_pos(char* file_cont,int row,int x,int y){
    int curr_row = 1;
    int word_count=0;
    int i=0;


    char* buffer= file_cont;
    
    while(curr_row<(row+y)){
        if(buffer[i]=='\n'){
            word_count=0;
            curr_row++;
            i++;
        }else{
            if(word_count==get_col()){
                word_count=0;
                curr_row++;
            }else{
                word_count++;
                i++;
            }
        }
    }
    return i+x;
}


void replace_word(int x,int y,int row,char c,char* file_cont){

    int i= get_pos(file_cont,row,x,y);


    char* buffer= file_cont;
    
   
    
    // if(buffer[i]=='\n'){
    //     char* temp = realloc(file_cont,strlen(file_cont));
    //     buffer = temp;
    //     buffer[i+1]='\n';
    // }


    buffer[i]=c;
    read_file(row,buffer,"VIEW");
    printf("\033[%d;%dH",y+1,x+1);
    fflush(stdout);





}



