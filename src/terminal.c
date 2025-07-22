#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "../include/file_managment.h"

static struct termios original;

void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &original);
    struct termios raw=original;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode(){
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
}


int get_col(){
    struct winsize w;
    ioctl(STDOUT_FILENO,TIOCGWINSZ,&w);
    return w.ws_col;
}

int get_row(){
    struct winsize w;
    ioctl(STDOUT_FILENO,TIOCGWINSZ,&w);
    return w.ws_row-2;
}



void handle_arrow_keys(int* x,int* y,int* curr_row,char* cont,char c,int file_rows){
    if(c=='A'){
        if(*y==0){
          if((*curr_row)!=1){
            (*curr_row)--;
            read_file(*curr_row,cont,"VIEW");
          }

        }else{
          (*y)--;
        }
      }else if(c=='B'){
        if((*y)==get_row()-1){
          if(((*curr_row)+get_row()-1) != file_rows){
            (*curr_row)++;
            read_file(*curr_row,cont,"VIEW");
          }
        }else{
        (*y)++;
        }
      }else if(c=='C'){
        (*x)++;
      }else if(c=='D'){
        (*x)--;
      }
      printf("\033[%d;%dH",(*y)+1,(*x)+1);
      fflush(stdout);
}