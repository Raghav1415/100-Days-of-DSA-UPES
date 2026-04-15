// Problem Statement
// Implement a hash table using quadratic probing with formula:

// h(k, i) = (h(k) + i*i) % m

// Input Format
// Same as previous.

// Output Format
// Result of SEARCH operations.

// Sample Input
// 7
// 4
// INSERT 49
// INSERT 56
// SEARCH 49
// SEARCH 15

// Sample Output
// FOUND
// NOT FOUND

// Explanation
// Collisions resolved using i² jumps.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> // For INT_MIN

#define EMPTY INT_MIN

// --- Hash Table Infrastructure ---
typedef struct HashTable {
    int size;
    int* table;
} HashTable;

HashTable* createHashTable(int size) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (!ht) exit(EXIT_FAILURE);
    
    ht->size = size;
    ht->table = (int*)malloc(size * sizeof(int));
    if (!ht->table) exit(EXIT_FAILURE);

    // Initialize all slots to our EMPTY marker
    for (int i = 0; i < size; i++) {
        ht->table[i] = EMPTY;
    }
    
    return ht;
}

// Core Hash Function: h(k)
int hash(int key, int m) {
    // Handle negative keys gracefully
    int h = key % m;
    return (h < 0) ? h + m : h;
}

/**
 * Inserts a key using Quadratic Probing: h(k, i) = (h(k) + i^2) % m
 */
void insert(HashTable* ht, int key) {
    int m = ht->size;
    int base_hash = hash(key, m);

    // Bounded loop: Never probe more than 'm' times to prevent infinite loops
    for (int i = 0; i < m; i++) {
        // The Quadratic Jump
        int probe_index = (base_hash + (i * i)) % m;

        // If we find an empty slot, claim it
        if (ht->table[probe_index] == EMPTY) {
            ht->table[probe_index] = key;
            return;
        }
        
        // Prevent duplicate keys
        if (ht->table[probe_index] == key) {
            return;
        }
    }
    // If we reach here, the table is functionally full or cycling endlessly.
    // In production, this triggers a resize/rehash event.
}

/**
 * Searches for a key and outputs according to specification.
 */
void search(HashTable* ht, int key) {
    int m = ht->size;
    int base_hash = hash(key, m);

    for (int i = 0; i < m; i++) {
        int probe_index = (base_hash + (i * i)) % m;

        if (ht->table[probe_index] == key) {
            printf("FOUND\n");
            return;
        }

        // If we hit an EMPTY slot, the chain is broken.
        // The key mathematically cannot exist further down the probe sequence.
        if (ht->table[probe_index] == EMPTY) {
            break;
        }
    }
    
    // If we broke early or exhausted all 'm' probes
    printf("NOT FOUND\n");
}

// Memory Cleanup
void freeHashTable(HashTable* ht) {
    if (ht) {
        free(ht->table);
        free(ht);
    }
}

int main() {
    int m, n;
    
    // Read table size (m) and number of operations (n)
    if (scanf("%d", &m) != 1) return 1;
    if (scanf("%d", &n) != 1) return 1;

    HashTable* ht = createHashTable(m);

    // Process operations
    for (int i = 0; i < n; i++) {
        char op[10];
        int val;
        scanf("%s %d", op, &val);

        if (strcmp(op, "INSERT") == 0) {
            insert(ht, val);
        } else if (strcmp(op, "SEARCH") == 0) {
            search(ht, val);
        }
    }

    freeHashTable(ht);
    return 0;
}