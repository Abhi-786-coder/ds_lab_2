#include <stdio.h>
    #include <stdlib.h>

    struct Node {
        int data;
        struct Node* next;
        struct Node* prev;
   };

    struct Node* newNode(int data) {
        struct Node* node = (struct Node*)malloc(sizeof(struct Node));
        node->data = data;
        node->next = NULL;
        node->prev = NULL;
        return node;
    }


    struct Node* insertEnd(struct Node* head, int data) {
        struct Node* node = newNode(data);
        if (head == NULL) {
            return node;
        }
        struct Node* temp = head;
        while (temp->next != NULL) { 
            temp = temp->next;
        }
        temp->next = node;
        node->prev = temp;
        return head;
    }


    struct Node* sortDLL(struct Node* head) {
        if (head == NULL || head->next == NULL) return head;
        struct Node* i = head;
        while (i != NULL) {
            struct Node* j = i->next;
            while (j != NULL) {
                if (i->data > j->data) {
                    int temp = i->data;
                    i->data = j->data;
                    j->data = temp;
                }
                j = j->next;
            }
            i = i->next;
        }
        return head;
    }


    struct Node* mergeSortedDLL(struct Node* head1, struct Node* head2) {
        struct Node* head3 = NULL;

        while (head1 != NULL && head2 != NULL) {
            if (head1->data < head2->data) {
                head3 = insertEnd(head3, head1->data);
                head1 = head1->next;
            } else {
                head3 = insertEnd(head3, head2->data);
                head2 = head2->next;
            }
        }
        while (head1 != NULL) {
            head3 = insertEnd(head3, head1->data);
            head1 = head1->next;
        }
        while (head2 != NULL) {
            head3 = insertEnd(head3, head2->data);
            head2 = head2->next;
        }
        return head3;
    }


    struct Node* sortedInsert(struct Node* head, int data) {
        struct Node* node = newNode(data);
        if (!head) return node;

        if (data <= head->data) {
            node->next = head;
            head->prev = node;
            return node;
        }

        struct Node* temp = head;
        while (temp->next && temp->next->data < data) {
            temp = temp->next;
        }

        node->next = temp->next;
        if (temp->next) temp->next->prev = node;
        temp->next = node;
        node->prev = temp;

        return head;
    }


    void printForward(struct Node* head) {
        while (head) {
            printf("%d ", head->data);
            head = head->next;
        }
        printf("\n");
    }

    int main() {
        struct Node* l1 = NULL;
        struct Node* l2 = NULL;
        int n1, n2, val;

        printf("Enter number of elements in List1: ");
        scanf("%d", &n1);
        printf("Enter %d elements: ", n1);
        for (int i = 0; i < n1; i++) {
            scanf("%d", &val);
            l1 = insertEnd(l1, val);
        }

        printf("Enter number of elements in List2: ");
        scanf("%d", &n2);
        printf("Enter %d elements: ", n2);
        for (int i = 0; i < n2; i++) {
            scanf("%d", &val);
            l2 = insertEnd(l2, val);
        }

        l1 = sortDLL(l1);
        l2 = sortDLL(l2);

        struct Node* merged = mergeSortedDLL(l1, l2);

        printf("Merged List: ");
        printForward(merged);

        printf("Enter value to insert into merged list: ");
        scanf("%d", &val);
        merged = sortedInsert(merged, val);

        printf("Updated merged list: ");
        printForward(merged);

        return 0;
}