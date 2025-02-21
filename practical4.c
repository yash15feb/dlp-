/*Task 1*/
%{
#include <stdio.h>
%}

%%

[0-9]+    { printf("%s\n", yytext); }
.         { /* Ignore non-numeric characters */ }

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}





/*Task 2*/
%{
#include <stdio.h>
%}

%%
[Cc]harusat   printf("university");
.            putchar(yytext[0]);

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}





/*Task 3*/
%{
#include <stdio.h>
int char_count = 0, word_count = 0, line_count = 0;
%}

%%

[^ \t\n]+  { word_count++; char_count += yyleng; }
[ \t]     { char_count += yyleng; }
\n        { line_count++; char_count++; }

%%

int main() {
    yylex();
    printf("Characters: %d\n", char_count);
    printf("Words: %d\n", word_count);
    printf("Lines: %d\n", line_count);
    return 0;
}

int yywrap() {
    return 1;
}




/*Task 4*/
%{
#include <stdio.h>
#include <string.h>

int has_upper = 0, has_lower = 0, has_digit = 0, has_symbol = 0;
char symbols[] = "*;#$@";
%}

%%

[A-Z]    { has_upper = 1; }
[a-z]    { has_lower = 1; }
[0-9]    { has_digit = 1; }
[*;#$@]  { has_symbol = 1; }

%%

int main() {
    char password[20];
    printf("Enter password: ");
    scanf("%s", password);

    int length = strlen(password);
    if (length < 9 || length > 15) {
        printf("Invalid password\n");
        return 0;
    }

    yylex();

    if (has_upper && has_lower && has_digit && has_symbol)
        printf("Valid password\n");
    else
        printf("Invalid password\n");

    return 0;
}

int yywrap() {
    return 1;
}
