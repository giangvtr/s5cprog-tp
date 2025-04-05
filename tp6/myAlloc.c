

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "myAlloc.h"
#include "memoryList.h"

List l = {
	{{NULL,NULL,0,NULL},&(l.sentinel_end),NULL},			/* sentinel_begin */
			&( l.sentinel_begin ) ,																			/* current */
		{{NULL,NULL,0,NULL},NULL,&(l.sentinel_begin)}		/* sentinel_end */
};

/*!
 * \brief Redefines the malloc function behavior
 * In addition of the memory allocation, this function adds an element in the list of the allocated blocks
 * \param[in] size the size of the block to be allocated
 * \param[in] file the file name where the memory allocation is required
 * \param[in] func the function name where the memory allocation is required
 * \param[in] line the line number where the memory allocation is required
 * \return void * the address of the allocated block
*/
void* myMalloc(unsigned int size, const char* file,  const char * func, int line)
{
	void * allocated_block;
	allocated_block = malloc (size);

	if (allocated_block != NULL)
	{
		if (!insertSort(&l,file,func,line,allocated_block)) {
			//if insertion fails, we free the allocated memory and return
			free(allocated_block);
			fprintf(stderr, "Failed to track memory allocation\n");
			return NULL;
		}
        	printf("In file %s,\n\t function %s,\n\t\t line %d :\n\t\t\t allocated block at memory address: %p\n",file,func,line,allocated_block);
	}

	return allocated_block;
}


/*!
 * \brief Redefines the free function behavior
 * In addition of the memory deallocation, this function  deletes an element in the list of the allocated blocks.
 * \param[in] block the address of the block to be deallocated
 * \param[in] file the file name where the memory deallocation is required
 * \param[in] func the function name where the memory deallocation is required
 * \param[in] line the line number where the memory deallocation is required
*/
void myFree ( void* block, const char* file,  const char * func, int line)
{
    if(block != NULL)
    {
        void *deleted = deleteValue(&l,block);
    	if (deleted == NULL) {
    		fprintf(stderr, "Warning: Attempting to free untracked memory block at %p\n", block);
    	}
		free(block);
    	printf("In file %s,\n\t function %s,\n\t\t line %d :\n\t\t\t freed block at memory address: %p\n",file, func, line, block);
    }
}

/*!
 * \fn  int myCheck()
 * \brief Check if every allocated block has been freed
 * It relies on the counter of allocated blocks
 * \return int the number of allocated blocks
*/
int myCheck()
{
    return !isEmpty(&l);
}

void myGarbageCollector() {
	if (isEmpty(&l)) {
		return; //no unfreed block allocated to be collected
	}

	printf("GarbageCollector start...\n");

	//free the unfreed block that is registered in the list
	setOnFirst(&l);
	while (!isOutOfList(&l)) {
		void* block = getCurrentAdress(&l);
		if (block != NULL) {
			printf("Garbage collector: freeing unfreed block at address %p\n", block);
			// Use standard free here to avoid modifying the list while iterating
			free(block);
		}
		setOnNext(&l);
	}

	// Now clear the tracking list itself by freeing each node
	while (!isEmpty(&l)) {
		setOnFirst(&l);
		if (!isOutOfList(&l)) {
			deleteValue(&l, l.current->b.address);
		}
	}

	printf("Garbage collection completed\n");
}



