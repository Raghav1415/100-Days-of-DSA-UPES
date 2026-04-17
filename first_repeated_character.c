// Problem Statement
// Given a string s consisting of lowercase letters, find the first repeated character in the string. A character is considered repeated if it appears more than once, and among all such characters, the one whose second occurrence has the smallest index should be returned.

// Input Format
// A single string s.

// Output Format
// Print the first repeated character. If no character is repeated, print -1.

// Sample Input
// geeksforgeeks

// Sample Output
// e
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Core Algorithm: Finds the first repeated character based on second occurrence.
 * Time Complexity: O(N) where N is string length.
 * Space Complexity: O(1) strictly bound to 26 bytes.
 */
char findFirstRepeated(const char* s) {
    // Allocate a boolean array for the 26 lowercase English letters.
    // Automatically initialized to false.
    bool seen[26] = {false};
    
    // Iterate through the string until the null terminator
    for (int i = 0; s[i] != '\0'; i++) {
        // Map the ASCII character 'a'-'z' to an integer index 0-25
        int index = s[i] - 'a';
        
        // If we have already seen this character, it is our first collision!
        if (seen[index]) {
            return s[i]; // Early exit
        }
        
        // Otherwise, mark this character as seen
        seen[index] = true;
    }
    
    // If the loop finishes without returning, no characters repeated
    return '\0'; 
}

int main() {
    // In competitive programming/interviews, constraints dictate buffer sizes.
    // Assuming a max string length of 100000 for standard problem sets.
    char s[100001];
    
    if (scanf("%100000s", s) != 1) {
        return 1;
    }

    char result = findFirstRepeated(s);

    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("-1\n");
    }

    return 0;
}