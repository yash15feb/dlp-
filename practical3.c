
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    KEYWORD,
    IDENTIFIER,
    CONSTANT,
    STRING,
    OPERATOR,
    DELIMITER,
    UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char value[50];
} Token;

typedef struct {
    char identifier[50];
    int index;
} SymbolTableEntry;

void tokenize(char* code, Token* tokens, int* tokenCount, SymbolTableEntry* symbolTable, int* tableSize);
void removeComments(char* code);
void removeWhitespace(char* code);
TokenType getTokenType(char* token);
void addToSymbolTable(char* identifier, SymbolTableEntry* symbolTable, int* tableSize);
char* tokenTypeToString(TokenType type);

int main() {
    char code[] = "int main() { int a = 5; char b = 'x'; return a + b; }";
    Token tokens[100];
    int tokenCount = 0;
    SymbolTableEntry symbolTable[100];
    int tableSize = 0;

    tokenize(code, tokens, &tokenCount, symbolTable, &tableSize);

    printf("TOKENS\n");
    for (int i = 0; i < tokenCount; i++) {
        printf("(%s, %s)\n", tokenTypeToString(tokens[i].type), tokens[i].value);
    }

    printf("\nSYMBOL TABLE ENTRIES\n");
    for (int i = 0; i < tableSize; i++) {
        printf("%d) %s\n", symbolTable[i].index, symbolTable[i].identifier);
    }

    return 0;
}

void tokenize(char* code, Token* tokens, int* tokenCount, SymbolTableEntry* symbolTable, int* tableSize) {

    char* token = strtok(code, " ()[]{};,+-*/=<>!&|");
    while (token != NULL) {
        TokenType type = getTokenType(token);
        strcpy(tokens[*tokenCount].value, token);
        tokens[*tokenCount].type = type;

        if (type == IDENTIFIER) {
            addToSymbolTable(token, symbolTable, tableSize);
        }

        (*tokenCount)++;
        token = strtok(NULL, " ()[]{};,+-*/=<>!&|");
    }
}

void removeComments(char* code) {
    // Implementation for removing single-line and multi-line comments
    // ...
}

void removeWhitespace(char* code) {
    // Implementation for removing whitespace characters
    // ...
}

TokenType getTokenType(char* token) {
    static char* keywords[] = {"int", "main", "char", "return", "if", "else", "for", "while", "do"};
    static char* operators[] = {"+", "-", "*", "/", "=", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "!", "++", "--"};
    static char* delimiters[] = {"(", ")", "{", "}", "[", "]", ",", ";", ":"};

    for (size_t i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(token, keywords[i]) == 0) {
            return KEYWORD;
        }
    }

    for (size_t i = 0; i < sizeof(operators) / sizeof(operators[0]); i++) {
        if (strcmp(token, operators[i]) == 0) {
            return OPERATOR;
        }
    }

    for (size_t i = 0; i < sizeof(delimiters) / sizeof(delimiters[0]); i++) {
        if (strcmp(token, delimiters[i]) == 0) {
            return DELIMITER;
        }
    }

    if (isdigit(*token)) {
        return CONSTANT;
    }

    if (*token == '\'' && strlen(token) == 3) { // Check for single-character string
        return STRING;
    }

    return IDENTIFIER;
}

void addToSymbolTable(char* identifier, SymbolTableEntry* symbolTable, int* tableSize) {
    // Check if identifier already exists in the table
    for (int i = 0; i < *tableSize; i++) {
        if (strcmp(identifier, symbolTable[i].identifier) == 0) {
            return; // Identifier already exists
        }
    }

    strcpy(symbolTable[*tableSize].identifier, identifier);
    symbolTable[*tableSize].index = *tableSize + 1;
    (*tableSize)++;
}

char* tokenTypeToString(TokenType type) {
    switch (type) {
        case KEYWORD:
            return "KEYWORD";
        case IDENTIFIER:
            return "IDENTIFIER";
        case CONSTANT:
            return "CONSTANT";
        case STRING:
            return "STRING";
        case OPERATOR:
            return "OPERATOR";
        case DELIMITER:
            return "DELIMITER";
        default:
            return "UNKNOWN";
    }
}
