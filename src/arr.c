#include <string.h>
#include "file_managment.h"
#include <stdio.h>

static int appended=0;
static long size;

char* append_to_array(char* arr,char c,int pos,long init_size){
    
    int CHUNK = 256;
    char* newarr=arr;

    if(appended==0){
        size = init_size;
    }
    if((appended+init_size)>=size){
        newarr = realloc(arr,size+CHUNK);
        size = size+256;
    }

    for(int i=(appended+init_size-1);pos<=(i);i--){
        newarr[i+1]=newarr[i];
    }
    newarr[pos]=c;
    appended++;
    return newarr;


}


char* delete_from_array(char* arr,int pos,long init_size){
    char* newarr = arr;

    for(int i=(pos-1);i<(init_size+appended);i++){
        newarr[i]=newarr[i+1];
    }
    appended--;
    return newarr;
}