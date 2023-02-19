#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

/*In C programming, a struct (short for structure) is a user-defined data type that allows
 you to combine different data types into a single unit. A struct can contain variables, arrays, 
 and other structures as its members.*/

struct node {
    int id;
    struct node *link;
}; typedef struct node linked_list;

struct pcb {
    int parent;
    linked_list *children;
}; typedef struct pcb pcb_type;
pcb_type *pcb_array[MAX_PROCESSES]; // array of pcb_type ptrs

/* Define structures and global constants, including:
the pcb type, the children linked list type, the maximum number of processes*/
/***************************************************************/

void HierarchyPrint() {
    /* declare local vars */
    int i;
    linked_list* current_child;
    /* for each process index i from 0 up to (but not including) maximum number of processes*/
    printf("Process List:\n");
    for (i=0; i< (MAX_PROCESSES); i++){
        /* if PCB[i] is not NULL */
        if (pcb_array[i] != NULL) {
            /* print process id, parent id, list of children processes */
            printf("Process id: %d\n", i);
            printf("\tParent process: %d\n", pcb_array[i]->parent);
            //children
            current_child = pcb_array[i]->children;
            while (current_child != NULL) {
                printf("\tChild process: %d\n", current_child->id);
                current_child = current_child->link;
            }
        }
    }
} /* end of procedure */
/***************************************************************/

void Initialize() {
    /* declare local vars */
    int i;

    /* Allocate memory for PCB[0] */
    // MALLOC is a standard library function in the C programming language that is used
    //to dynamically allocate a block of memory in the heap. It stands for "memory allocation.//

    pcb_array[0] = (pcb_type *)malloc(sizeof(pcb_type));
    pcb_array[0]->parent = 0;
    pcb_array[0]->children = NULL;

    /* Intitialize all other PCB's to NULL */
    for( i=1; i<MAX_PROCESSES; i++) {
        pcb_array[i] = NULL;
    }
    /* print hierarchy of processes */
    HierarchyPrint();
    return;
} /* end of procedure */
/***************************************************************/

void CreateNewChild() {
    /* define local vars */
    int p, q=1;
    /* prompt for parent process index p */
    printf("Enter the parent process id: \n");
    scanf("%d", &p);
    pcb_type *parent = pcb_array[p];
    /* if PCB[p] is NULL, print message process does not exist, return */
    if (parent == NULL) {
        printf("\nProcess does not exist.\n\n");
        return;
    }
    /* search for first available index q without a parent in a while loop */
    while ((q < MAX_PROCESSES) && (pcb_array[q] != NULL)) {
        q++;
    }
    /* if maximum number of processes reached, print message of no more available PCBs */
    if (q == MAX_PROCESSES) {
        printf("Number of processes has reached its limit. Purge them!!");
    }
    /* allocate memory for new child process & linked list*/
    /* initialize fields */
    pcb_type *pcb_pointer = (pcb_type*)malloc(sizeof(pcb_type)); // allocating memory for one pcb_type.
    linked_list  *new_child_node = (linked_list*) malloc(sizeof(linked_list)*1);
    
    /* record the parent's index p in PCB[q] */
    /* Initialize the list of children of PCB[q] as empty */

    pcb_array[q] = pcb_pointer; // pointing to first element in allocated memory
    pcb_array[q]->children = NULL;
    pcb_array[q]->parent = p;

    if (pcb_array[p]->children == NULL) {
        /* append the node containing the child's index q to the children linked list of PCB[p] */
        pcb_array[p]->children = new_child_node;
        pcb_array[p]->children->link = NULL;
        pcb_array[p]->children->id = q;
        /* print hierarchy of processes */
        HierarchyPrint();
        return;
    } else {
        linked_list* current_child;
        current_child = pcb_array[p]->children;

        while (current_child->link != NULL) {
            current_child = current_child->link;
        }
        // setting id
        /* append the node containing the child's index q to the children linked list of PCB[p] */
        current_child->link = new_child_node;
        current_child->link->id = q;
        current_child->link->link = NULL;
        /* print hierarchy of processes */
        HierarchyPrint();
    }
    return;
} /* end of procedure */
/***************************************************************/
void DestroyChildren(linked_list *node) {
    /* declare local vars */
    int q;
    /* check if end of linked list--if so return */
    if (node == NULL) {
        return;
    }
    /* else call self on link node in linked list */
    DestroyChildren(node->link);
    /* set variable q to current node's process index field */
    q = node->id;
    /* call self on children of PCB[q] */
    DestroyChildren(pcb_array[q]->children);
    /* free memory of PCB[q] and set PCB[q] to NULL*/
    free(pcb_array[q]);
    pcb_array[q] = NULL;
    /* free memory of parameter and set to NULL */
    free(node);
    node = NULL;
    return;
} /* end of procedure */

/***************************************************************/
void EliminateDescendants() {
    /* declare local vars */
    /* prompt for process index p */
    int p;
    int q=1;
    printf("Input parent process, whose offspring are to be eliminated:");
    scanf("%d", &p);
    pcb_type *parent = pcb_array[p];
    if (parent == NULL) {
        printf("\nProcess does not exist.\n\n");
        return;
    }
    /* call recursive procedure to destroy children of PCB[p] */
    DestroyChildren(pcb_array[p]->children);
    /* reset children of PCB[p] to NULL */
    pcb_array[p]->children = NULL;
    /* print hierarchy of processes */
    HierarchyPrint();
    return;
} /* end of procedure */

/***************************************************************/

int main() {
    int select = 0;
    	/* while user has not chosen to quit */
    while (select != 4) {
        /* print menu of options */

        printf("Process creation and destruction\n");
        printf("--------------------------------\n");
        printf("1) Initialize process hierarchy.\n");
        printf("2) Create a new child process.\n");
        printf("3) Destroy all descendants of a parent process.\n");
        printf("4) Quit program and free memory.\n");

        scanf("%d", &select);
        /* call appropriate procedure based on choice--use switch statement or series of if, else if, else statements */	

        switch (select) {
            case 1:
                printf("\nEnter selection: %d\n", select);
                Initialize();
                break;
            case 2:
                printf("\nEnter selection: %d\n", select);
                CreateNewChild();
                break;
            case 3:
                printf("\nEnter selection: %d\n", select);
                EliminateDescendants();
                break;
            case 4:
                printf("\nEnter selection: %d\n", select);
                break;

            default: printf("Invalid option \n"); 
        }
    }
    return 0;
}