#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int coeff;
    int pow;
    struct Node* next;
};

struct Node* head1 = NULL;
struct Node* head2 = NULL;

// Create new node
struct Node* createNode(int coeff, int pow) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->coeff = coeff;
    newNode->pow = pow;
    newNode->next = NULL;
    return newNode;
}

// Insert at end
void insertAtEnd(struct Node** head, int coeff, int pow) {
    struct Node* newNode = createNode(coeff, pow);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
}

// Add two polynomials
struct Node* addPolynomials(struct Node* p1, struct Node* p2) {
    struct Node* result = NULL;
    struct Node* t1 = p1;
    struct Node* t2 = p2;

    while (t1 != NULL && t2 != NULL) {
        if (t1->pow > t2->pow) {
            insertAtEnd(&result, t1->coeff, t1->pow);
            t1 = t1->next;
        } else if (t1->pow < t2->pow) {
            insertAtEnd(&result, t2->coeff, t2->pow);
            t2 = t2->next;
        } else { // same power
            int sum = t1->coeff + t2->coeff;
            if (sum != 0) // only insert non-zero
                insertAtEnd(&result, sum, t1->pow);
            t1 = t1->next;
            t2 = t2->next;
        }
    }

    // Remaining terms
    while (t1 != NULL) {
        insertAtEnd(&result, t1->coeff, t1->pow);
        t1 = t1->next;
    }
    while (t2 != NULL) {
        insertAtEnd(&result, t2->coeff, t2->pow);
        t2 = t2->next;
    }

    return result;
}

// Traverse polynomial
void traversePoly(struct Node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->coeff >= 0 && temp != head) printf("+");
        printf("%dx%d ", temp->coeff, temp->pow);
        temp = temp->next;
    }
    printf("\n");
}

// Main function
int main() {
    int n1, n2, coeff, pow;

    printf("Enter number of terms in 1st polynomial: ");
    scanf("%d", &n1);
    printf("Enter terms (coeff pow) in descending order of power:\n");
    for (int i = 0; i < n1; i++) {
        scanf("%d %d", &coeff, &pow);
        insertAtEnd(&head1, coeff, pow);
    }

    printf("Enter number of terms in 2nd polynomial: ");
    scanf("%d", &n2);
    printf("Enter terms (coeff pow) in descending order of power:\n");
    for (int i = 0; i < n2; i++) {
        scanf("%d %d", &coeff, &pow);
        insertAtEnd(&head2, coeff, pow);
    }

    printf("1st Polynomial: ");
    traversePoly(head1);
    printf("2nd Polynomial: ");
    traversePoly(head2);

    struct Node* result = addPolynomials(head1, head2);
    printf("Sum of polynomials: ");
    traversePoly(result);

    return 0;
}
