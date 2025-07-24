# Terminal Text Reader

A extremely lightweight, keyboard-controlled text editor for the terminal with navigation support.

## Features

- very small application size of 20kb
- low memory usage of only a few megabytes;
- Edit text files with clean pagination
- Keyboard navigation (arrow keys)
- Adjusts to terminal window size
- Cross-platform file handling (Windows/Linux)
- Raw terminal mode for responsive input
- File size and row counting

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/ShahradArianNezhad/terminal-text-editor.git
   cd terminal-text-editor
   ```
2. Compile with make:  
    ```bash
    make
    ```

## Usage
-
    ```bash
    ./bin/hydro path/to/your/file.txt
    ```

### Navigation controls
- UP/DOWN arrow keys: scroll through file
- LEFT/RIGHT arrow keys: move cursor horizontally
- W: write to file
- A: append mode
- R: replace mode
- ESC: leave append mode
- q: Quit the application


## Requirements
- C compiler
- standard C library
- Unix-like system or Windows with POSIX compatibility

## File structure
```
text-reader/
├── bin
│   └── hydro               #The application
├── include
│   ├── arr.h
│   ├── file_managment.h    #included header files
│   └── terminal.h
├── src                     #source files
│   ├── arr.c
│   ├── file_managment.c
│   ├── main.c
│   └── terminal.c
├── tests                   #demo txt files for testing
│   ├── myfile.txt
│   └── test.txt
├── LICENSE                 #MIT license
├── Makefile                #included makefile for easy compilation
└── readme.md               #Readme


```

## License
MIT License - Free for personal and commercial use