
/*!
* \file memoryList.c
* \brief File with the functions required to manage the list of allocated blocks as studied in the leak detector lab
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memoryList.h"

#include <stdint.h>

#include "myFunctions.h"


/*!
* \brief Free memory stored in a  MemoryBlock
* \param[in] b the address of the block structure to be freed.
*/
static void freeMemoryBlock(MemoryBlock *b)
{
    if(b->file != NULL)
        free((void*) b->file);
    if(b->function != NULL)
        free((void*) b->function);

    b->file = b->function = NULL;
}

static void freeNodeList(NodeList * n) {
    free((void*)n);
}


/*!
* \brief Initialize data for a memory block
* \param[in] b the address of the block structure to be initialized. 
* \param[in] f the filename
* \param[in] fn the function name
* \param[in] l the line number
* \param[in] a the address of the allocated block
* \return MemoryBlock* the address of the initialised structure
*/
static MemoryBlock * initMemoryBlock(MemoryBlock *b,const char *f,  const char * fn, int l, void * a)
{
    b->file = (char *)malloc(strlen(f)+1);
    b->function = (char *)malloc(strlen(fn)+1);
    if(b->file != NULL && b->function !=NULL)
    {
        strcpy(b->file,f);
        strcpy(b->function,fn);
        b->line = l;
        b->address = a;
    }
    else
	{
            freeMemoryBlock(b);
            return NULL;
	}
       	    
    return b;
}

static NodeList * newNodeList(const char * file, const char * function, int l, void * a, NodeList * next, NodeList * prev) {
    NodeList * newNode = (NodeList *)malloc(sizeof(NodeList));
    if (newNode==NULL) {
        fprintf(stderr,"Memory allocation error\n");
        return NULL;
    }
    if (initMemoryBlock(&newNode->b,file,function,l,a)==NULL) {
        freeNodeList(newNode);
        return NULL;
    }

    newNode->next = next;
    newNode->previous = prev;

    return newNode;
}

void initList(List * l) {
    if(l != NULL) {
        l->sentinel_begin.next = &(l->sentinel_end);
        l->sentinel_begin.previous = NULL;
        l->sentinel_end.previous = &(l->sentinel_begin);
        l->sentinel_end.next = NULL;
        l->current = &(l->sentinel_begin);
    }
}

int isEmpty(List *l) {
    if (l->sentinel_begin.next == &(l->sentinel_end) || l == NULL) {
        return 1;
    }
    return 0;
}

int isFirst(List *l) {
    if (isEmpty(l) || l->current == NULL) return 0;
    return (l->current == l->sentinel_begin.next);
}

int isLast(List *l) {
    if (l == NULL || l->current == NULL) return 0;
    return (l->current == l->sentinel_end.previous);
}

int isOutOfList(List *l) {
    if (isEmpty(l) || l->current == &(l->sentinel_begin) || l->current == &(l->sentinel_end)) {
        return 1;
    }
    return 0;
}

void setOnFirst(List *l) {
    if (isEmpty(l)) return;
    l->current = l->sentinel_begin.next;
}

void setOnLast(List *l) {
    l->current = l->sentinel_end.previous;
}

void setOnNext(List *l) {
    if (l == NULL || l->current == NULL || l->current == &(l->sentinel_end)) return;
    l->current = l->current->next;
}

void setOnPrevious(List *l) {
    l->current = l->current->previous;
}

void * getCurrentAdress(List * l) {
    if (isEmpty(l) || isOutOfList(l)) return NULL;
    return l->current->b.address;
}

void printList(List * l) {
    if (l == NULL || isEmpty(l)) {
        return;
    }

    NodeList *temp = l->sentinel_begin.next;  // Use temporary pointer
    while (temp != &(l->sentinel_end)) {
        printf("File : %s\n", temp->b.file);
        printf("Function : %s\n", temp->b.function);
        printf("line : %d\n", temp->b.line);
        temp = temp->next;
    }
}

int countElements(List * l) {
    if (!isEmpty(l)) {
        int count = 0;
        setOnFirst(l);
        while (!isOutOfList(l)) {
            count ++;
            setOnNext(l);
        }
        return count;
    }
    fprintf(stderr, "List is empty.\n");
    return 0;
}

int insertSort(List * l, const char * file, const char * function, int line, void * address) {
    if ( file == NULL || function == NULL || address == NULL) {
        return 0;  // Return 0 when any parameter is NULL
    }
    NodeList * toInsert = newNodeList(file,function,line,address,NULL,NULL);
    if (toInsert == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return 0;
    }

    if (isEmpty(l)) {
        toInsert->next = &(l->sentinel_end);
        toInsert->previous = &(l->sentinel_begin);
        l->sentinel_begin.next = toInsert;
        l->sentinel_end.previous = toInsert;
        return 1;
    }

    NodeList * current = l->sentinel_begin.next;
    // Change this to check current directly against sentinel_end
    while (current != &(l->sentinel_end)) {
        if (strcmp(current->b.file, toInsert->b.file) < 0
            || (strcmp(current->b.file, toInsert->b.file) == 0 && strcmp(current->b.function, toInsert->b.function) < 0)) {
            break;
            }
        current = current->next;
    }

    toInsert->next = current;
    toInsert->previous = current->previous;
    current->previous->next = toInsert;
    current->previous = toInsert;
    return 1;
}

int find(List * l, void * address) {
    if (l == NULL || address == NULL || isEmpty(l)) {
        return 0;
    }

    NodeList *temp = l->sentinel_begin.next;
    while (temp != &(l->sentinel_end)) {
        if (temp->b.address == address) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void * deleteValue(List *l, void * address) {
    if (l == NULL || address == NULL || isEmpty(l)) {
        return NULL;
    }

    NodeList *temp = l->sentinel_begin.next;
    while (temp != &(l->sentinel_end)) {
        if (temp->b.address == address) {
            void *deletedAddress = temp->b.address;

            // Fix links
            temp->previous->next = temp->next;
            temp->next->previous = temp->previous;

            // Update current pointer if needed
            if (l->current == temp) {
                l->current = temp->next;
            }

            // Free memory
            freeMemoryBlock(&temp->b);
            free(temp);

            return deletedAddress;
        }
        temp = temp->next;
    }
    return NULL;
}

int insertSortGeneric(List * l, const char *f, const char * fn, int ln, void * a, int (*comp)(void *, void *)) {
    // Parameter validation
    if (l == NULL) {
        return 0;
    }
    if (f == NULL || fn == NULL || a == NULL || comp == NULL) {
        return 0;
    }

    NodeList * toInsert = newNodeList(f, fn, ln, a, NULL, NULL);
    if (toInsert == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return 0;
    }

    if (isEmpty(l)) {
        toInsert->next = &(l->sentinel_end);
        toInsert->previous = &(l->sentinel_begin);
        l->sentinel_begin.next = toInsert;
        l->sentinel_end.previous = toInsert;
        return 1;
    }

    NodeList * current = l->sentinel_begin.next;
    while (current != &(l->sentinel_end)) {
        // Use the comparison function instead of direct strcmp
        if (comp(current->b.address, toInsert->b.address) > 0) {
            break;
        }
        current = current->next;
    }

    // Insert the node
    toInsert->next = current;
    toInsert->previous = current->previous;
    current->previous->next = toInsert;
    current->previous = toInsert;
    return 1;
}

#include "test.h"
void test_list()
{
    List l1;
    int ret1;
    void* addr1 = malloc(sizeof(int));
    void* addr2 = malloc(sizeof(char) * 10);
    void* addr3 = malloc(sizeof(int));

    printf("Unit tests on the list module\n");

    /*group 1*/

    initList(&l1);
    display_test_int("Test isEmpty() on an empty list",1,isEmpty(&l1));
    display_test_int("Test isOutOfList() when the list is empty",1,isOutOfList(&l1));
    display_test_string("Test getCurrentAdress() when the list is empty",NULL,getCurrentAdress(&l1));
    display_test_check_by_user("Test printList on an isEmpty list");
    printList(&l1);

    /* group 2 : insertion */
    ret1 = insertSort(&l1, "test.c", "main", 10, addr1);
    display_test_int("Test insertSort() on an empty list", 1, ret1);

    ret1 = insertSort(&l1, "test.c", "function2", 20, addr2);
    display_test_int("Test insertSort() on a non-empty list", 1, ret1);

    ret1 = insertSort(&l1, "test.c", "function3", 30, addr3);
    display_test_int("Test insertSort() on a non-empty list", 1, ret1);

    display_test_check_by_user("Test insertSort: (list should show three entries sorted by file/function)");
    printList(&l1);
    display_test_int("Test isEmpty() on a non-empty list", 0, isEmpty(&l1));

    /* group 3: Navigation */
    setOnFirst(&l1);
    display_test_int("Test isFirst() when setOnFirst", 1, isFirst(&l1));
    display_test_int("Test isLast() when not on last", 0, isLast(&l1));
    display_test_int("Test isOutOfList() when in the list", 0, isOutOfList(&l1));

    setOnNext(&l1);
    display_test_int("Test setOnNext() navigation", 0, isOutOfList(&l1));

    setOnLast(&l1);
    display_test_int("Test isLast() when setOnLast", 1, isLast(&l1));

    /* Test Group 4: Search and Count */
    display_test_int("Test find() with existing address", 1, find(&l1, addr1));
    display_test_int("Test find() with non-existing address", 0, find(&l1, NULL));
    display_test_int("Test countElements()", 3, countElements(&l1));

    /* Test Group 5: Deletion */
    void* deleted_addr = deleteValue(&l1, addr1);
    display_test_int("Test deleteValue() returns correct address", 1, (deleted_addr == addr1));
    display_test_int("Test countElements() after deletion", 2, countElements(&l1));

    deleted_addr = deleteValue(&l1, addr2);
    display_test_int("Test deleteValue() of last element", 1, (deleted_addr == addr2));
    display_test_int("Test isEmpty() after all elements deleted", 0, isEmpty(&l1));

    deleted_addr = deleteValue(&l1, addr3);
    display_test_int("Test deleteValue() of last element", 1, (deleted_addr == addr3));
    display_test_int("Test isEmpty() after all elements deleted", 1, isEmpty(&l1));

    /* Test Group 6: Error Cases */
    ret1 = insertSort(&l1, NULL, "function", 10, addr1);
    display_test_int("Test insertSort() with NULL filename", 0, ret1);

    deleted_addr = deleteValue(&l1, addr1);
    display_test_int("Test deleteValue() on empty list returns NULL", 1, (deleted_addr == NULL));

    // Clean up allocated memory
    free(addr1);
    free(addr2);
    free(addr3);
}

void test_generic_sort() {
    List l1;
    int ret1;

    // Comparison function that sorts by address value


    printf("\nTesting Generic Sort Function\n");
    printf("-----------------------------\n");

    // Initialize list and test data
    initList(&l1);
    void* addr1 = malloc(sizeof(int));
    void* addr2 = malloc(sizeof(int));
    void* addr3 = malloc(sizeof(int));

    // Test Group 1: Basic insertion with address comparison
    printf("\nTest Group 1: Basic insertion with address comparison\n");
    ret1 = insertSortGeneric(&l1, "test1.c", "func1", 10, addr1, compare_by_address);
    display_test_int("Test insertSortGeneric() on empty list", 1, ret1);

    ret1 = insertSortGeneric(&l1, "test2.c", "func2", 20, addr2, compare_by_address);
    display_test_int("Test insertSortGeneric() with second element", 1, ret1);

    ret1 = insertSortGeneric(&l1, "test3.c", "func3", 30, addr3, compare_by_address);
    display_test_int("Test insertSortGeneric() with third element", 1, ret1);

    display_test_int("Test list size after insertions", 3, countElements(&l1));

    // Test Group 2: Verify order
    printf("\nTest Group 2: Verify order\n");
    setOnFirst(&l1);
    NodeList* current = l1.current;
    int ordered = 1;
    while (current->next != &(l1.sentinel_end)) {
        if (compare_by_address(current->b.address, current->next->b.address) > 0) {
            ordered = 0;
            break;
        }
        current = current->next;
    }
    display_test_int("Test if list is properly ordered", 1, ordered);

    // Test Group 3: Clear and test reverse order
    printf("\nTest Group 3: Test reverse order comparison\n");
    // Clear the list first
    while (!isEmpty(&l1)) {
        deleteValue(&l1, l1.sentinel_begin.next->b.address);
    }

    // Insert with reverse comparison
    ret1 = insertSortGeneric(&l1, "test1.c", "func1", 10, addr1, compare_reverse);
    ret1 &= insertSortGeneric(&l1, "test2.c", "func2", 20, addr2, compare_reverse);
    ret1 &= insertSortGeneric(&l1, "test3.c", "func3", 30, addr3, compare_reverse);

    display_test_int("Test reverse insertion success", 1, ret1);

    // Verify reverse order
    setOnFirst(&l1);
    current = l1.current;
    ordered = 1;
    while (current->next != &(l1.sentinel_end)) {
        if (compare_reverse(current->b.address, current->next->b.address) > 0) {
            ordered = 0;
            break;
        }
        current = current->next;
    }
    display_test_int("Test if list is properly reverse ordered", 1, ordered);

    // Clean up
    while (!isEmpty(&l1)) {
        deleteValue(&l1, l1.sentinel_begin.next->b.address);
    }
    free(addr1);
    free(addr2);
    free(addr3);

    printf("\nGeneric Sort Tests Completed\n");
}
