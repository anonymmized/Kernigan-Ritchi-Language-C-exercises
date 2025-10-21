#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1000

int balance_getline(int lim);

int in_ml_comm = 0;

int main() {
    int len;
    while ((len = balance_getline(MAXLINE)) > 0) {
        continue;
    }
    if (in_ml_comm == 1) {
        printf("There's an unclosed multiline comment somewhere");
    }
    return 0;
}

int balance_getline(int lim) {
    char s[lim];
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i++] = '\n';
    }
    s[i] = '\0';
    int in_s_quotes = 0, in_m_quotes = 0, in_left_brackets = 0, in_right_brackets = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '\\' && (s[i + 1] == '"' || s[i + 1] == '\'')) {
            i++;
            continue;
        }
        if (s[i] == '*' && s[i + 1] == '/') {
            in_ml_comm = 0;
            i++;
            continue;
        }
        if (s[i] == '/' && s[i + 1] == '*') {
            in_ml_comm = 1;
            i++;
            continue;
        } 
        if (s[i] == '\'') {
            in_s_quotes += 1;
            continue;
        }
        if (s[i] == '"') {
            in_m_quotes += 1;
            continue;
        }
        if (s[i] == '(') {
            in_left_brackets += 1;
            continue;
        }
        if (s[i] == ')') {
            in_right_brackets += 1;
            continue;
        }
    }
    if (in_left_brackets != in_right_brackets) {
        printf("There is an unclosed or unopened parenthesis somewhere\n");
    }
    else if (in_m_quotes % 2 != 0) {
        printf("There's an unclosed or unopened quote somewhere\n");
    }
    else if (in_s_quotes % 2 != 0) {
        printf("There's an unclosed or unopened quote somewhere\n");
    }
    else {
        printf("Everything is fine\n");
    }
    return i;
}