#include <stdio.h>
#include <ctype.h>
#define MAXLINE 1000

double atof(char line[]);

double atof(char s[]) {
    double value, power;
    int i, sign, exp_value, exp_sign = 1;
    for (i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    
    for (value = 0.0; isdigit(s[i]); i++) {
        value = value * 10.0 + (s[i] - '0');
    }
    if (s[i] == '.') i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        value = value * 10.0 + (s[i] - '0');
        power *= 10.0;
    }
    double result = value / power;
    if (s[i] == 'e' || s[i] == 'E') i++;
    if (s[i] == '-') {
        exp_sign = -1;
        i++;
    }
    for (exp_value = 0; isdigit(s[i]); i++) {
        exp_value = exp_value * 10 + (s[i] - '0');
    }
    if (exp_sign == -1) {
        double temp = 1.0;
        for (int j = 0; j < exp_value; j++) {
            temp *= 10;
        }
        temp = 1 / temp;
        return result * temp;
    } else if (exp_sign == 1) {
        double temp = 1.0;
        for (int j = 0; j < exp_value; j++) {
            temp *= 10;
        }
        return result * temp;
    }
    return result;
}

int get_line(char s[], int lim) {
    int c, i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') s[i++] = c;
    if (c == '\n') s[i++] = '\n';
    s[i] = '\0';
    return i;
}

int main() {
    char line[1000];
    double sum = 0;
    while (get_line(line, MAXLINE) > 0) {
        printf("%g\n", sum += atof(line));
    }
    return 0;
}