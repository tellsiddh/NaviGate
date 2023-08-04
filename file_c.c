#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <direct.h>

#define SIZE 100  // Maximum number of items (files, folders) that can be handled
#define VIEW_SIZE 20  // Maximum number of items that can be displayed at a time

// Function to print menu items
void print_menu(char *items[], int selected, int start, int size) {
    system("cls");  // Clear console
    char cwd[1024];  // Array to hold the current working directory
    _getcwd(cwd, sizeof(cwd));  // Get the current working directory
    printf("Current directory: %s\n", cwd);  // Print the current working directory
    // Loop to print the menu items
    for(int i=start; i < start + VIEW_SIZE && i < size; i++) {
        if(i == selected) {
            printf(">> ");  // Indicator for the currently selected item
        }
        printf("%s\n", items[i]);  // Print the menu item
    }
}

// Function to get the contents of the current directory
void get_directory_contents(char* menu_items[], int* item_count) {
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;

    hFind = FindFirstFile(".\\*", &FindFileData);  // Find the first file in the directory
    if (hFind == INVALID_HANDLE_VALUE) {
        printf ("FindFirstFile failed (%d)\n", GetLastError());  // If the find fails, print an error message
        return;
    }
    else {
        do {
            menu_items[*item_count] = _strdup(FindFileData.cFileName);  // Add the found file to the menu items
            (*item_count)++;  // Increase the item count
            if(*item_count == SIZE-1) {
                break;  // If the maximum number of items is reached, stop the loop
            }
        } while (FindNextFile(hFind, &FindFileData) != 0);  // Find the next file
        FindClose(hFind);  // Close the find handle
    }
    menu_items[*item_count] = _strdup("Quit");  // Add a quit option to the menu items
    (*item_count)++;  // Increase the item count
}

// Main function
int main() {
    char *menu_items[SIZE];  // Array to hold the menu items
    int item_count;  // Variable to hold the number of items
    int selected = 0;  // Variable to hold the currently selected item
    int ch;  // Variable to hold the pressed key
    int start = 0;  // Variable to hold the index of the first item to be displayed

    item_count = 0;  // Initialize the item count
    get_directory_contents(menu_items, &item_count);  // Get the contents of the current directory

    // Main loop
    while(1) {
        print_menu(menu_items, selected, start, item_count);  // Print the menu items

        ch = getch();  // Get the pressed key
        if(ch == 0 || ch == 224) {  // If the pressed key is a special key (like an arrow key)
            switch(getch()) {  // Get the second character of the pressed key
                case 72:  // Up arrow key
                    if(selected > 0) {
                        selected--;  // If the up arrow key is pressed and the selected item is not the first one, move the selection up
                        if(selected < start) {
                            start = selected;  // If the selected item is above the first displayed item, move the first displayed item up
                        }
                    }
                    break;
                case 80:  // Down arrow key
                    if(selected < item_count-1) {
                        selected++;  // If the down arrow key is pressed and the selected item is not the last one, move the selection down
                        if(selected >= start + VIEW_SIZE) {
                            start = selected - VIEW_SIZE + 1;  // If the selected item is below the last displayed item, move the first displayed item down
                        }
                    }
                    break;
                case 75:  // Left arrow key
                    _chdir("..");  // If the left arrow key is pressed, go to the parent directory
                    // Free memory allocated for previous directory contents
                    for(int i=0; i < item_count; i++) {
                        free(menu_items[i]);
                    }
                    item_count = 0;  // Reset the item count
                    get_directory_contents(menu_items, &item_count);  // Get the contents of the new directory
                    selected = 0;  // Reset the selected item
                    start = 0;  // Reset the first displayed item
                    break;
                case 77:  // Right arrow key
                    if(selected < item_count-1) {
                        WIN32_FIND_DATA FindFileData;
                        HANDLE hFind;
                        hFind = FindFirstFile(menu_items[selected], &FindFileData);  // Find the selected file
                        if (hFind == INVALID_HANDLE_VALUE) {
                            printf ("FindFirstFile failed (%d)\n", GetLastError());  // If the find fails, print an error message
                            return 1;
                        } else {
                            if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && _chdir(menu_items[selected]) == 0) {
                                // If the selected file is a directory, go to that directory
                                // Free memory allocated for previous directory contents
                                for(int i=0; i < item_count; i++) {
                                    free(menu_items[i]);
                                }
                                item_count = 0;  // Reset the item count
                                get_directory_contents(menu_items, &item_count);  // Get the contents of the new directory
                                selected = 0;  // Reset the selected item
                                start = 0;  // Reset the first displayed item
                            } else {
                                // If the selected file is a file, display its content
                                char command[1024];
                                sprintf(command, "type \"%s\"", menu_items[selected]);  // Prepare a command to display the file content
                                system(command);  // Execute the command
                                printf("\nPress any key to continue...");  // Wait for the user to press a key
                                getch();  // Get the pressed key
                            }
                            FindClose(hFind);  // Close the find handle
                        }
                    }
                    break;
            } 
        }
        else if (ch == 'q' || ch == 'Q') {  // If 'q' or 'Q' is pressed
            break;  // Exit the main loop
        } else if(ch == 13) {  // If the enter key is pressed
            if(selected == item_count-1) {  // If the selected item is the quit option
                break;  // Exit the main loop
            }
            printf("You selected %s\n", menu_items[selected]);  // Print the selected item
            system("pause");  // Wait for the user to press a key
        }
    }

    // Free memory allocated for menu items
    for(int i=0; i < item_count; i++) {
        free(menu_items[i]);
    }

    return 0;  // End of the program
}
