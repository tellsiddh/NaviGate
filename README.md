# NaviGate

_NaviGate is a simple and user-friendly console application for navigating directories and files on a Windows system._

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [System Requirements and Platform Dependencies](#system-requirements-and-platform-dependencies)
- [Installation](#installation)
- [Usage](#usage)
- [Contribution](#contribution)
- [License](#license)

## Introduction

NaviGate is a console application that allows you to navigate through directories in your Windows system using arrow keys and displays the content of the selected file. It's developed in C and provides a handy way to explore and manage files from a command-line interface.

## Features

- Intuitive directory navigation using arrow keys.
- Preview file content within the console.
- Locate specific files or directories with an inbuilt search function.
- Launch files using their associated Windows application.
- User-centric design, prioritizing simplicity and speed.


## System Requirements and Platform Dependencies

### System Requirements

- Operating System: Windows 7 or higher.

- Memory: Minimum 2GB RAM.

- Disk Space: At least 100MB available.

- Processor: A CPU with SSE2 support (e.g., Pentium 4 or newer).

### Platform Dependencies

NaviGate is developed and tested on a Windows-based system. It is designed to work with Windows 7 and later.

You will need GCC (GNU Compiler Collection) installed in your system to compile the source code. It is available for free download and installation here https://gcc.gnu.org/install/index.html.

NaviGate relies on standard C libraries for its operation. Ensure your system supports the execution of C programs.

Git should be installed in your system to clone the repository. If not already installed, you can download it from the official Git website https://git-scm.com/downloads.

Remember, NaviGate is a console-based application, it doesn't provide a Graphical User Interface (GUI). It is intended for users who are comfortable using a command-line interface.

## Installation

Clone this repository to your local machine to get started.


git clone https://github.com/tellsiddh/NaviGate.git

cd NaviGate

Usage

After cloning the repository, navigate to the repository folder and compile the source code:


gcc NaviGate.c -o NaviGate

Now you can start the program:

NaviGate.exe

Use the arrow keys to navigate through directories and files, press Enter to open a directory or view a file, press 's' or 'S' to search for files or directories, and press 'q' or 'Q' to quit the program.

When a file is selected, press 'ENTER' to open it with its default Windows application or Right Arrow Key to open it in the terminal. If a search is initiated, type the name of the file or directory and press Enter, the cursor will navigate to the searched item if found, or you can exit search by pressing ESC.

## Contribution
Contributions are welcome! Please read the contribution guidelines first.

## License
This project is licensed under the MIT License. See the LICENSE file for details.