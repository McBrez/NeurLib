/*
 * NeurLib.h
 *
 *  Created on: 13. Okt. 2017
 *      Author: David
 */

#ifndef NEURLIB_H_
#define NEURLIB_H_

//globals

char Debug_enabled = 0;
void (*DEBUG)(char *);

//enums

typedef enum{
	new,
	ready,
	learning,
	working,
	destroy,
}net_state;

typedef enum{
	SUCCESS,
	INVALID_ARGUMENT,
	MEMALLOC_FAILED,
	MEMDEALLOC_FAILED,
	INVALID_STATE,
	INVALID_DIMENSIONS,
}err_code;

typedef enum{
	input,
	output,
	output_learn,
	generic,
}vector_type;

typedef enum{
	linear,
} learn_type;

//structs

typedef struct{
	int size_x;
	int size_y;
	net_state state;
	double **net_matrix;
}net;

typedef struct{
	double *double_data;
	char dont_care;
}vector_data;

typedef struct{
	int size;
	vector_type type;
	vector_data *data;
}vector;

//Frontend functions
err_code createNetwork(int x, int y, net *netpointer);
err_code destroyNetwork(net *netpointer);
err_code learn(net *netpointer,const vector *input,const vector *output, learn_type type);
err_code feed(net *netpointer,const vector *input,vector *output);
err_code enable_Debug(void (*debug_fct)(char *));
err_code disable_Debug();

//Backend functions
void INIT_NET(net *netpointer, double x);
err_code CREATE_NETSTRUCT(net *p);
err_code CHECK_VECTOR_INPUTS(net *netpointer, vector *input, vector *output);
err_code HANLDE_DEBUG(char *str);
void SORT_ROW(double *row_elements, int size);
int GET_POSITION(double *row_elements_sorted, double *row_elements_original, int size);

#endif /* NEURLIB_H_ */
