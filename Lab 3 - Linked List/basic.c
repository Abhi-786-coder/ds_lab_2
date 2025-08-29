#include <stdio.h>
#include <stdlib.h>
// Structure for a node
struct Node
{
    int data;
    struct Node *next;
};
struct Node *head = NULL; // Global head pointer
// Function to create a new node
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (!newNode)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
// Insert at beginning
void insertAtBeginning(int data)
{
    struct Node *newNode = createNode(data);
    newNode->next = head;
    head = newNode;
}
// Insert at end
void insertAtEnd(int data)
{
    struct Node *newNode = createNode(data);
    if (head == NULL)
    {
        head = newNode;
        return;
    }
    struct Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}
// Insert at specific position
void insertAtPosition(int data, int pos)
{
    if (pos < 1)
    {
        printf("Invalid position!\n");
        return;
    }
    if (pos == 1)
    {
        insertAtBeginning(data);
        return;
    }
    struct Node *newNode = createNode(data);
    struct Node *temp = head;
    for (int i = 1; temp != NULL && i < pos - 1; i++)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("Position out of range!\n");
        free(newNode);
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}
// Delete from beginning
void deleteAtBeginning()
{
    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }
    struct Node *temp = head;
    head = head->next;
    printf("Deleted: %d\n", temp->data);
    free(temp);
}
// Delete from end
void deleteAtEnd()
{
    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }
    if (head->next == NULL)
    {
        printf("Deleted: %d\n", head->data);
        free(head);
        head = NULL;
        return;
    }
    struct Node *temp = head;
    struct Node *prev = NULL;
    while (temp->next != NULL)
    {
        prev = temp;
        temp = temp->next;
    }
    printf("Deleted: %d\n", temp->data);
    free(temp);
    prev->next = NULL;
}
// Delete from specific position
void deleteAtPosition(int pos)
{
    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }
    if (pos < 1)
    {
        printf("Invalid position!\n");
        return;
    }
    if (pos == 1)
    {
        deleteAtBeginning();
        return;
    }
    struct Node *temp = head;
    struct Node *prev = NULL;
    for (int i = 1; temp != NULL && i < pos; i++)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("Position out of range!\n");
        return;
    }
    prev->next = temp->next;
    printf("Deleted: %d\n", temp->data);
    free(temp);
}
// Traverse the list
void traverse()
{
    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }
    struct Node *temp = head;
    printf("Linked List: ");
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
// Main menu-driven function
int main()
{
    int choice, data, pos;
    while (1)
    {
        printf("\n--- Singly Linked List Menu ---\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Specific Position\n");
        printf("4. Delete at Beginning\n");
        printf("5. Delete at End\n");
        printf("6. Delete at Specific Position\n");
        printf("7. Traverse\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter data: ");
            scanf("%d", &data);
            insertAtBeginning(data);
            break;
        case 2:
            printf("Enter data: ");
            scanf("%d", &data);
            insertAtEnd(data);
            break;
        case 3:
            printf("Enter data: ");
            scanf("%d", &data);
            printf("Enter position: ");
            scanf("%d", &pos);
            insertAtPosition(data, pos);
            break;
        case 4:
            deleteAtBeginning();
            break;
        case 5:
            deleteAtEnd();
            break;
        case 6:
            printf("Enter position: ");
            scanf("%d", &pos);
            deleteAtPosition(pos);
            break;
        case 7:
            traverse();
            break;
        case 8:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}