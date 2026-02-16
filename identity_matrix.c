// Problem: Write a program to check whether a given square matrix is an Identity Matrix. An identity matrix is a square matrix in which all diagonal elements are 1 and all non-diagonal elements are 0.

// Input:
// - First line: integer n representing number of rows and columns
// - Next n lines: n integers each representing the matrix elements

// Output:
// - Print "Identity Matrix" if the matrix satisfies the condition
// - Otherwise, print "Not an Identity Matrix"

// Example:
// Input:
// 3
// 1 0 0
// 0 1 0
// 0 0 1

// Output:
// Identity Matrix
#include <stdio.h>

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 1;

    int arr[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    int is_identity = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                if (arr[i][j] != 1) {
                    is_identity = 0;
                    break;
                }
            } else {
                if (arr[i][j] != 0) {
                    is_identity = 0;
                    break;
                }
            }
        }
        if (!is_identity) break;
    }

    if (is_identity) printf("Identity Matrix\n");
    else printf("Not an Identity Matrix\n");

    return 0;
}