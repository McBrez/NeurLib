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

// ENUMERATIONS

/**
 * \brief enum for the state of a neural network
 */
typedef enum{
	new,		/**< net has just been created, it is not yet ready for use*/
	ready,		/**< net is ready for learning or feeding*/
	learning,	/**< net is currently learning*/
	working,	/**< data has been fed to the net*/
	destroy,	/**< net is being destroyed*/
}net_state;

/**
 * \brief The Error Codes which are used by front- and backendfunctions
 */

typedef enum{
	SUCCESS, 			/**< No error occured*/
	INVALID_ARGUMENT,	/**< Function has been handed an invalid Argument*/
	MEMALLOC_FAILED,	/**< Memory allocation has failed- Reason not further specified */
	MEMDEALLOC_FAILED,	/**< Memory deallovation has failed. Reason not further specified */
	INVALID_STATE,		/**< Net struct is not in the right state, to execute the requested function */
	INVALID_DIMENSIONS, /**< Vector do not have the required size */
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

//   STRUCTS

/**
 * \brief holds all the neural network information. Is basically a matrix
 *
 * The counting direction of the x and y is conform to the mathematical definitions of a matrix,
 * which means net_matrix[i][j] refer to the element in the i - row and the j - column.
 */

typedef struct{
	int size_x;  			/**< amount of columns of the matrix*/
	int size_y;	 			/**< amount of rows of the matrix*/
	net_state state;		/**< state of the net*/
	double **net_matrix;	/**< pointer in which the matrix elements are stored*/
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
net *createNetwork(int x, int y, err_code *err);
err_code destroyNetwork(net *netpointer);
err_code learn(net *netpointer,const vector *input,const vector *output, learn_type type);
err_code feed(net *netpointer,const vector *input,const vector *output);
err_code enable_Debug(void (*debug_fct)(char *));
err_code disable_Debug();

//Backend functions
void INIT_NET(net *netpointer, double x);
err_code CREATE_NETSTRUCT(net *p);
err_code CHECK_VECTOR_INPUTS(net *netpointer, vector *input, vector *output);
err_code HANLDE_DEBUG(char *str);
void SORT_ROW(double **row_elements, int size);
int GET_POSITION(double *row_elements_sorted, double *row_elements_original, int size);

#endif /* NEURLIB_H_ */
