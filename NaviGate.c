#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <direct.h>
#include <string.h>
#include <shellapi.h>


#define SIZE 100
#define VIEW_SIZE 20

int viewing_file = 0; // Add this at the start of your main function
char current_file[1024]; // keep track of the current file being viewed

void print_menu(char *items[], int selected, int start, int size) {
    system("cls");  // Clear console
    char cwd[1024];
    _getcwd(cwd, sizeof(cwd));
    printf("Current directory: %s\n", cwd);
    for(int i=start; i < start + VIEW_SIZE && i < size; i++) {
        if(i == selected) {
            printf(">> ");  // Indicator for the currently selected item
        }

        // Check if the current item is a directory or a file
        WIN32_FIND_DATA FindFileData;
        HANDLE hFind;
        hFind = FindFirstFile(items[i], &FindFileData);
        if (hFind != INVALID_HANDLE_VALUE) {
            LARGE_INTEGER fileSize;
            fileSize.LowPart = FindFileData.nFileSizeLow;
            fileSize.HighPart = FindFileData.nFileSizeHigh;
            if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                printf("[DIR]	%s\n", items[i]);
            } else {
                printf("[FILE]	%s	%15lld bytes\n", items[i], fileSize.QuadPart);
            }
            FindClose(hFind);
        } else {
            printf("[FILE]	%s\n", items[i]); // In case FindFirstFile fails, just print the item.
        }
    }
}



void print_file(char *filename, int start_line) {
    system("cls");  // Clear console

    char line[1024];
    FILE *file = fopen(filename, "r");
    if(file == NULL) {
        printf("Error opening file %s\n", filename);
        system("pause");
        viewing_file = 0;
        return;
    }

    int line_no = 0;
    while(fgets(line, sizeof(line), file)) {
        line_no++;
        if(line_no < start_line) {
            continue;
        }
        if(line_no >= start_line + VIEW_SIZE) {
            break;
        }
        printf("%s", line);
    }
    fclose(file);
}

void get_directory_contents(char* menu_items[], int* item_count) {
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;

    hFind = FindFirstFile(".\\*", &FindFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf ("FindFirstFile failed (%d)\n", GetLastError());
        return;
    }
    else {
        do {
            menu_items[*item_count] = _strdup(FindFileData.cFileName);
            (*item_count)++;
            if(*item_count == SIZE-1) {
                break;
            }
        } while (FindNextFile(hFind, &FindFileData) != 0);
        FindClose(hFind);
    }
    menu_items[*item_count] = _strdup("Quit");
    (*item_count)++;
}

int search_in_current_directory(char* menu_items[], int* item_count, char* target) {
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;

    hFind = FindFirstFile(".\\*", &FindFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf ("FindFirstFile failed (%d)\n", GetLastError());
        return -1;
    }
    else {
        int i = 0;
        do {
            if(_stricmp(FindFileData.cFileName, target) == 0) {
                printf("Found: %s\n", FindFileData.cFileName);
                printf("Press Enter to select this file, or Esc to continue search\n");
                int ch = getch();
                if(ch == 13) {  // Enter key
                    FindClose(hFind);
                    return i;
                } else if(ch == 27) {  // Esc key
                    FindClose(hFind);
                    return -1;
                }
            }
            i++;
        } while (FindNextFile(hFind, &FindFileData) != 0);
        FindClose(hFind);
    }
    return -1;
}

int main() {
    char *menu_items[SIZE];
    int item_count;
    int selected = 0;
    int ch;
    int start = 0;
    int file_line_start = 0;

    item_count = 0;
    get_directory_contents(menu_items, &item_count);

    while(1) {
        if(viewing_file) {
            print_file(current_file, file_line_start);
        } else {
            print_menu(menu_items, selected, start, item_count);
        }

        ch = getch();
        if(ch == 0 || ch == 224) {
            switch(getch()) {
                case 72:  // Up arrow key
                    if(viewing_file) {
                        if(file_line_start > 0) {
                            file_line_start--;
                        }
                    } else {
                        if(selected > 0) {
                            selected--;
                            if(selected < start) {
                                start = selected;
                            }
                        }
                    }
                    break;
                case 80:  // Down arrow key
                    if(viewing_file) {
                        file_line_start++;
                    } else {
                        if(selected < item_count-1) {
                            selected++;
                            if(selected >= start + VIEW_SIZE) {
                                start = selected - VIEW_SIZE + 1;
                            }
                        }
                    }
                    break;
                case 75:  // Left arrow key
                    if(viewing_file) {
                        viewing_file = 0;
                    } else {
                        _chdir("..");
                        // Free memory allocated for previous directory contents
                        for(int i=0; i < item_count; i++) {
                            free(menu_items[i]);
                        }
                        item_count = 0;
                        get_directory_contents(menu_items, &item_count);
                        selected = 0;
                        start = 0;
                    }
                    break;
                case 77:  // Right arrow key
                    if(!viewing_file && selected < item_count-1) {
                        WIN32_FIND_DATA FindFileData;
                        HANDLE hFind;
                        hFind = FindFirstFile(menu_items[selected], &FindFileData);
                        if (hFind == INVALID_HANDLE_VALUE) {
                            printf ("FindFirstFile failed (%d)\n", GetLastError());
                            return 1;
                        } else {
                            if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && _chdir(menu_items[selected]) == 0) {
                                // Free memory allocated for previous directory contents
                                for(int i=0; i < item_count; i++) {
                                    free(menu_items[i]);
                                }
                                item_count = 0;
                                get_directory_contents(menu_items, &item_count);
                                selected = 0;
                                start = 0;
                            } else {
                                strcpy(current_file, menu_items[selected]);
                                viewing_file = 1;
                                file_line_start = 0;
                            }
                            FindClose(hFind);
                        }
                    }
                    break;
            }
} else if(ch == 'q' || ch == 'Q') {  // Q key
            if(viewing_file) {
                viewing_file = 0;
            } else {
                break;
            }
        } else if(ch == 's' || ch == 'S') {  // S key
            if(!viewing_file) {
                char search_target[1024];
                printf("Enter search term: ");
                scanf("%s", search_target);
                int result = search_in_current_directory(menu_items, &item_count, search_target);
                if(result != -1) {
                    selected = result;
                    if(selected >= start + VIEW_SIZE) {
                        start = selected - VIEW_SIZE + 1;
                    }
                }
                system("pause");
            }
        } else if(ch == 13) {  // Enter key
    if(!viewing_file && selected == item_count-1) {  // "Quit" option
        break;
    }
    if (!viewing_file) { // if we are not viewing a file, try to open it
        ShellExecute(NULL, "open", menu_items[selected], NULL, NULL, SW_SHOW);
    }
    printf("You selected %s\n", menu_items[selected]);
    system("pause");
}
    }

    // Free memory allocated for menu items
    for(int i=0; i < item_count; i++) {
        free(menu_items[i]);
    }

    return 0;
}
