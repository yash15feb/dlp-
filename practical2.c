#include <stdio.h>
#include <string.h>

int simulate_dfa(char *string) {
    int dfa[5][2] = {
        {0, 0}, {2, 3}, {1, 2}, {4, 1}, {3, 2}
    };
    int current_state = 1;

    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == 'a') {
            current_state = dfa[current_state][0];
        } else if (string[i] == 'b') {
            current_state = dfa[current_state][1];
        } else {
            return 0;
        }
    }

    return current_state == 2;
}

int main() {
    char *test_cases[] = {"bbbb", "aaa", "baaabb", "aaabbb", "aaaab", "abbabb", "abb", "aaaaabb"};
    int n = sizeof(test_cases) / sizeof(test_cases[0]);

    printf("\nDFA Simulation Results:\n");
    for (int i = 0; i < n; i++) {
        printf("%s: %s\n", test_cases[i], simulate_dfa(test_cases[i]) ? "Accepted" : "Rejected");
    }

    return 0;
}
