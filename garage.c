#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10
#define MAX_PLATE_LEN 20

// Structure representing a car with license plate and move count
typedef struct Car {
    char plate[MAX_PLATE_LEN];
    int moves;
} Car;

// Structure for queue holding Cars
typedef struct Queue {
    int front, rear, size;
    Car arr[MAX_SIZE];
} Queue;

// Initialize an empty queue
void initQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
    q->size = MAX_SIZE;
}

// Check if queue is empty
int isEmpty(Queue* q) {
    return q->front == q->rear;
}

// Check if queue is full
int isFull(Queue* q) {
    return (q->rear + 1) % q->size == q->front;
}

// Enqueue a car into the queue. Returns 1 on success, 0 if full
int enqueue(Queue* q, const char* plate) {
    if (isFull(q)) {
        return 0; // Queue full
    }
    strncpy(q->arr[q->rear].plate, plate, MAX_PLATE_LEN);
    q->arr[q->rear].plate[MAX_PLATE_LEN - 1] = '\0';
    q->arr[q->rear].moves = 0;
    q->rear = (q->rear + 1) % q->size;
    return 1;
}

// Dequeue a car from the queue. Returns 1 on success, 0 if empty
int dequeue(Queue* q, Car* car) {
    if (isEmpty(q)) {
        return 0; // Empty
    }
    if (car != NULL) {
        *car = q->arr[q->front];
    }
    q->front = (q->front + 1) % q->size;
    return 1;
}

// Peek front car without dequeuing. Returns NULL if empty
Car* front(Queue* q) {
    if (isEmpty(q)) return NULL;
    return &q->arr[q->front];
}

// Find car index by plate in queue, returns -1 if not found
int findCarIndex(Queue* q, const char* plate) {
    int i = q->front;
    while (i != q->rear) {
        if (strcmp(q->arr[i].plate, plate) == 0) {
            return i;
        }
        i = (i + 1) % q->size;
    }
    return -1;
}

// Print current queue status
void printQueue(Queue* q) {
    printf("Garage state (north to south):\n");
    if (isEmpty(q)) {
        printf("  [empty]\n");
        return;
    }
    int i = q->front;
    while (i != q->rear) {
        printf("  %s (moves: %d)\n", q->arr[i].plate, q->arr[i].moves);
        i = (i + 1) % q->size;
    }
}

// Move cars temporarily from src to dest queue until car at index targetIdx is at front of src
// Increment move count for cars moved out plus the departing car's final move
void departCar(Queue* garage, Queue* temp, const char* plate) {
    if (isEmpty(garage)) {
        printf("Garage is empty. Car %s not found.\n", plate);
        return;
    }

    int carIdx = findCarIndex(garage, plate);
    if (carIdx == -1) {
        printf("Car %s not found in garage.\n", plate);
        return;
    }

    // Move cars out of garage to temp until the target car is at front
    Car movedCars[MAX_SIZE];
    int movedCount = 0;
    while (garage->front != carIdx) {
        Car tempCar;
        dequeue(garage, &tempCar);
        tempCar.moves++; // car moved temporarily
        movedCars[movedCount++] = tempCar;
        enqueue(temp, tempCar.plate);
        carIdx = (carIdx + 1) % garage->size; // update car index since queue front changed
    }

    // Remove the departing car (front of garage)
    Car departingCar;
    dequeue(garage, &departingCar);
    departingCar.moves++; // count departure as move
    printf("Car %s has departed, moved %d times.\n", departingCar.plate, departingCar.moves);

    // Restore moved cars back to garage in same order
    for (int i = 0; i < movedCount; i++) {
        enqueue(garage, movedCars[i].plate);
        // Set their move counts correctly by copying from temp queue cars (which has updated moves)
        // We adjust move counts after restoration
        garage->arr[(garage->rear + MAX_SIZE - 1) % MAX_SIZE].moves = movedCars[i].moves;
    }
}

int main() {
    Queue garage, tempQueue;
    initQueue(&garage);
    initQueue(&tempQueue);

    char command;
    char plate[MAX_PLATE_LEN];

    printf("Commands:\n  A <plate> - arrive\n  D <plate> - depart\n  Q - quit\n");

    while (1) {
        printf("Enter command: ");
        int result = scanf(" %c", &command);
        if (result != 1) break;

        if (command == 'Q' || command == 'q') {
            break;
        }

        if (command == 'A' || command == 'a') {
            scanf("%s", plate);
            if (enqueue(&garage, plate)) {
                printf("Car %s has arrived.\n", plate);
            } else {
                printf("Garage full. Car %s must wait.\n", plate);
            }
            printQueue(&garage);
        } else if (command == 'D' || command == 'd') {
            scanf("%s", plate);
            departCar(&garage, &tempQueue, plate);
            printQueue(&garage);
            // Clear tempQueue after restoration
            initQueue(&tempQueue);
        } else {
            printf("Invalid command. Use A <plate>, D <plate>, or Q.\n");
            char ch;
            while ((ch = getchar()) != '\n' && ch != EOF); // flush input line
        }
    }

    printf("Exiting program.\n");
    return 0;
}
