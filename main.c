#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ANSI_COLOR_WHITE "\e[1;37m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"

typedef enum { false, true } bool;

bool is_int(char *stroke) {
    for (int i = 0; i != strlen(stroke) - 1; i++) {
        if ((int)stroke[i] >= 48 && (int)stroke[i] <= 57) {
        }
        else return false;
    }
    return true;
}

long int make_int(bool test, char *stroke) {
    long n;
    if (test == true) {
        if (stroke[0] == '0') {
            printf(ANSI_COLOR_RED
                   "ERROR: Введенно некорректное число строк!\n");
            return 0;
        }
        n = strtol(stroke, NULL, 10);
        return n;
    }
    else {
        printf(ANSI_COLOR_RED "ERROR: Введенно некорректное число строк!\n");
        return 0;
    }
}

int make_file() {
    FILE *cur_file;
    long n;
    char k[20];
    char str[100];
    char null = '\0';
    char ent = '\n';
    printf("Число строк:\n");
    fgets(k, 20, stdin);
    n = make_int(is_int(k), k);
    cur_file = fopen("data.txt", "w");
    for (int i = 0; i < n; i++) {
        printf("Введите %d-ую строку:\n", i + 1);
        if (i == n - 1) {
            fgets(str, 100, stdin);
            if (*str == '\n') fprintf(cur_file, &null);
            else fprintf(cur_file, "%s", strtok(str, "\n"));
        }
        else {
            fgets(str, 100, stdin);
            if (*str == '\n') fprintf(cur_file, &ent);
            else fprintf(cur_file, "%s", str);
        }
    }
    fclose(cur_file);
    return (int)n;
}

int search(char s1[], const char s2[]) {
    int k, i, count = 0;
    for (k = 0; s1[k] != '\0'; k++) {
        for (i = 0; s2[i] != '\0'; i++)
            if (s1[k] == s2[i])
                count++;
    }
    return count;
}

int unique(FILE *file, int size) {
    char str[100];
    char *istr;
    int wrd_count = 0;
    for (int i = 0; i < size; i++) {
        fgets(str, 100, file);
        istr = strtok(str, " ");
        while (istr != NULL) {
            wrd_count++;
            istr = strtok(NULL, " ");
        }
    }
    return wrd_count;
}

int _min(const char *list, int len) {
    int min = 1000;
    for (int i = 0; i < len; i++) {
        if ((list[i] < min) && (list[i] != 0)) min = (int)list[i];
    }
    return min;
}

void strstrip(char str[], char t) {
    int i = 0, j;
    while (i < strlen(str)) {
        if (str[i] == t)
            for (j = i; j < strlen(str); j++)
                str[j] = str[j + 1];
        else i++;
    }
}

void solution(int size) {
    FILE *cur_file, *cur_file1, *cur_file2, *new_file;
    char str[100];
    char letters[30] = "aeiou";
    char *istr;
    int j = 0;
    int m_vowel;
    int t;

    cur_file = fopen("data.txt", "r");
    int wrds_count = unique(cur_file, size);
    char *counts = malloc(wrds_count * sizeof(int));
    fclose(cur_file);

    cur_file1 = fopen("data.txt", "r");
    for (int i = 0; i < size; i++) {
        fgets(str, 100, cur_file1);
        istr = strtok(str, " ");
        while (istr != NULL) {
            counts[j] = search(istr, letters);
            istr = strtok(NULL, " ");
            j++;
        }
    }
    fclose(cur_file1);

    m_vowel = _min(counts, wrds_count);
    cur_file2 = fopen("data.txt", "r");
    new_file = fopen("res.txt", "w");
    for (int i = 0; i < size; i++) {
        t = 0;
        fgets(str, 100, cur_file2);
        istr = strtok(str, " ");
        while (istr != NULL) {
            if (search(istr, letters) == m_vowel) {
                strstrip(istr, '\n');
                if (t == 0)
                    if (i == 0)
                        fprintf(new_file, "%s", istr);
                    else fprintf(new_file, "\n%s", istr);
                else fprintf(new_file, " %s", istr);
                t++;
            }
            istr = strtok(NULL, " ");
        }
    }
    fclose(cur_file2);
    fclose(new_file);
}

int lines_count() {
    FILE *file;
    int lines_count = 1;
    file = fopen("res.txt", "r");
    while (!feof(file)) {
        if (fgetc(file) == '\n')
            lines_count++;
    }
    return lines_count;
}

void output(int size) {
    FILE *output_file;
    char outline[100];
    output_file = fopen("res.txt", "r");
    printf(ANSI_COLOR_GREEN "\nНовый файл:\n");
    for (int i = 0; i < size; i++) {
        fgets(outline, 100, output_file);
        printf(ANSI_COLOR_WHITE "%s", outline);
    }
    printf("\n");
    fclose(output_file);
}

int main(void) {
    int n = make_file();
    if (n == 0) return 0;
    solution(n);
    output(lines_count());
    return 0;
}

