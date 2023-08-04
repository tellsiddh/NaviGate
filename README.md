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

- Navigate directories using arrow keys.
- Open directories and view file contents directly from the console.
- Simple, lightweight, and quick to use.


## System Requirements and Platform Dependencies

NaviGate is a lightweight console application that doesn't require a high-performing system. However, there are some basic system requirements and platform dependencies you should be aware of before installing.

### System Requirements

Windows 7 or later.

At least 2GB of RAM.

At least 100MB of free disk space.

A processor supporting SSE2 (Pentium 4 or newer).

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


gcc main.c -o NaviGate

Now you can start the program:

./NaviGate

Use the arrow keys to navigate through directories and files, press Enter to open a directory or view a file, and press q or Q to quit the program.

## Contribution
Contributions are welcome! Please read the contribution guidelines first.

## License
This project is licensed under the MIT License. See the LICENSE file for details.