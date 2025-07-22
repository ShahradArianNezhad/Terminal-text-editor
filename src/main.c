#include "../include/terminal.h"
#include "../include/file_managment.h"

#include <unistd.h>
#include <stdio.h>



int handle_args(int argc,char* argv[]){
    if (argv[1]==NULL){
    printf("no file path declared\n");
    return 1;
  }
  return 0;
}




int main(int argc,char* argv[]){

  if (handle_args(argc,argv)){
    return 1;
  }

  int curr_row=1;


  enable_raw_mode();
  FILE* file= open_handle(argv[1]);
  char* cont = get_file_cont(file);
  int file_rows = get_file_rows(file);
  read_file(curr_row,cont,"VIEW");


  int x=0,y=0;
  printf("\033[%d;%dH",y,x);
  fflush(stdout);

  char c;

  while (read(STDIN_FILENO,&c,1)==1 && c !='q'){


    // REPLACE MODE
    if(c=='r'){
      read_file(curr_row,cont,"REPLACE");
      printf("\033[%d;%dH",y+1,x+1);
      fflush(stdout);
      read(STDIN_FILENO,&c,1);
      while(c=='\033'){
        read(STDIN_FILENO,&c,1);
        read(STDIN_FILENO,&c,1);
        handle_arrow_keys(&x,&y,&curr_row,cont,c,file_rows);
        read(STDIN_FILENO,&c,1);
      }
      replace_word(x,y,curr_row,c,cont);
    }


    // VIEW MODE
    if(c=='\033'){

      read(STDIN_FILENO,&c,1);
      read(STDIN_FILENO,&c,1);
      handle_arrow_keys(&x,&y,&curr_row,cont,c,file_rows);
    }
  }
  close_handle(file);















  disable_raw_mode();
  printf("\033[99999999999;1H");


  





  return 0;

}