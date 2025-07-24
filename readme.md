# Terminal Text Reader

A lightweight, keyboard-controlled text editor for the terminal with navigation support.

## Features

- View text files with clean pagination
- Keyboard navigation (arrow keys)
- Adjusts to terminal window size
- Cross-platform file handling (Windows/Linux)
- Raw terminal mode for responsive input
- File size and row counting

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/ShahradArianNezhad/terminal-text-reader.git
   cd terminal-text-reader
   ```
2. Compile with make:  
    ```bash
    make
    ```

## Usage
-
    ```bash
    ./bin/textreader path/to/your/file.txt
    ```

### Navigation controls
- UP/DOWN arrow keys: scroll through file
- LEFT/RIGHT arrow keys: move cursor horizontally
- q: Quit the application


## Requirements
- C compiler
- standard C library
- Unix-like system or Windows with POSIX compatibility

## File structure
```
text-reader/
├── include/        # Header files
│   ├── terminal.h
│   └── file_managment.h
├── src/            # Source code
│   └── terminal.c
├── Makefile        # Build configuration
└── README.md       # This file
```

## License
MIT License - Free for personal and commercial use