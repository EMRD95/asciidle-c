#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>
#include <stdbool.h>

void display_ascii_art(const char *filename, int *row);
void random_ascii_art(const char *folder, char *filename, size_t len);

int main() {
    char ascii_art_folder[256];
    strcpy(ascii_art_folder, getenv("HOME"));
    strcat(ascii_art_folder, "/asciidle-c/txt");
    char ascii_art_file[256];

    srand(time(NULL));

    initscr();
    curs_set(0);
    scrollok(stdscr, TRUE);

    int row = 0;
    while (1) {
        random_ascii_art(ascii_art_folder, ascii_art_file, sizeof(ascii_art_file));
        display_ascii_art(ascii_art_file, &row);
        usleep(200000); // Increase sleep duration to reduce CPU load
    }

    endwin();

    return 0;
}

void display_ascii_art(const char *filename, int *row) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open ASCII art file");
        exit(1);
    }

    int ch, col = 0;
    int max_row, max_col;
    getmaxyx(stdscr, max_row, max_col);

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            if (col < max_col) {
                (*row)++;
            }
            col = 0;
            refresh();
            if (*row >= max_row) {
                scroll(stdscr);
                (*row)--;
            }
            usleep(100000); // Display each line for 0.1 seconds
        } else {
            if (col < max_col) {
                mvaddch(*row, col, ch);
                col++;
            }
        }
    }

    fclose(file);
    refresh();
}

bool has_txt_extension(const char *filename) {
    const char *dot = strrchr(filename, '.');
    return (dot && strcmp(dot, ".txt") == 0);
}

void random_ascii_art(const char *folder, char *filename, size_t len) {
    DIR *dir;
    struct dirent *ent;
    int file_count = 0;
    int random_file;

    if ((dir = opendir(folder)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG && has_txt_extension(ent->d_name)) {
                file_count++;
            }
        }
        closedir(dir);
    } else {
        perror("Unable to open directory");
        exit(1);
    }

    if (file_count == 0) {
        perror("No ASCII art files found");
        exit(1);
    }

    random_file = rand() % file_count;
    file_count = 0;

    if ((dir = opendir(folder)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG && has_txt_extension(ent->d_name)) {
                if (file_count == random_file) {
                    snprintf(filename, len, "%s/%s", folder, ent->d_name);
                    break;
                }
                file_count++;
            }
        }
        closedir(dir);
    }
}
