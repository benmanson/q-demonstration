// Queue implementation as a linked list
//
// This program is intended to demonstrate how queues work and the basic operations that can be
// performed on them. It also demostrates what can be done with some basic C knowledge as it
//
// Ben Manson
// June 25 2019


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>           /* necessary for the delay function to make use of clock_t, CLOCKS_PER_SEC and clock() */

typedef struct elem {       /* structure for an element in the q in linked list form */
 int val;
 struct elem *nxt;
} elem;

elem *head;


/* delay function taken from https://c-for-dummies.com/blog/?p=69 */
void delay(int milliseconds)
{
    long pause;
    clock_t now, then;
    
    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while ( (now-then) < pause )
        now = clock();
}

void insertq(elem *qhead, int value)
{
    elem *new;                          /* create a pointer to a new elem i.e. what is to be inserted */
    new = malloc(sizeof(elem));         /* dynamically allocate memory for this elem */
    new->val = value;                   /* store the insertion value into this elem */
    new->nxt = NULL;                    /* make this new elem point to the next elem (NULL at this stage) */
    
    /* loop over the queue until we find the last elem, where the next points to NULL */
    while (qhead->nxt)
    {
        qhead = qhead->nxt;
    }
    
    /* make the previous last elem point to the new last elem (which points to NULL) */
    qhead->nxt = new;
    
    printf("\nSuccessfully added %d to the queue\n", value);
}


void removeq(elem *qhead, int size)
{
    /* if the queue only contains the head then we cannot delete it in this version */
    if (size == 1) {
        printf("\nError: you cannot delete the first element if it is the only element. Try another command or quit and start over");
    } else {
        
        head = qhead->nxt;
        
        free(qhead);                        /* free memory allocated for qhead to prevent memory leaking */
        
        printf("\nSuccessfully removed %d from queue\n", qhead->val);
    }
}

int sizeq(elem *qhead)
{
    int size = 1;                       /* int to keep track of size */
    
    /* while we are still in q */
    while (qhead->nxt)
    {
        size++;                         /* increment size */
        qhead = qhead->nxt;             /* move forward in q */
    }
    
    return size;                        /* return size */
}

void searchq(elem *qhead, int value)
{
    /* while we haven't found the first instance of search value and have not reached the end of the q */
    while (qhead->val != value && qhead->nxt)
    {
        qhead = qhead->nxt;             /* move forward in search */
    }
    
    if (qhead->val == value) {
        printf("\n%d found at %p\n", value, qhead);
    } else {
        printf("\nNot found\n");
    }
    
}

void printq(elem *qhead)
{
    printf("\n");
    while (qhead->nxt)
    {
        printf("Value: %d at %p.   Next Address: %p\n", qhead->val, qhead, qhead->nxt);
        qhead = qhead->nxt;
    }
    
    printf("Value: %d at %p.   (Final item)\n", qhead->val, qhead);
    
}

void illustrateq(elem *qhead)
{
    printf("\nValue    |   Next address");                      /* print column headers */
    
    while (qhead->nxt)
    {
        delay(2000);                                            /* wait 2000 milliseconds (2 seconds) before proceeding */
        printf("\n%d        |   %p", qhead->val, qhead->nxt);   /* print the value in the q and the next address */
        qhead = qhead->nxt;                                     /* move forward in the q */
    }
    
    printf("\n%d        |   NULL", qhead->val);                 /* print the final value in the q */
}

void helpq(char option[]) {
    if ((strcmp(option, "insert")) == 0)
    {
        printf("\n\nThe command insert followed by the value to be inserted will insert the value at the end of the queue. This is equivalent to enqueue for users familiar with the queue structure. Format: insert [val] (where val is replaced by value to be inserted)\n");
        
    } else if ((strcmp(option, "remove")) == 0) {
        printf("\n\nThe command remove will remove the value at the front of the queue. This is equivalent to dequeue for users familiar with the queue structure. Format: remove\n");
        
    } else if ((strcmp(option, "search")) == 0) {
        printf("\n\nSearch followed by the value to be searched for in the queue will return the address in memory that said item is stored in in the queue. Format: search [val] (where val is the value to be searched for)\n");
        
    } else if ((strcmp(option, "print")) == 0) {
        printf("\n\nWill print the queue. Format: print\n");
        
    } else if ((strcmp(option, "illustrate")) == 0) {
        printf("\n\nWill print the queue, one element at a time. Format: illustrate\n");
        
    } else if ((strcmp(option, "quit")) == 0) {
        printf("\n\nQuits the program. Format: illustrate\n");
        
    } else {
        printf("\n\nThat is not a command.\n");
        
    }
}

/* main is a basic function to allow the user to interface with the q */
int main(void)
{
    char option[10];
    char command[10];
    int insert;
    int search;
    int size;
    
    head = malloc(sizeof(elem));
    head->nxt = NULL;
    
    printf("Enter value for head of queue: ");
    scanf("%d", &head->val);
    
    while (1)
    {
        printf("\nWhat would you like to do with the queue? (insert [VALUE]/remove/search [VALUE]/print/illustrate/help [COMMAND]/quit)\n");
        scanf("%s", option);
        
        if ((strcmp(option, "insert")) == 0)
        {
            scanf("%d", &insert);
            
            insertq(head, insert);
        } else if ((strcmp(option, "remove")) == 0) {
            size = sizeq(head);
            
            removeq(head, size);
        } else if ((strcmp(option, "search")) == 0) {
            scanf("%d", &search);
            
            searchq(head, search);
        } else if ((strcmp(option, "print")) == 0) {
            printq(head);
        } else if ((strcmp(option, "illustrate")) == 0) {
            illustrateq(head);
        } else if ((strcmp(option, "quit")) == 0) {
            printf("\n\nQuitting...\n");
            break;
        } else if ((strcmp(option, "help")) == 0) {
            scanf("%s", command);
            
            helpq(command);
        } else {
            printf("\n\nNot an option, quitting...\n");
            break;
        }
    }
    
    printf("\nFinal queue:\n");
    printq(head);
    
    return 0;
}
