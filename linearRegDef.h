#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////////////////
/// #define(s) to increase readability of the code
////////////////////////////////////////////////////////////////////////////////////////////

//Menu options
#define CLEAR_MEMORY						0
#define	UPLOAD_NEW_FILE						1
#define	CALCULATE_REGRESSION_LINE			2
#define PRINT_RESULTS						3
#define RESULTS_TO_FILE						4
#define	CALCULATE_Y_WITH_REG_FUNC			6
#define	XY_TABLE_TO_FILE					7


//Boolean values
#define FALSE								0
#define TRUE								1

//Used for fopen() function
#define READ								"r"
#define WRITE								"w"

//kein plan wie in function machbar
#define GET_MEMORY(struct_name, size)		(struct struct_name*) calloc(size, sizeof(struct struct_name))
#define CHECK_MEMORY(struct_pointer)		if(struct_pointer == NULL){MessageBox_OK("Memory not allocated\nClear memory with menu option '0'", "Error"); break;}

												


