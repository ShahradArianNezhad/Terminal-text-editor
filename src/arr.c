#include <string.h>
#include "file_managment.h"
#include <stdio.h>

char* append_to_array(char* arr,char c,int pos,long init_size){
    static int appended=0;
    static long size;
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