
/*!
* \file list.c
* \brief File with the functions required to manage the list as studied in labs 6 and 7
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listMO.h"


/*!
* \brief Allocate memory for the data element and initialize the structure members
* \param[in] name the name of the multimedia object
* \param[in] path the path of the multimedia object
* \param[in] day the day of creation of the multimedia object
* \param[in] month the  month of creation  of the multimedia object
* \param[in] year the  year of creation  of the multimedia object
* \param[in] type the type of the multimedia object
* \param[in] n the address of the setOnNext data element
* \return NodeList* the address of the new data element
*/
static NodeList *newNodeList(char * name, char * path, int day, int month, int year, TypeMultimediaObject type, NodeList * n)
{
    NodeList *newNL = (NodeList *) malloc(sizeof(NodeList));
    if(newNL != NULL)
    {
        fillMO(&(newNL->value),name,path,day,month,year,type);
        newNL->next = n;
    }
    else
        fprintf(stderr,"Erreur d'allocation memoire dans newNodeList()\n");
    return newNL;
}


/*!
* \brief Desallocate memory associated to a node
* \param[in] n the address of the  data element to be freed
*/
static void freeNodeList(NodeList *n)
{
  free((void *)n);
}

void initList(List * l){
  l->first = l->last = l->current = NULL;
}

int isEmpty(List * l){
  return l->first == NULL;
}

int insertFirst(List * l, char * name, char * path, int day, int month, int year, TypeMultimediaObject type){
  if(!isEmpty(l)){
    NodeList * new_node = newNodeList(name,path,day,month,year,type,l->first);  //l->first is the adresse of setOnNext
    l->first = new_node;
    return new_node != NULL;
  }
  else{
    List * new_l = (List *) malloc(sizeof(List));
    initList(new_l);
    NodeList * new_node = newNodeList(name,path,day,month,year,type,NULL);
    l->first = l->last = l->current = new_node;
    return new_node != NULL;
  }

}

int isFirst(List * l){
  return l->current == l->first;
}

int isLast(List * l){
  return l->current == l->last;
}

int isOutOfList(List * l){
  return l->current == NULL;
}

char * getCurrentName (List * l){
  if (isEmpty(l)|| isOutOfList(l)) {
    return NULL;
  }
  return l->current->value.name;
}

char * getCurrentPath (List * l){
  if (isEmpty(l) || isOutOfList(l)) {
    return NULL;
  }
  return l->current->value.path;
}

Date getCurrentDate (List * l){
  Date emptyDate = {0,0,0};
  if (isEmpty(l) || isOutOfList(l)) {
    return emptyDate;
  }
  return l->current->value.date;
}

TypeMultimediaObject getCurrentType (List * l){
  if (isEmpty(l) || isOutOfList(l)) {
    return -1; //Type va de 0 a 2
  }
  return l->current->value.type;
}

void setOnFirst(List * l){
  l->current = l->first;
}

void setOnLast(List * l){
  l->current = l->last;
}

void setOnNext (List * l){
  if ( (l != NULL) && (l->current != NULL) ){
    l->current = l->current->next;
  }
}

void printList(List * l){
  if(!isEmpty(l)){
    setOnFirst(l);
    while(!isOutOfList(l)){
      displayConsoleOM(&(l->current->value));
      printf("-----------------------\n");
      setOnNext(l);
    }
  }
  else{
    fprintf(stderr,"List empty cannot be printed\n");
  }
}

int nbElement(List * l){
  int nbElement = 0;
  if(!isEmpty(l)){
    setOnFirst(l);
    while(!isOutOfList(l)){
      nbElement ++;
      setOnNext (l);
    }
  }
  return nbElement;
}

int find(List * l, char *name){
  if(!isEmpty(l)){
    setOnFirst(l);
    while(!isOutOfList(l)){
      if(strcmp(getCurrentName(l), name) == 0) return 1;
      setOnNext (l);
    }
    return 0;
  }
  else
  {
    fprintf(stderr,"List empty cannot be found\n");
    return 0;
  }
}

static int deleteFirst(List * l) {
  if(isEmpty(l)){
    fprintf(stderr,"List empty cannot be deleted\n");
    return 0;
  }else{
    setOnFirst(l);
    NodeList *toDelete = l->first;
    l->first = l->first->next;

    // If list becomes empty after deletion
    if (l->first == NULL) {
      l->last = NULL;
    }

    freeNodeList(toDelete);
    return 1;  // Deletion successful
  }
}

static int deleteCurrent(List * l) {
  if(isEmpty(l)||isOutOfList(l)) {
    return 0;
  }
  if (isFirst(l)) {
    return deleteFirst(l);
  }
  // Find the element before current
  NodeList *prev = l->first;
  while (prev != NULL && prev->next != l->current) {
    prev = prev->next;
  }
  if (prev == NULL) {
    return 0;  // Something went wrong
  }
  //delete current node
  NodeList *toDelete = l->current;
  prev->next = toDelete->next;

  // Update last if we're deleting the last element
  if (isLast(l)) {
    l->last = prev;
  }

  // Move current to next element
  l->current = toDelete->next;

  // Free the node
  freeNodeList(toDelete);
  return 1;
}

int deleteValue(List * l, char *name) {
  if (isEmpty(l)) {
    fprintf(stderr, "List empty cannot be deleted\n");
    return 0;
  }

  // Search for the element
  setOnFirst(l);
  while (!isOutOfList(l)) {
    if (strcmp(getCurrentName(l), name) == 0) {
      return deleteCurrent(l);
    }
    setOnNext(l); //maybe in the list, there are two nodes with the same value so we continue de search
  }

  fprintf(stderr, "Element to be deleted not found\n");
  return 0;
}

void freeList(List * l) {
  if (l == NULL) return;

  while (!isEmpty(l)) {
    deleteFirst(l);
  }
  l->first = l->current = l->last = NULL;
}

#include "test.h"
/*!
* \brief  Unit testing of the functions provided in the list.c file
*/
void test_list(){
    List l1;
    int ret1;
    printf("Unit tests on the list module\n");

    /* group 1 */
    initList(&l1);
    display_test_int("Test isEmpty() on an empty list", 1, isEmpty(&l1));
    display_test_int("Test isOutOfList() when the list is empty", 1, isOutOfList(&l1));
    display_test_string("Test getCurrentName() when the list is empty", NULL, getCurrentName(&l1));
    display_test_check_by_user("Test printList on an empty list");
    printList(&l1);

    ret1 = insertFirst(&l1, "WEI", "data/fish.jpg", 10, 10, 2014, PHOTO);
    display_test_int("Test insertFirst() on an empty list", 1, ret1);

    ret1 = insertFirst(&l1, "WEI2", "data/fishAndTree.jpg", 11, 10, 2014, PHOTO);
    display_test_int("Test insertFirst() on a not-empty list", 1, ret1);
    display_test_check_by_user("Test insertFirst : (list should be with WEI2 and WEI)");
    printList(&l1);
    display_test_int("Test isEmpty() on an non-empty list", 0, isEmpty(&l1));

    setOnLast(&l1);
    display_test_int("Test isLast() when setOnLast", 1, isLast(&l1));
    display_test_int("Test isFirst() when not on first", 0, isFirst(&l1));
    display_test_int("Test isOutOfList() when in the list", 0, isOutOfList(&l1));
    display_test_string("Test getCurrentName() when in the list", "WEI", getCurrentName(&l1));

    setOnNext(&l1);
    display_test_int("Test isOutOfList() when out of the non-empty list", 1, isOutOfList(&l1));
    display_test_string("Test getCurrentName() when out of a non-empty list", NULL, getCurrentName(&l1));

    setOnFirst(&l1);
    display_test_int("Test isFirst() when setOnFirst", 1, isFirst(&l1));
    display_test_int("Test isLast() when not on last", 0, isLast(&l1));
    display_test_string("Test getCurrentName() when in the list", "WEI2", getCurrentName(&l1));

    setOnNext(&l1);
    display_test_int("Test setOnNext()", 1, isLast(&l1));

    /* group 2 */
    display_test_int("Test find()", 1, find(&l1, "WEI"));
    display_test_int("Test find()", 0, find(&l1, "WEI5"));

    /* group 3 */
    setOnFirst(&l1);
    display_test_int("Test deleteValue()", 0, deleteValue(&l1, "WEI6"));
    display_test_int("Test deleteValue()", 1, deleteValue(&l1, "WEI"));
    display_test_int("Test deleteFirst()", 1, deleteFirst(&l1));

    /* group 4 */
    display_test_check_by_user("Testing freeList on empty list");
    freeList(&l1);
    display_test_int("Test isEmpty() after freeList", 1, isEmpty(&l1));
    display_test_int("Test isOutOfList() after freeList", 1, isOutOfList(&l1));

    // Test inserting after freeing
    ret1 = insertFirst(&l1, "TEST", "data/test.jpg", 1, 1, 2024, PHOTO);
    display_test_int("Test insertFirst() after freeList", 1, ret1);

}
