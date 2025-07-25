#include "../include/terminal.h"
#include "../include/file_managment.h"
#include "../include/arr.h"

#include <unistd.h>
#include <stdio.h>



int handle_args(int argc,char* argv[]){

  if(argc!=2){
    printf("too many/few arguments supplied");
    return 1;
  }


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
  FILE* file= open_handle(argv[1],'r');
  char* cont = get_file_cont(file);
  int file_rows = get_file_rows(file);
  read_file(curr_row,cont,"VIEW MODE",get_curr_size(get_size(file)));


  int x=0,y=0;
  printf("\033[%d;%dH",y,x);
  fflush(stdout);

  char c;

  while (read(STDIN_FILENO,&c,1)==1 && c !='q'){

    
    // REPLACE MODE
    if(c=='r'){
      read_file(curr_row,cont,"REPLACE MODE",get_curr_size(get_size(file)));
      printf("\033[4 q");
      printf("\033[%d;%dH",y+1,x+1);
      fflush(stdout);
      read(STDIN_FILENO,&c,1);
      while(c=='\033'){
        read(STDIN_FILENO,&c,1);
        read(STDIN_FILENO,&c,1);
        handle_arrow_keys(&x,&y,&curr_row,cont,c,file_rows,file);
        read(STDIN_FILENO,&c,1);
      }
        replace_word(x,y,curr_row,c,cont,file);
        printf("\033[2 q");
        printf("\033[%d;%dH",y+1,x+1);
        fflush(stdout);
    }


    // VIEW MODE
    else if(c=='\033'){

      read(STDIN_FILENO,&c,1);
      read(STDIN_FILENO,&c,1);
      handle_arrow_keys(&x,&y,&curr_row,cont,c,file_rows,file);
    }


    else if(c=='a'){
      read_file(curr_row,cont,"APPEND MODE",get_curr_size(get_size(file)));
      printf("\033[6 q");
      printf("\033[%d;%dH",y+1,x+1);
      fflush(stdout);

      read(STDIN_FILENO,&c,1);
      while(1){
        if(c=='\033'){
          
          if(read(STDIN_FILENO, &c, 1) == 1){
            if(c == '['){
              if(read(STDIN_FILENO, &c, 1) == 1){
                
                  handle_arrow_keys(&x,&y,&curr_row,cont,c,file_rows,file);
                  read(STDIN_FILENO, &c, 1);
                  continue;
                }  
            }
          }
          read_file(curr_row,cont,"VIEW MODE",get_curr_size(get_size(file)));
          printf("\033[2 q"); 
          printf("\033[%d;%dH",y+1,x+1);
          fflush(stdout);
          
          break;
        }else if(c=='\b' || c==127){
          if(x==0){
            read(STDIN_FILENO,&c,1);
            continue;
          }
          cont = delete_from_array(cont,get_pos(cont,curr_row,x,y),get_size(file));
          
          x--;
          read_file(curr_row,cont,"APPEND MODE",get_curr_size(get_size(file)));
          printf("\033[%d;%dH",y+1,x+1);
          fflush(stdout);

        }else{
          cont = append_to_array(cont,c,get_pos(cont,curr_row,x,y),get_size(file));
          if(c=='\n'){
            x=0;
            y++;
          }else{
            x++;
          }
          read_file(curr_row,cont,"APPEND MODE",get_curr_size(get_size(file)));
          
          printf("\033[%d;%dH",y+1,x+1);
          fflush(stdout);
        }
        read(STDIN_FILENO,&c,1);
        
      }
      
      
    }

    else if(c=='w'){
      close_handle(file);
      file=open_handle(argv[1],'w');
      close_handle(file);
      file= open_handle(argv[1],'r');
      fprintf(file,cont);
      read_file(curr_row,cont,"WROTE TO FILE",get_curr_size(get_size(file)));
      printf("\033[%d;%dH",y+1,x+1);
      fflush(stdout);
    }


  }
  close_handle(file);















  disable_raw_mode();
  printf("\033[99999999999;1H");


  





  return 0;

}