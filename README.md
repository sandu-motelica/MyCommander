# My Commander

**My Commander** is a graphical file manager built with **SFML** and **C++**, designed for efficient file and directory navigation.

## Features

- Browse directories and files with ease
- View and sort files by **name** or **extension**
- Copy, move, rename, and delete files/folders
- Intuitive graphical interface
- Support for multiple file types with dedicated icons

## System Requirements

- **Operating System:** Windows (tested on Windows 10 and 11)
- **Required Libraries:**  
  - [SFML](https://www.sfml-dev.org/) (Simple and Fast Multimedia Library)
  - C++ 11 or later
- **Recommended Compiler:** MinGW/GCC or Visual Studio

## Installation and Running

### 1. Install SFML
Download and install **SFML** from the [official website](https://www.sfml-dev.org/download.php).

### 2. Clone and Compile the Project

```sh
git clone https://github.com/your-username/MyCommander.git
cd MyCommander
g++ main.cpp -o MyCommander.exe -lsfml-graphics -lsfml-window -lsfml-system
```

### 3. Run the Application

After compiling, execute the program:

```sh
./MyCommander.exe
```

## Project Structure

- `main.cpp` - The entry point of the application
- `button.h` - Handles interface buttons
- `filebutton.h` - Manages file-related buttons
- `filearbore.h` - Handles the file/directory tree
- `folders.h` - Structures and functions for directory management
- `textbox.h` - Handles text input fields in the interface
- `textbutton.h` - Manages text-based buttons in the interface
- `Segoe UI.ttf` - The font used in the UI

## Functionality

- **Directory Navigation:** Easily explore files and directories on your system.
- **Sorting:** Sort by **name** or **extension**.
- **File Operations:** Copy and move files between directories.
- **Renaming:** Rename files and folders directly from the interface.
- **Deletion:** Delete files and directories with confirmation.
- **File Viewing:** Open multimedia, text, or archive files.

## Contributing
Since this project is for educational purposes, contributions are welcome, especially in the form of code improvements, bug fixes, or additional learning resources. Feel free to fork the repository and submit a pull request with your enhancements.

## License

This project is licensed under the **MIT License**.

