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

