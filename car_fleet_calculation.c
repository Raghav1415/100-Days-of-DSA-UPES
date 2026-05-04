// Problem: Given a target distance and cars’ positions & speeds, compute the number of car fleets reaching the destination.
// Sort cars by position in descending order and calculate time to reach target.
#include <stdio.h>
#include <stdlib.h>

// 1. Structural Binding: Keep position, speed, and time inextricably linked
typedef struct {
    int pos;
    int speed;
    double time;
} Car;

/**
 * Comparator function for qsort
 * Sorts cars in DESCENDING order by position (closest to target first)
 */
int compareCars(const void* a, const void* b) {
    Car* carA = (Car*)a;
    Car* carB = (Car*)b;
    return carB->pos - carA->pos; 
}

/**
 * Core Algorithm: Monotonic Time Evaluation
 * Time Complexity: O(N log N) for sorting
 * Space Complexity: O(N) for the struct array
 */
int carFleet(int target, int* position, int positionSize, int* speed, int speedSize) {
    // Edge case: No cars on the road
    if (positionSize == 0) return 0;

    // Dynamically allocate the paired array
    Car* cars = (Car*)malloc(positionSize * sizeof(Car));
    if (!cars) {
        fprintf(stderr, "Fatal: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Populate the structs and calculate precise floating-point times
    for (int i = 0; i < positionSize; i++) {
        cars[i].pos = position[i];
        cars[i].speed = speed[i];
        
        // TRAP AVOIDANCE: Cast the numerator to double FIRST to force floating-point math
        cars[i].time = (double)(target - position[i]) / speed[i];
    }

    // Sort cars from closest to furthest
    qsort(cars, positionSize, sizeof(Car), compareCars);

    int fleets = 0;
    double slowest_leader_time = 0.0;

    // The Sweep Engine
    for (int i = 0; i < positionSize; i++) {
        // If this car takes STRICTLY LONGER than the fleet ahead of it,
        // it is physically impossible for it to catch up. It becomes a new fleet.
        if (cars[i].time > slowest_leader_time) {
            fleets++;
            slowest_leader_time = cars[i].time; 
        }
        // If it takes LESS OR EQUAL time, it catches the car ahead.
        // Because you cannot pass, it joins that fleet and slows down. No new fleet is counted.
    }

    free(cars);
    return fleets;
}

int main() {
    int target = 12;
    int position[] = {10, 8, 0, 5, 3};
    int speed[] = {2, 4, 1, 1, 3};
    int n = sizeof(position) / sizeof(position[0]);

    int result = carFleet(target, position, n, speed, n);
    printf("Number of car fleets: %d\n", result);

    return 0;
}