/*
 * list.c
 *
 *  Created on: 31.10.2017
 *      Author: davfr
 */



list_element *create_list(int size)
{
	list_element *first_elem = 0;
	list_element *prev_elem = 0;
	list_element *curr_elem = 0;

	if(size > 0)
	{
		first_elem = malloc(sizeof(list_element));

		if(first_elem != 0)
		{
			first_elem->prev = 0;
			prev_elem = first_elem;

			for(int i = 0; i < size ; i++)
			{
				curr_elem =  malloc(sizeof(list_element));
				if(curr_elem != 0)
				{
					prev_elem->next = curr_elem;
					curr_elem->prev = curr_elem;

					prev_elem = curr_elem;
				}
				else
				{
					return 0;
				}
			}
			curr_elem->next = 0;

			return first_elem;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

/**
 * \brief gives the memory that is allocated to list free.
 * @param list the pointer to the list that that will be deallocated.
 */

void destroy_list(list_element *list);

/**
 * \brief swaps two elements of the supplied list.
 * @param list The list in which the elements will be swapped.
 * @param element1 The first element that will be swapped.
 * @param element2 The second element that will be swapped.
 * @return can return SUCCESS, INVALID_ARGUMENT or INVALID_DIMENSIONS
 */
err_code swap_elements(list_element *list, int element1, int element2);
