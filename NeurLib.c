/*
 * NeurLib.c
 *
 *  Created on: 13. Okt. 2017
 *      Author: David
 */
#include "NeurLib.h"
#include <stdlib.h>


net *createNetwork(int x, int y, err_code *err)
{
	double **temp_netpointer = 0;
	net *net_struct = 0;
	err_code internal_err_code;

	if(x > 0 && y > 0)
	{
		internal_err_code = CREATE_NETSTRUCT(net_struct);

		if(internal_err_code == SUCCESS)
		{
			temp_netpointer = (double **)malloc(y * sizeof(double *));

			if(temp_netpointer != 0)
			{
				for(int i = 0 ; i < y ; i++)
				{
					double *A = 0;

					A = (double *)malloc(x * sizeof(double));

					if(A != 0)
					{
						temp_netpointer[i] = A;
					}
					else
					{
						*err = MEMALLOC_FAILED;
						return 0;
					}
				}

				net_struct->net_matrix = temp_netpointer;
				net_struct->size_x = x;
				net_struct->size_y = y;
				net_struct->state = ready;

				*err = SUCCESS;
				return net_struct;
			}
			else
			{
				*err = MEMALLOC_FAILED;
				return 0;
			}
		}
		else
		{
			*err = internal_err_code;
			return 0;
		}
	}
	else
	{
		*err = INVALID_ARGUMENT;
		return 0;
	}
}

err_code destroyNetwork(net *netpointer)
{
	free(netpointer);
	return SUCCESS;
}

err_code learn(net *netpointer,const vector *input,const vector *output, learn_type type)
{
	err_code internal_err_code;

	internal_err_code = CHECK_VECTOR_INPUTS(netpointer, input, output);

	if (internal_err_code == SUCCESS)
	{
		switch(type)
		{
		case linear:
		{
			for(int i = 0 ; i < netpointer->size_y ; i++)
			{
				if(output->data->dont_care == 0)
				{
					double delta = 0;
					double row_sum = 0;
					double k = 0;
					double temp_sum = 0;
					double *row_elements_sorted = 0;

					//build row sum
					for(int j = 0 ; i < netpointer->size_x ; j++)
					{
						row_sum = row_sum + netpointer->net_matrix[j][i] * input->data->double_data;
					}

					//calculate delta

					delta = output->data->double_data - row_sum;

					//calculate delta part for coefficients

					for(int j = 1 ; j <= netpointer->size_x ; j++)
					{
						temp_sum = temp_sum + j;
					}

					k = delta / temp_sum;
					row_elements_sorted = netpointer->net_matrix[i];
					SORT_ROW(row_elements_sorted, netpointer->size_x);

					//calculate new coefficients

					for(int j = 0 ; j < netpointer->size_x ; j++)
					{
						int pos;

						pos = GET_POSITION(row_elements_sorted, &netpointer->net_matrix[i][j], netpointer->size_x);
						if(pos > 0)
						{
							netpointer->net_matrix[i][j] = netpointer->net_matrix[i][j]*input[j]
						}
					}
				}
			}
			break;
		}
		}
	}
	else
	{

	}
}

err_code feed(net *netpointer,const vector *input,const vector *output)
{
	if(CHECK_VECTOR_INPUTS(netpointer, input, output) == SUCCESS)
	{
		for(int j = 0 ; j < output->size ; j++)
		{
			double sum = 0;

			for(int i = 0 ; i < input->size ; i++)
			{
				sum = sum + netpointer->net_matrix[i][j] * input[i];
			}

			output[j] = sum;
		}
		return SUCCESS;
	}
	else
	{

		return INVALID_ARGUMENT;
	}
}

err_code enable_Debug(void (*debug_fct)(char *))
{
	if(debug_fct != 0)
	{
		Debug_enabled = 1;
		DEBUG = debug_fct;

		return SUCCESS;
	}
	else
	{
		return INVALID_ARGUMENT;
	}
}

err_code disable_Debug()
{
	Debug_enabled = 0;
	DEBUG = 0;

	return SUCCESS;
}

void INIT_NET(net *netpointer, double x)
{

}

err_code CREATE_NETSTRUCT(net *p)
{
	if(p != 0)
	{
		net net_struct = {
			0,
			0,
			new,
			0,
		};

		p = &net_struct;

		return SUCCESS;
	}
	else
	{
		return INVALID_ARGUMENT;
	}
}

err_code CHECK_VECTOR_INPUTS(net *netpointer, vector *input, vector *output)
{
	if(netpointer > 0 && input > 0 && output > 0)
	{
		//pointers seem ok.
		if(netpointer->size_x == input->size && netpointer->size_y == output->size)
		{
			//dimensions are ok
			if(netpointer->state == ready)
			{
				//net is ready
				return SUCCESS;
			}
			else
			{
				return INVALID_STATE;
			}
		}
		else
		{
			return INVALID_DIMENSIONS;
		}
	}
	return INVALID_ARGUMENT;
}

err_code HANLDE_DEBUG(char *str)
{
	if(Debug_enabled == 1)
	{
		DEBUG(str);
		return SUCCESS;
	}
	else
	{
		//do nothing
		return SUCCESS;
	}
}

void SORT_ROW(double **row_elements, int size)
{
	int finished;
	double *temp_pointer;

	do
	{
		finished = 1;
		for(int i = 0 ; i < size - 1 ; i++)
		{
			if(row_elements[i+1] < row_elements[i])
			{
				temp_pointer = row_elements + i + 1;
				&(row_elements + 1) = &row_elements[i];
				&(row_elements[i]) = temp_pointer;

				finished = 0;
			}
		}
	}
	while(!finished);
}

int GET_POSITION(double *row_elements_sorted, double *row_elements_original, int size)
{
	for(int i = 0; i < size ; i++)
	{
		if(row_elements_sorted[i] == row_elements_original)
		{
			return i;
		}
	}

	return -1;
}
