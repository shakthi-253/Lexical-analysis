#include <stdio.h>
#include <ctype.h>
#include <string.h>

char keywords[][10] = {
    "int","float","if","else","while",
    "return","for","char","double","void"
};

int isKeyword(char *word) {
    for(int i=0;i<10;i++) {
        if(strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    FILE *fp;
    char ch, buffer[50];
    int i = 0;

    fp = fopen("input.c", "r");

    if(fp == NULL) {
        printf("File not found!\n");
        return 0;
    }

    while((ch = fgetc(fp)) != EOF) {

        // IDENTIFIER or KEYWORD
        if(isalpha(ch)) {
            buffer[i++] = ch;
            while(isalnum(ch = fgetc(fp))) {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            i = 0;

            if(isKeyword(buffer))
                printf("%s : Keyword\n", buffer);
            else
                printf("%s : Identifier\n", buffer);

            fseek(fp, -1, SEEK_CUR);
        }

        // NUMBER
        else if(isdigit(ch)) {
            printf("%c : Number\n", ch);
        }

        // OPERATORS
        else if(strchr("+-*/=%", ch)) {
            printf("%c : Operator\n", ch);
        }

        // SPECIAL SYMBOLS
        else if(strchr("(){}[],;", ch)) {
            printf("%c : Special Symbol\n", ch);
        }

        // HEADER FILE
        else if(ch == '#') {
            printf("# : Header File\n");
        }

        // COMMENTS
        else if(ch == '/') {
            char next = fgetc(fp);
            if(next == '/') {
                while((ch = fgetc(fp)) != '\n');
                printf("// Comment\n");
            }
        }
    }

    fclose(fp);
    return 0;
}