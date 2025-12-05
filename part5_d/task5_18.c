#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100
const char *types[] = { "int", "char", "void" };
const char *args_types[] = { "const", "volatile", "volatile", "signed", "unsigned", "short", "long"};
enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);
int gettoken(void);
int getch(void);
void ungetch(int);

int tokentype;
char token[MAXTOKEN];
char argtype[MAXTOKEN];
char datatype[MAXTOKEN];
char name[MAXTOKEN] = "";
char out[1000];
static char bufer[BUFSIZE];
static int bufp = 0;

int main() {
    char qual[MAXTOKEN * 10] = "";
    char base[MAXTOKEN] = "";     

    while (1) {
        int t = gettoken();
        if (t == EOF) return 0;
        
        int is_qual = 0;
        for (int i = 0; i < 7; i++) {
            if (strcmp(token, args_types[i]) == 0) {
                if (qual[0]) strcat(qual, " ");
                strcat(qual, token);
                is_qual = 1;
                break;
            }
        }
        if (is_qual) continue;

        int is_base = 0;
        for (int i = 0; i < 3; i++) {
            if (strcmp(token, types[i]) == 0) {
                strcpy(base, token);
                is_base = 1;
                break;
            }
        }
        if (is_base) break;

        printf("error: expected type specifier\n");
        return 1;
    }

    strcpy(datatype, base);

    out[0] = '\0';
    name[0] = '\0';
    dcl();

    if (strlen(name) == 0) {
        printf("error: missing name\n");
        return 1;
    }

    if (strlen(qual) > 0) {
        printf("%s %s: %s %s\n", qual, name, out, datatype);
    } else {
        printf("%s: %s %s\n", name, out, datatype);
    }

    return 0;
}

void dcl(void) {
    int ns;
    for (ns = 0; gettoken() == '*'; ) 
        ns++;
    dirdcl();
    while(ns-- > 0) {
        strcat(out, " pointer to");
    }
}

void dirdcl(void) {
    int type;

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')') {
            printf("error: missing )\n");
        }
    } else if (tokentype == NAME) {
        strcpy(name, token);
    }
    else 
        printf("error: must be name or (dcl)\n");
    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS) {
            strcat(out, " function return");
        } else {
            strcat(out, " massive");
            strcat(out, token);
            strcat(out, " from");
        }
    }
}

int getch(void) {
    return (bufp > 0) ? bufer[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        bufer[bufp++] = c;
    }
}

int gettoken(void) {
    int c;
    char *p = token;
    while ((c = getch()) == ' ' || c == '\t') {
        ;
    }
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; )  
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); ) {
            *p++ = c;
        }
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else {
        return tokentype = c;
    }
}