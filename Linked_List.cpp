#include <stdio.h>//* Standard input-output header file */
#include <stdlib.h>//* Standard library header file for memory allocation */

//* Definition of the element type */
typedef int ELemType;  

//* Definition of the status type */
typedef int Status;  

//* Definition of the node structure */
typedef struct LNode{  
    ELemType data;
    struct LNode *next;//* Pointer to the next node */
}LNode, *LinkList;  //* Definition of the linked list type (LNode *==LinkList)*/

//* Function to create an empty linked list */
LinkList CreateList(){
    LinkList L;
    L = (LinkList)malloc(sizeof(LNode)); //* Create head node */
    L->data = 0;  //* Initialize data field of head node */
    L->next = NULL;  //* Initialize the next pointer of head node to NULL */
    return L;  //* Return the head of the linked list */
}

//* Function to create a linked list using head insertion method */
LNode* CreateList_Head(int n,LNode *L){
    for(int i = 0; i < n; i++){
        LNode *p = (LNode *)malloc(sizeof(LNode)); //* Create a new node */
        scanf("%d", &p->data);  //* Input data for the new node */
        p->next = L->next;  //* New node points to the current first node */
        L->next = p;  //* Head node points to the new node */
        L->data++;  //* Increment the count of nodes */
    }
    return L;  //* Return the head of the linked list */
}

//* Function to create a linked list using tail insertion method */
LNode* CreateList_Tail(int n,LNode *L){
    LNode *r = L;  //* r points to the tail node, initially the head node */
    for(int i = 0; i < n; i++){
        LNode *p = (LNode *)malloc(sizeof(LNode));  //* Create a new node */
        scanf("%d", &p->data);  //* Input data for the new node */
        r->next = p;  //* Tail node points to the new node */
        r = p;  //* Update tail pointer to the new node */
        L->data++;  //* Increment the count of nodes */
    }
    r->next = NULL;  //* Set the next pointer of the last node to NULL */
    return L;  //* Return the head of the linked list */
}

//* Function to print the linked list */
void PrintList(LNode *L){
    LNode *p = L->next;  //* Start from the first node */
    while(p != NULL){
        printf("%d ", p->data);  //* Print the data of the current node */
        p = p->next;  //* Move to the next node */
    }
    printf("\n");  //* Print a newline at the end */
}   

//* Function to find the element at index i (1-based) */
Status find(LinkList L, int i, ELemType *e){
    if(i < 1 || i > L->data) {
        return 0;  //* Check if index is valid */
    }
    LNode *p = L->next;  //* Start from the first node */
    int j = 1;  //* Initialize index counter */
    while(j < i){//* Traverse to the ith node */
        p = p->next;  //* Move to the next node */
        j++;  //* Increment index counter */
    }//* After the loop, p points to the ith node */
    *e = p->data;  //* Retrieve the data at index i */
    return 1;  //* Return success status */
}

//* Function to insert an element after the nth node (1-based) */
void insertAfterNth(LinkList L, int n, ELemType e){
    if(n < 1 || n > L->data) {
        printf("Index out of bounds\n");
        return;  //* Check if index is valid */
    }
    LNode *p = L;  //* Start from the head node */
    int j = 0;  //* Initialize index counter */
    while(j < n){
        p = p->next;  //* Move to the next node */
        j++;  //* Increment index counter */
    }
    LNode *newNode = (LNode *)malloc(sizeof(LNode));  //* Create a new node */
    newNode->data = e;  //* Set the data of the new node */
    newNode->next = p->next;  //* New node points to the next node */
    p->next = newNode;  //* Current node points to the new node */
    L->data++;  //* Increment the count of nodes */
}

//* Function to delete the ith node (1-based) */
void Listdelete(LinkList L, int i){
    if(i < 1 || i > L->data) {
        printf("Index out of bounds\n");
        return;  //* Check if index is valid */
    }
    LNode *p = L;  //* Start from the head node */
    int j = 0;  //* Initialize index counter */
    while(j < i - 1){
        p = p->next;  //* Move to the next node */
        j++;  //* Increment index counter */
    }
    LNode *toDelete = p->next;  //* Node to be deleted */
    p->next = toDelete->next;  //* Bypass the node to be deleted */
    free(toDelete);  //* Free the memory of the deleted node */
    L->data--;  //* Decrement the count of nodes */
}

//* Main function to demonstrate linked list operations */
int main(){

    //* Variables declaration */
    int n,i,choice;
    ELemType e;

    //* Create linked lists using head and tail insertion */

    printf("To show the difference in input order between head insertion and tail insertion");
    printf("\nL1:Enter number of elements to insert using head insertion: ");
    scanf("%d", &n);//* Input number of elements */

    //* Create linked list using head insertion */
    LinkList L1 = CreateList();  //* Create an empty linked list */
    L1 = CreateList_Head(n, L1);  //* Create linked list using head insertion */
    printf("L1:Linked list after head insertion: ");
    PrintList(L1);  //* Print the linked list */

    //* Create linked list using tail insertion */
    LinkList L2 =CreateList();//* Create an empty linked list */
    printf("L2:Enter number of elements to insert using tail insertion: ");
    scanf("%d", &n);//* Input number of elements */
    L2 = CreateList_Tail(n, L2);  //* Create linked list using tail insertion */
    printf("L2:Linked list after tail insertion: ");
    PrintList(L2);  //* Print the linked list */
    
    //* Choose which linked list to operate on */
    printf("Choose a list (1 or 2)");
    scanf("%d",&choice);
    LinkList L =CreateList();
    if (choice==1){//* if L1 is chosen */
        L=L1;// * set L to L1 */
    }else{//* if L2 is chosen */
        L=L2;// * set L to L2 */
    }

    //* Find element at index i */
    printf("Enter index to find (1-based): ");
    scanf("%d", &i);//* Input index */
    if(find(L, i, &e)){
        printf("Element at index %d: %d\n", i, e);//* Print the found element */
    } else {
        printf("Index %d is out of bounds.\n", i);//* Print out of bounds message */
    }
    
    //* Insert element after nth node */
    printf("Enter index to insert after (1-based) and element to insert: ");
    scanf("%d %d", &i, &e);//* Input index and element */
    insertAfterNth(L, i, e);  //* Insert element after nth node */
    printf("Linked list after insertion: ");
    PrintList(L);  //* Print the linked list */

    //* Delete ith node */
    printf("Enter index to delete (1-based): ");
    scanf("%d", &i);//* Input index */
    Listdelete(L, i);  //* Delete ith node */
    printf("Linked list after deletion: ");
    PrintList(L);  //* Print the linked list */

    //* Print the other linked list */
    printf("Printing the other list \n");//* Print the other linked list */
    if (choice==1){//* if L1 was chosen */
        PrintList(L2);//* print L2 */
    }else{//* if L2 was chosen */
        PrintList(L1);//* print L1 */
    }  

    //* End of main function */
    return 0;  //* End of program */
}
