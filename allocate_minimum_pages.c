// Problem Statement
// Given an array of integers where each element represents the number of pages in a book, and m students, allocate books such that each student gets at least one book and the maximum number of pages assigned to a student is minimized.

// Books must be allocated in contiguous order.

// Input Format
// n m
// n space-separated integers representing pages in books

// Output Format
// Print the minimum possible value of the maximum pages assigned to any student.

// Sample Input
// 4 2
// 12 34 67 90

// Sample Output
// 113

// Explanation
// One optimal allocation is:
// Student 1: 12 + 34 + 67 = 113
// Student 2: 90
// Maximum pages = 113 (minimum possible).
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * The Greedy Validator
 * Simulates handing out books to see if we can do it using 'm' or fewer students
 * without any single student exceeding 'max_pages_allowed'.
 */
bool canAllocate(int books[], int n, int m, long long max_pages_allowed) {
    int students_needed = 1;
    long long current_student_pages = 0;

    for (int i = 0; i < n; i++) {
        // If we try to hand the student the next book and it busts their limit...
        if (current_student_pages + books[i] > max_pages_allowed) {
            
            // We must bring in a new student
            students_needed++;
            current_student_pages = books[i]; // They start fresh with this book
            
            // If we run out of allowed students, this page limit is physically impossible
            if (students_needed > m) {
                return false;
            }
        } else {
            // Otherwise, keep stacking books onto the current student
            current_student_pages += books[i];
        }
    }
    return true; // We successfully distributed all books!
}

/**
 * Core Algorithm: Binary Search on Answer
 * Time Complexity: O(N * log(Sum - Max))
 * Space Complexity: O(1)
 */
long long allocateBooks(int books[], int n, int m) {
    // Edge Case: If there are more students than books, it's impossible 
    // to give every student at least one book.
    if (m > n) return -1;

    long long low = 0;
    long long high = 0;

    // Define the boundaries of our search space
    for (int i = 0; i < n; i++) {
        if (books[i] > low) {
            low = books[i]; // The thickest book
        }
        high += books[i];   // The sum of all books
    }

    long long best_allocation = -1;

    // Binary Search the theoretical page limits
    while (low <= high) {
        long long mid = low + (high - low) / 2;

        if (canAllocate(books, n, m, mid)) {
            // It is possible to limit students to 'mid' pages.
            // But can we squeeze them even tighter (a smaller max)?
            best_allocation = mid;
            high = mid - 1; 
        } else {
            // 'mid' is too tight. We ran out of students. We must allow more pages.
            low = mid + 1;
        }
    }

    return best_allocation;
}

int main() {
    int n, m;
    
    if (scanf("%d %d", &n, &m) != 2) return 1;

    int* books = (int*)malloc(n * sizeof(int));
    if (!books) {
        fprintf(stderr, "Fatal: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &books[i]);
    }

    long long result = allocateBooks(books, n, m);
    printf("%lld\n", result);

    free(books);
    return 0;
}