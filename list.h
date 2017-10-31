/**
 * list.h
 *
 *  Created on: 31.10.2017
 *      Author: davfr
 *
 *  provides functions for working with lists
 */

/**
 *  \brief struct of an list element
 *
 *  Data that is stored in the list should be casted, since the pointer is of type void.
 */
typedef struct{
	list_element *prev;
	list_element *next;
	void *data;
}list_element;

/**
 * \brief Allocates memory for the list and returns the pointer.
 *
 * @param size elements of the list.
 * @return returns the pointer to the first list element or 0 if allocation was not successful
 */
list_element *create_list(int size);

/**
 * \brief gives the memory that is allocated to list free.
 * @param list the pointer to the list that that will be deallocated.
 */

void destroy_list(list_element *list);

/**
 * \brief swaps two elements of the supplied list.
 * Indexcounting starts with 0. i.e. the first element (The head of the list) has the index 0, the second element has the
 * index 1, and so on.
 * @param list The list in which the elements will be swapped.
 * @param element1 The index of the first element that will be swapped.
 * @param element2 The index of the second element that will be swapped.
 * @return can return SUCCESS, INVALID_ARGUMENT or INVALID_DIMENSIONS
 */
err_code swap_elements(list_element *list, int element1, int element2);

/**
 * \brief inserts an element at the specified index.
 * Indexcounting starts with 0. i.e. the first element (Head of the list) has the index 0, the second element has the
 * index 1, and so on.
 * @params list the list in which the element will be inserted.
 * @params element the element which will be inserted in the list.
 * @params insert_index index where the element will be inserted.
 * @return The function returns the head of the list.
 */
list_element *insert_element(list_element *list, list_element *element, int insert_index);
