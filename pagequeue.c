/** pagequeue.c
* ===========================================================
* Name: Sweta chandra Mohan, 4/ 22/ 2026
* Section: CS483 / M3
* Project: PEX3 - Page Replacement Simulator
* Purpose: Implementation of the PageQueue ADT — a doubly-linked
*          list for LRU page replacement.
*          Head = LRU (eviction end), Tail = MRU end.
* =========================================================== */
#include <stdio.h>
#include <stdlib.h>
#include "pagequeue.h"

/**
* @brief Create and initialize a page queue with a given capacity
*/



PageQueue *pqInit(unsigned int maxSize) {
   // TODO: malloc a PageQueue, set head and tail to NULL,
   //       size to 0, maxSize to maxSize, and return the pointer
   PageQueue *pq = malloc(sizeof(PageQueue));


   if (pq == NULL) {
       fprintf(stderr, "malloc failed\n");
       exit(1);
   }


   pq->head = NULL;
   pq->tail = NULL;
   pq->size = 0;
   pq->maxSize = maxSize;


   return pq;
}


//head == LRU / old
//tail = MRU / new


//if hit => find the pace and remove from current , move to tail, return depth
// if miss=> create a new node and insert at tale
//       if size is greater than max size, remove head and return -1


/**
* @brief Access a page in the queue (simulates a memory reference)
*/
//long pqAccess(PageQueue *pq, unsigned long pageNum) {
   // TODO: Search the queue for pageNum (suggest searching tail->head
   //       so you naturally count depth from the MRU end).


   //
   // HIT path (page found at depth d):
   //   - Remove the node from its current position and re-insert
   //     it at the tail (most recently used).
   //   - Return d.
   //
   // MISS path (page not found):
   //   - Allocate a new node for pageNum and insert it at the tail.
   //   - If size now exceeds maxSize, evict the head node (free it).
   //   - Return -1.




long pqAccess(PageQueue *pq, unsigned long pageNum) {


   //start w tail
   PqNode *current = pq->tail;
   int depth = 0;


   // search through ll
   while (current != NULL && current->pageNum != pageNum) {
       current = current->prev;
       depth++;
   }


   if (current != NULL) {


       //if not at tail then move
       if (current != pq->tail) {


           if (current->prev != NULL) {
               current->prev->next = current->next;
           }


           else {
               pq->head = current->next;
           }


           if (current->next != NULL) {
               current->next->prev = current->prev;
           }


           //attach it to the tail
           current->next = NULL;
           current->prev = pq->tail;
           pq->tail-> next = current;
           pq->tail = current;
       }


       return depth;
   }


   //MISS
   PqNode *newNode = malloc(sizeof(PqNode));
   //safety
   if (newNode == NULL) {


       printf("malloc has failed\n");
       exit(1);

   }

   newNode->pageNum = pageNum;


   newNode->next = NULL;
   newNode->prev = pq->tail;


   //new node to tail
   if (pq->tail != NULL) {
       pq->tail->next = newNode;
   }
   else {
       pq->head = newNode;
   }


   pq->tail = newNode;
   pq->size++;


   //remove head
   if (pq->size > pq->maxSize) {


       PqNode *temp = pq ->head;
       pq->head = pq-> head->next;

       if (pq->head != NULL) {

           pq->head->prev = NULL;
       }

       free(temp);
       pq->size--;
   }

   return -1;
}


/**
* @brief Free all nodes in the queue and reset it to empty
*/
void pqFree(PageQueue *pq) {

   PqNode *current = pq->head;

   while (current != NULL) {

       PqNode *temp = current;
       current = current->next;
       free(temp);

   }
   free(pq);
}


/**
* @brief Print queue contents to stderr for debugging
*/
void pqPrint(PageQueue *pq) {
   // TODO (optional): Print each page number from head to tail,
   //                  marking which is head and which is tail.
   //                  Useful for desk-checking small traces.
}




