#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_valid_string(char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != 'a' && s[i] != 'b') {
            return 0;
        }
    }
    int found_b = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == 'b') {
            found_b = 1;
        } else if (found_b && s[i] == 'a') {
            return 0;
        }
    }
    return 1;
}

int main() {
    char user_input[100];
    printf("Enter a string: ");
    scanf("%s", user_input);

    if (is_valid_string(user_input)) {
        printf("%s = Valid string\n", user_input);
    } else {
        printf("%s = Invalid string\n", user_input);
    }

    return 0;
}
