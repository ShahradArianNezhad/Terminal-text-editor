#pragma once

void enable_raw_mode();

void disable_raw_mode();

int get_col();

int get_row();

void handle_arrow_keys(int* x,int* y,int* curr_row,char* cont,char c,int file_rows);