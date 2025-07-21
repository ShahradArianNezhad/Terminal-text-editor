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

  int file_rows = get_file_rows(file);
  read_file(file,curr_row);



  int x=0,y=0;
  printf("\033[%d;%dH",y,x);
  fflush(stdout);

  char c;

  while (read(STDIN_FILENO,&c,1)==1 && c !='q'){
    if(c=='\033'){

      read(STDIN_FILENO,&c,1);
      read(STDIN_FILENO,&c,1);
      if(c=='A'){
        if(y==0){
          if(curr_row!=1){
            curr_row--;
            read_file(file,curr_row);
          }

        }else{
          y--;
        }
      }else if(c=='B'){
        if(y==get_row()-1){
          if((curr_row+get_row()-1) != file_rows){
            curr_row++;
            read_file(file,curr_row);
          }
        }else{
        y++;
        }
      }else if(c=='C'){
        x++;
      }else if(c=='D'){
        x--;
      }
      printf("\033[%d;%dH",y+1,x+1);
      fflush(stdout);

    }
  }
  close_handle(file);

















  disable_raw_mode();
  printf("\033[99999999999;1H");


  





  return 0;

}