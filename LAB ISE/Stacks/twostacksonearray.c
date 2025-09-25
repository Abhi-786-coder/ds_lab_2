#include <stdio.h>
#include <stdlib.h>

struct TwoStacks {
    int top1, top2;
    unsigned capacity;
    int *array;
};

struct TwoStacks* createTwoStacks(unsigned capacity) {
    struct TwoStacks *ts = (struct TwoStacks*)malloc(sizeof(struct TwoStacks));
    ts->capacity = capacity;
    ts->top1 = -1;
    ts->top2 = capacity;
    ts->array = (int *)malloc(ts->capacity * sizeof(int));
    return ts;
}

int isFull(struct TwoStacks *ts) {
    return ts->top1 == ts->top2 - 1;
}

int isEmpty1(struct TwoStacks *ts) {
    return ts->top1 == -1;
}

int isEmpty2(struct TwoStacks *ts) {
    return ts->top2 == ts->capacity;
}

void push1(struct TwoStacks *ts, int value) {
    if (!isFull(ts)) {
        ts->array[++(ts->top1)] = value;
        printf("Pushed %d to Stack 1\n", value);
    } else {
        printf("Overflow: No space to push into Stack 1\n");
    }
}

void push2(struct TwoStacks *ts, int value) {
    if (!isFull(ts)) {
        ts->array[--(ts->top2)] = value;
        printf("Pushed %d to Stack 2\n", value);
    } else {
        printf("Overflow: No space to push into Stack 2\n");
    }
}

int pop1(struct TwoStacks *ts) {
    if (!isEmpty1(ts)) {
        return ts->array[(ts->top1)--];
    } else {
        printf("Underflow: Stack 1 is empty\n");
        return -1;
    }
}

int pop2(struct TwoStacks *ts) {
    if (!isEmpty2(ts)) {
        return ts->array[(ts->top2)++];
    } else {
        printf("Underflow: Stack 2 is empty\n");
        return -1;
    }
}

int peek1(struct TwoStacks *ts) {
    if (!isEmpty1(ts)) return ts->array[ts->top1];
    printf("Stack 1 is empty\n");
    return -1;
}

int peek2(struct TwoStacks *ts) {
    if (!isEmpty2(ts)) return ts->array[ts->top2];
    printf("Stack 2 is empty\n");
    return -1;
}

void display1(struct TwoStacks *ts) {
    if (isEmpty1(ts)) {
        printf("Stack 1 is empty\n");
        return;
    }
    printf("Stack 1 (top -> bottom): ");
    for (int i = ts->top1; i >= 0; i--) {
        printf("%d ", ts->array[i]);
    }
    printf("\n");
}

void display2(struct TwoStacks *ts) {
    if (isEmpty2(ts)) {
        printf("Stack 2 is empty\n");
        return;
    }
    printf("Stack 2 (top -> bottom): ");
    for (int i = ts->top2; i < (int)ts->capacity; i++) {
        printf("%d ", ts->array[i]);
    }
    printf("\n");
}

void freeTwoStacks(struct TwoStacks *ts) {
    free(ts->array);
    free(ts);
}

int main() {
    unsigned capacity;
    printf("Enter total capacity (n) for both stacks: ");
    if (scanf("%u", &capacity) != 1 || capacity == 0) {
        printf("Invalid capacity\n");
        return 1;
    }

    struct TwoStacks *ts = createTwoStacks(capacity);

    int running = 1;
    while (running) {
        int choice;
        printf("\nOperations:\n");
        printf("1. Push to Stack 1\n");
        printf("2. Push to Stack 2\n");
        printf("3. Pop from Stack 1\n");
        printf("4. Pop from Stack 2\n");
        printf("5. Peek Stack 1\n");
        printf("6. Peek Stack 2\n");
        printf("7. Display Stack 1\n");
        printf("8. Display Stack 2\n");
        printf("9. Check Full/Empty status\n");
        printf("10. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            // clear invalid input
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("Invalid input. Try again.\n");
            continue;
        }

        if (choice == 1) {
            int x;
            printf("Enter value to push into Stack 1: ");
            if (scanf("%d", &x) == 1) push1(ts, x);
            else {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF) {}
                printf("Invalid value\n");
            }
        } else if (choice == 2) {
            int x;
            printf("Enter value to push into Stack 2: ");
            if (scanf("%d", &x) == 1) push2(ts, x);
            else {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF) {}
                printf("Invalid value\n");
            }
        } else if (choice == 3) {
            int v = pop1(ts);
            if (v != -1) printf("Popped from Stack 1: %d\n", v);
        } else if (choice == 4) {
            int v = pop2(ts);
            if (v != -1) printf("Popped from Stack 2: %d\n", v);
        } else if (choice == 5) {
            int v = peek1(ts);
            if (v != -1) printf("Top of Stack 1: %d\n", v);
        } else if (choice == 6) {
            int v = peek2(ts);
            if (v != -1) printf("Top of Stack 2: %d\n", v);
        } else if (choice == 7) {
            display1(ts);
        } else if (choice == 8) {
            display2(ts);
        } else if (choice == 9) {
            printf("isFull: %s\n", isFull(ts) ? "true" : "false");
            printf("Stack1 isEmpty: %s\n", isEmpty1(ts) ? "true" : "false");
            printf("Stack2 isEmpty: %s\n", isEmpty2(ts) ? "true" : "false");
            printf("Used total = %u\n", (unsigned)(ts->top1 + 1 + (ts->capacity - ts->top2)));
        } else if (choice == 10) {
            running = 0;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    freeTwoStacks(ts);
    return 0;
}
