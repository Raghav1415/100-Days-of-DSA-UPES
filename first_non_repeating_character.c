// Problem Statement
// Given a string s consisting of lowercase English letters, find and return the first character that does not repeat in the string. If all characters repeat, return '$'.

// Input Format
// A single string s.

// Output Format
// Print the first non-repeating character or '$' if none exists.

// Sample Input
// geeksforgeeks

// Sample Output
// f

// Explanation
// The character 'f' occurs only once in the string and appears before any other non-repeating character.
#include <stdio.h>
#include <stdlib.h>

/**
 * Core Algorithm: Finds the first non-repeating character using a Frequency Map.
 * Time Complexity: O(N) where N is string length.
 * Space Complexity: O(1) strictly bound to 26 integers.
 */
char firstNonRepeating(const char* s) {
    // 1. Allocate a frequency array for the 26 lowercase English letters.
    // Initialize all counts to 0.
    int freq[26] = {0};
    
    // 2. PASS ONE: The Census
    // Iterate through the string and tally the exact occurrences of every character.
    for (int i = 0; s[i] != '\0'; i++) {
        freq[s[i] - 'a']++;
    }
    
    // 3. PASS TWO: The Verification
    // Iterate through the STRING again (NOT the frequency array).
    // This guarantees we check the characters in their original left-to-right order.
    for (int i = 0; s[i] != '\0'; i++) {
        // The first character we hit that has a total tally of exactly 1 is our winner.
        if (freq[s[i] - 'a'] == 1) {
            return s[i];
        }
    }
    
    // If the loop finishes, every character repeated at least once.
    return '$'; 
}

int main() {
    // Assuming a max string length of 100000 for standard problem sets.
    char s[100001];
    
    if (scanf("%100000s", s) != 1) {
        return 1;
    }

    char result = firstNonRepeating(s);
    printf("%c\n", result);

    return 0;
}